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
                         const string &background,
                         const vector<string> &foreground)
: _rows(rows)
, _columns(columns)
, _background(background)
, _foreground(foreground)
{
    // TODO: Check rows and columns
    if (_background.size() != 8)
    {
        throw std::invalid_argument("Background color has the wrong format: " +
                                    _background);
    }
    for (const string &color : _foreground)
    {
        if (color.size() != 8)
        {
            throw std::invalid_argument("Foreground color has the wrong format: " +
                                        color);
        }
    }
}

