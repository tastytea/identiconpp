/*  This file is part of identiconpp.
 *  Copyright © 2018 tastytea <tastytea@tastytea.de>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <exception>
#include <stdexcept>
#include <sstream>
#include "identiconpp.hpp"
#include "debug.hpp"

Identiconpp::Identiconpp(const uint8_t columns, const uint8_t rows,
                         algorithm type,
                         const string &background,
                         const vector<string> &foreground,
                         const array<const uint8_t, 2> &padding)
: _rows(rows)
, _columns(columns)
, _type(type)
, _background(background)
, _foreground(foreground)
, _padding(padding)
{
    check_color(background);

    for (const string &color : foreground)
    {
        check_color(color);
    }
}

Magick::Image Identiconpp::generate(const string &digest, const uint16_t width)
{
    ttdebug << "Using digest: " << digest << '\n';
    check_entropy(digest, _type);
    const uint16_t imgwidth = width - _padding[0] * 2;
    const uint16_t imgheight = imgwidth / _columns * _rows;
    ttdebug << "width: " << std::to_string(imgwidth + _padding[0] * 2)
            << ", height: " << std::to_string(imgheight + _padding[1] * 2)
            << "\n";
    Magick::Image img;

    switch (_type)
    {
        case algorithm::ltr_symmetric:
        {
            img = generate_ltr_symmetric(digest);
            break;
        }
        case algorithm::ltr_asymmetric:
        {
            img = generate_ltr_asymmetric(digest);
            break;
        }
        case algorithm::sigil:
        {
            img = generate_sigil(digest);
            break;
        }
    }

    img.backgroundColor(Magick::Color('#' + _background));
    img.scale(Magick::Geometry(imgwidth, imgheight));
    img.borderColor(Magick::Color('#' + _background));
    img.border(Magick::Geometry(_padding[0], _padding[1]));
    img.magick("png");
    return img;
}

bool Identiconpp::get_bit(const uint16_t bit, const string &digest)
{
    std::stringstream ss;
    ss << std::hex << digest[bit / 4];
    // std::stringstream does not support writing into uint8_t
    unsigned short nibble;
    ss >> nibble;

    // Shift nibble to the right until the bit we want is on the right border.
    // Then check if it is set.
    if (nibble >> (3 - bit % 4) & 1)
    {
        ttdebug << "Bit " << std::to_string(bit + 1) << " is set.\n";
        return true;
    }

    return false;
}

Magick::Color Identiconpp::get_color(const uint16_t firstbit,
                                     const string &digest)
{
    // Number of bits to use
    const uint16_t colorbits = _foreground.size() / 2 + _foreground.size() % 2;

    // Extract approximation
    std::stringstream ss;
    if (colorbits % 4 == 0)
    {
        ss << std::hex << digest.substr(firstbit / 4, colorbits / 4);
    }
    else
    {
        ss << std::hex << digest.substr(firstbit / 4, colorbits / 4 + 1);
    }
    // std::stringstream does not support writing into uint16_t
    unsigned short bits;
    ss >> bits;
    
    // Shift an one $colorbits times to the left, substract 1. This leaves us
    //  with $colorbits ones. Then AND bits and our ones to keep only as many
    //  bits as we need.
    bits = bits & ((1 << colorbits) - 1);

    // We may get a number that is slightly too big if _foreground.size() is not
    // a power of 2.
    if (bits > (_foreground.size() - 1))
    {
        bits -= (_foreground.size() - 1);
    }

    // Lookup und set color
    ttdebug << "Color: #" << _foreground[bits] << '\n';
    return Magick::Color("#" + _foreground[bits]);
}
