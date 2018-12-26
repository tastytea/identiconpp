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
 *          Use this class for all your identicons. Exceptions will be thrown on
 *          error.
 */
class Identiconpp
{
public:
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
     *          image formats and sizes. The colors must consist of exactly 8
     *          digits.
     *
     *  @param  rows        Number of rows
     *  @param  columns     Number of columns
     *  @param  type        The type of identicon
     *  @param  background  Background color, hexadecimal, rrggbbaa
     *  @param  foreground  vector of foreground colors
     */
    explicit Identiconpp(const uint8_t rows, const uint8_t columns,
                         identicon_type type = identicon_type::simple,
                         const string background = "ffffffff",
                         const vector<string> &foreground = { "000000ff" } );

    /*!
     *  @brief  Generates identicon from digest.
     *
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the image
     *
     *  @return The image
     */
    Magick::Image generate(const string &digest, const uint16_t width = 100);

private:
    const uint8_t _rows;
    const uint8_t _columns;
    const identicon_type _type;
    const string _background;
    const vector<string> _foreground;

    /*!
     *  @brief  Generate simple identicon.
     *
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the image
     *  @param  height  The height of the image
     *
     *  @return The image
     */
    Magick::Image generate_simple(const string &digest,
                                  const uint16_t width,
                                  const uint16_t height);

    /*!
     *  @brief  Generate libravatar-style / sigil identicon.
     *
     *  @param  digest  The pre-computed digest
     *  @param  width   The width of the image
     *  @param  height  The height of the image
     *
     *  @return The image
     */
    Magick::Image generate_libravatar(const string &digest,
                                      const uint16_t width,
                                      const uint16_t height);

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

    /*!
     *  @brief  Checks if character is not hexadecimal.
     *
     *  @param  c       Character to check
     *
     *  @return true if not hex.
     */
    static bool not_hex(const char c);

    /*!
     *  @brief  Performs checks on a color definition in a string.
     *
     *  @param  color   The color as string
     */
    void check_color(const string &color);
};
