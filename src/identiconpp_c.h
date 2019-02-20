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

#ifndef IDENTICONPP_C_H
#define IDENTICONPP_C_H

#ifdef __cplusplus
extern "C"
{
#endif

    #include <stdbool.h>
    #include <stdint.h>
    #include <stddef.h>

    /*!
     * @brief   C interface for identiconpp.
     * @file identiconpp_c.h
     * @example example.c
     */

    /*!
     * @brief  List of identicon algorithms
     */
    typedef enum
    {
        //! Generates symmetric (vertically mirrored) identicons.
        identiconpp_ltr_symmetric,
        //! Generates asymmetric identicons.
        identiconpp_ltr_asymmetric,
        /*!
         * Generates the same results as
         * [sigil](https://github.com/cupcake/sigil/) and
         * [pydenticon](https://github.com/azaghal/pydenticon/).
         */
        identiconpp_sigil
    } identiconpp_algorithm;

    /*!
     *  @brief  Setup identicon parameters.
     *
     *  @param  columns         Number of columns
     *  @param  rows            Number of rows
     *  @param  type            The algorithm to use
     *  @param  background      Background color, hexadecimal, rrggbbaa
     *  @param  foreground      Array of foreground colors
     *  @param  foreground_len  Length of the array of foreground colors
     *  @param  padding         Padding in pixels { left & right, top & down }
     *
     *  @return false on error, true otherwise.
     *  
     *  @since  before 0.5.0
     */
    bool identiconpp_setup(const uint8_t columns, const uint8_t rows,
                           identiconpp_algorithm type,
                           const char background[9],
                           const char foreground[][9],
                           const uint8_t foreground_len,
                           const uint8_t padding[2]);

    /*!
     *  @brief  Generates identicon from digest.
     *
     *  @param  magick  See http://imagemagick.org/script/formats.php
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the identicon
     *
     *  @return Length of the generated base64-string, or 0 on error.
     *  
     *  @since  before 0.5.0
     */
    uint64_t identiconpp_generate(const char magick[],
                                  const char digest[], const uint16_t width);

    /*!
     *  @brief  Return base64-encoded string of the image generated with
     *          identiconpp_generate().
     *
     *  @since  before 0.5.0
     */
    const char *identiconpp_base64();

#ifdef __cplusplus
}
#endif
#endif  // IDENTICONPP_C_H
