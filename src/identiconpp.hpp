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
#include <tuple>
#include <Magick++/Image.h>

using std::uint8_t;
using std::uint16_t;
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
     * @brief  Return type for images.
     */
    struct Image
    {
        uint8_t error;
        Magick::Image data;
    };

    /*!
     *  @brief  List of identicon types
     *
     *          libravatar and sigil are synonymous.
     */
    enum class identicon_type
    {
        simple,
        libravatar,
        sigil
    };

    /*!
     *  @brief  Initialises an instance of Identiconpp.
     *
     *          The instance can be used for creating identicons with differing
     *          image formats and sizes.
     *
     *  @param  rows        Number of rows
     *  @param  columns     Number of columns
     *  @param  background  Background color, hexadecimal, rrggbbaa
     *  @param  foreground  vector of foreground colors
     */
    explicit Identiconpp(const uint8_t rows, const uint8_t columns,
                         const uint32_t background = 0xffffffff,
                         const vector<uint32_t> &foreground = { 0x000000ff } );

    /*!
     *  @brief  Generates identicon from digest.
     *
     *  @param  digest  The pre-computed digest
     *  @param  type    The type of identicon
     *  @param  width   The width of the image
     *  @param  height  The height of the image
     *
     *  @return 0 and an image on success, 1 and an empty image on error.
     */
    Image generate(const string &digest, identicon_type type,
                   const uint16_t width = 100, const uint16_t height = 100);

private:
    const uint8_t _rows;
    const uint8_t _columns;
    const uint32_t _background;
    const vector<uint32_t> _foreground;

    /*!
     *  @brief  Generate simple identicon.
     *
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the image
     *  @param  height  The height of the image
     *
     *  @return 0 and an image on success, 1 and an empty image on error.
     */
    Image generate_simple(const string &digest,
                          const uint16_t width, const uint16_t height);

    /*!
     *  @brief  Generate libravatar-style / sigil identicon.
     *
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the image
     *  @param  height  The height of the image
     *
     *  @return 0 and an image on success, 1 and an empty image on error.
     */
    Image generate_libravatar(const string &digest,
                              const uint16_t width, const uint16_t height);

    /*!
     *  @brief  Check if the digest contains enough entropy.
     *
     *          Throws `std::invalid_argument` if not.
     *
     *  @param  digest  The pre-computed digest
     *  @param  type    The type of identicon
     */
    void check_entropy(const string &digest, identicon_type type);

    /*!
     *  @brief  Determines if the n-th bit of passed digest is 1 or 0.
     *
     *  @param  bit     Bit to get
     *  @param  digest  The digest
     *
     *  @return The bit.
     */
    bool get_bit(const uint16_t bit, const string &digest);

    /*!
     *  @brief  Chooses a foreground color.
     *
     *          Extracts the right bits from the digest and returns a color.
     *
     *  @param  firstbit  The first bit of the digest to choose a color
     *  @param  digest    The digest
     *
     *  @return A foreground color.
     */
    Magick::Color get_color(const uint16_t firstbit, const string &digest);
};
