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

#include "identiconpp.hpp"
#include "debug.hpp"

Magick::Image Identiconpp::generate_sigil(const string &digest)
{
    Magick::Image img(Magick::Geometry(_columns, _rows),
                      Magick::Color("#00000000"));
    Magick::Color dotcolor = get_color(0, digest);

    uint8_t used_columns = _columns / 2 + _columns % 2;
    uint8_t cells = _rows * used_columns;
    for (uint8_t cur_cell = 0; cur_cell < cells; ++cur_cell)
    {
        if (get_bit(8 + cur_cell, digest))
        {
            const uint8_t column = cur_cell / _columns;
            const uint8_t row = cur_cell % _rows;
            ttdebug << "col=" << std::to_string(column)
                    << ", row=" << std::to_string(row) << '\n';
            img.pixelColor(column, row, dotcolor);
            img.pixelColor(_columns - column - 1, row, dotcolor);
        }
    }

    return img;
}
