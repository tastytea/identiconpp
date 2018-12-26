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
#include <iomanip>
#include "identiconpp.hpp"
#include "debug.hpp"

Identiconpp::Identiconpp(const uint8_t rows, const uint8_t columns,
                         const uint32_t background,
                         const vector<uint32_t> &foreground)
: _rows(rows)
, _columns(columns)
, _background(background)
, _foreground(foreground)
{
}

Identiconpp::Image Identiconpp::generate(const string &digest,
                                         identicon_type type,
                                         const uint16_t width,
                                         const uint16_t height)
{
    check_entropy(digest, type);
    switch (type)
    {
        case identicon_type::simple:
        {
            return generate_simple(digest, width, height);
        }
        case identicon_type::libravatar:
        case identicon_type::sigil:
        {
            return generate_libravatar(digest, width, height);
        }
    }
}

Identiconpp::Image Identiconpp::generate_simple(const string &digest,
                                                const uint16_t width,
                                                const uint16_t height)
{
    std::stringstream ss;
    ss << std::hex << _background;
    const string bgcolor = "#" + ss.str();
    Magick::Image img(Magick::Geometry(_columns, _rows),
                      Magick::Color(bgcolor));
    uint8_t used_columns = _columns / 2 + _columns % 2;
    Magick::Color dotcolor = get_color(used_columns * _rows + 1, digest);

    for (uint8_t row = 0; row < _rows; ++row)
    {
        for (uint8_t column = 0; column < used_columns; ++column)
        {
            if (get_bit(row * used_columns + column, digest))
            {
                ttdebug << "col=" << std::to_string(column)
                        << ", row=" << std::to_string(row) << '\n';
                ttdebug << "col=" << std::to_string(used_columns - 1 + column)
                        << ", row=" << std::to_string(_rows - 1 - row) << '\n';
                img.pixelColor(column, row, dotcolor);
                img.pixelColor(_columns - 1 - column, row, dotcolor);
            }
        }
    }

    img.scale(Magick::Geometry(width, height));
    img.magick("png");
    return { 0, img };
}

Identiconpp::Image Identiconpp::generate_libravatar(const string &digest,
                                                    const uint16_t width,
                                                    const uint16_t height)
{
    return { 1, Magick::Image() };
}

void Identiconpp::check_entropy(const string &digest, identicon_type type)
{
    uint8_t entropy_provided;
    uint8_t entropy_required;
    switch (type)
    {
        case identicon_type::simple:
        {
            // Every char is 4 bit
            entropy_provided = digest.length() * 4;
            // We need bits for each field in half of the columns, +1 column if
            // they are uneven. Then we need enough bits to pick a color.
            entropy_required = (_columns / 2 + _columns % 2) * _rows
                + (_foreground.size() / 2 + _foreground.size() % 2);
            break;
        }
        case identicon_type::libravatar:
        case identicon_type::sigil:
        {
            entropy_provided = digest.length() / 2 * 8;
            entropy_required = (_columns / 2 + _columns % 2) * _rows + 8;
            break;
        }
    }
    ttdebug << "entropy_provided=" << std::to_string(entropy_provided)
        << ", entropy_required=" << std::to_string(entropy_required) << '\n';

    if (entropy_provided < entropy_required)
    {
        throw std::invalid_argument(
            "Passed digest \"" + digest + "\" is not capable of providing " +
            std::to_string(entropy_required) + " bits of entropy.");
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
    
    if (nibble[bit % 4])
    {
        // ttdebug << "Bit " << std::to_string(bit) << " is set in " << digest << ".\n";
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

    // Lookup und set color
    ss.str(string());
    ss.clear();
    ss << std::hex << std::setw(8) << std::setfill('0') << _foreground[bits - 1];
    ttdebug << "Color: #" << ss.str() << '\n';
    return Magick::Color("#" + ss.str());
}
