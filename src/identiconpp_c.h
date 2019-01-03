/*  This file is part of identiconpp.
 *  Copyright © 2019 tastytea <tastytea@tastytea.de>
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

#ifndef IDENTICONPP_H
#define IDENTICONPP_H

#ifdef __cplusplus
extern "C"
{
#endif

    #include <stdbool.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <MagickWand/MagickWand.h>

    typedef enum
    {
        identiconpp_ltr_symmetric,
        identiconpp_ltr_asymmetric,
        identiconpp_sigil
    } identiconpp_algorithm;

    bool identiconpp_setup(const uint8_t columns, const uint8_t rows,
                           identiconpp_algorithm type,
                           const char background[9],
                           const char foreground[][9],
                           const uint8_t foreground_len,
                           const uint8_t padding[2]);
    bool identiconpp_generate(MagickWand *wand,
                              const char digest[], const uint16_t width);

#ifdef __cplusplus
}
#endif
#endif  // IDENTICONPP_H
