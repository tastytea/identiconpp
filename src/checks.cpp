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
#include <algorithm>
#include <cmath>
#include "identiconpp.hpp"
#include "debug.hpp"

void Identiconpp::check_entropy(const string &digest, algorithm type)
{
    if (std::any_of(digest.begin(), digest.end(), not_hex))
    {
        throw std::invalid_argument
        (
            "Colors must consist of hexadecimal digits (" + digest + ")."
        );
    }

    uint16_t entropy_provided;
    uint16_t entropy_required;
    switch (type)
    {
        case algorithm::ltr_symmetric:
        {
            // Every char is 4 bit
            entropy_provided = digest.length() * 4;
            // We need bits for each field in half of the columns, +1 column if
            // they are uneven. Then we need enough bits to pick a color.
            entropy_required = (_columns / 2 + _columns % 2) * _rows
                + std::floor(std::log2(_foreground.size())) + 1;
            break;
        }
        case algorithm::ltr_asymmetric:
        {
            entropy_provided = digest.length() * 4;
            entropy_required = _columns * _rows
                + std::floor(std::log2(_foreground.size())) + 1;
            break;
        }
        case algorithm::sigil:
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

bool Identiconpp::not_hex(const char c)
{
    if (c >= 0x61 && c <= 0x66)
    {   // a-f
        return false;
    }
    if (c >= 0x30 && c <= 0x39)
    {   // 0-9
        return false;
    }

    return true;
}

void Identiconpp::check_color(const string &color)
{
    if (color.length() != 8)
    {
        throw std::invalid_argument
        (
            "Colors must consist of exactly 8 digits(" + color + ")."
        );
    }
    if (std::any_of(color.begin(), color.end(), not_hex))
    {
        throw std::invalid_argument
        (
            "Colors must consist of hexadecimal digits (" + color + ")."
        );
    }
}
