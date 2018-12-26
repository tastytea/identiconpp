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

Magick::Image Identiconpp::generate_simple(const string &digest,
                                           const uint16_t width,
                                           const uint16_t height)
{
    Magick::Image img(Magick::Geometry(_columns, _rows),
                      Magick::Color("#" + _background));
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
    return img;
}
