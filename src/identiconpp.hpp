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

#include <cstdint>
#include <string>
#include <vector>

using std::uint8_t;
using std::uint32_t;
using std::string;
using std::vector;

/*!
 *  @brief  Base class for identiconpp.
 *
 *          Use this class for all your identicons.
 */
class Identiconpp
{
public:
    /*!
     *  @brief  Initialises an instance of Identiconpp.
     *
     *          The instance can be used for creating identicons with differing
     *          image formats and sizes. Will throw `std::invalid_argument` if
     *          an argument is invalid.
     *
     *  @param  rows        Number of rows
     *  @param  columns     Number of columns
     *  @param  background  Background color, hexadecimal, rrggbbaa
     *  @param  foreground  vector of foreground colors
     */
    explicit Identiconpp(const uint8_t rows, const uint8_t columns,
                         const uint32_t background = 0xffffffff,
                         const vector<uint32_t> &foreground = { 0x000000ff } );

private:
    const uint8_t _rows;
    const uint8_t _columns;
    const uint32_t _background;
    const vector<uint32_t> _foreground;
};
