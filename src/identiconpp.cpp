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
#include <bitset>
#include "identiconpp.hpp"
#include "debug.hpp"

Identiconpp::Identiconpp(const uint8_t rows, const uint8_t columns,
                         algorithm type,
                         const string &background,
                         const vector<string> &foreground)
: _rows(rows)
, _columns(columns)
, _type(type)
, _background(background)
, _foreground(foreground)
{
    check_color(background);

    for (const string &color : foreground)
    {
        check_color(color);
    }
}

Magick::Image Identiconpp::generate(const string &digest, const uint16_t width)
{
    check_entropy(digest, _type);
    const uint16_t height = width / _columns * _rows;
    ttdebug << "width: " << std::to_string(width)
            << ", height: " << std::to_string(height) << "\n";

    switch (_type)
    {
        case algorithm::ltr_symmetric:
        {
            return generate_ltr_symmetric(digest, width, height);
        }
        case algorithm::sigil:
        {
            return generate_sigil(digest, width, height);
        }
    }
}

bool Identiconpp::get_bit(const uint16_t bit, const string &digest)
{
    std::stringstream ss;
    ss << std::hex << digest[bit / 4];
    // std::stringstream does not support writing into uint8_t
    unsigned short buf;
    ss >> buf;
    std::bitset<4> nibble(buf);
    
    if (nibble[3 - bit % 4])
    {
        ttdebug << "Bit " << std::to_string(bit + 1) << " is set in "
                << digest << ".\n";
        ttdebug << nibble << " (" << bit % 4 << ")\n";
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
    unsigned short bits;
    ss >> bits;
    
    // Get rid of excess bits
    bits = bits & (1 << colorbits) - 1;

    if (bits > (_foreground.size() - 1))
    {
        bits -= (_foreground.size() - 1);
    }

    // Lookup und set color
    ttdebug << "Color: #" << _foreground[bits] << '\n';
    return Magick::Color("#" + _foreground[bits]);
}
