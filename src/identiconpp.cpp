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
                                         identicon_type type)
{
    switch (type)
    {
        case identicon_type::simple:
        {
            return generate_simple(digest);
        }
        case identicon_type::libravatar:
        case identicon_type::sigil:
        {
            return generate_libravatar(digest);
        }
    }
}

Identiconpp::Image Identiconpp::generate_simple(const string &digest)
{
    return { 1, Magick::Image() };
}

Identiconpp::Image Identiconpp::generate_libravatar(const string &digest)
{
    uint8_t entropy_provided = digest.length() / 2 * 8;
    uint8_t entropy_required = (_columns / 2 + _columns % 2) * _rows + 8;
    ttdebug << "entropy_provided=" << std::to_string(entropy_provided)
        << ", entropy_required=" << std::to_string(entropy_required) << '\n';

    if (entropy_provided < entropy_required)
    {
        throw std::invalid_argument(
            "Passed digest \"" + digest + "\" is not capable of providing " +
            std::to_string(entropy_required) + " bits of entropy.");
    }

    // TODO: implement

    return { 1, Magick::Image() };
}
