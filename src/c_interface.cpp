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

#include <vector>
#include <memory>
#include <exception>
#include <iostream>
#include <Magick++/Image.h>
#include <Magick++/Blob.h>
#include "identiconpp.hpp"
#include "debug.hpp"
#include "identiconpp_c.h"

using std::cerr;
using std::endl;

static std::unique_ptr<Identiconpp> identicon;
static string base64;

bool identiconpp_setup(const uint8_t columns, const uint8_t rows,
                       identiconpp_algorithm type,
                       const char background[9],
                       const char foreground[][9],
                       const uint8_t foreground_len,
                       const uint8_t padding[2])
{
    Identiconpp::algorithm algo = Identiconpp::algorithm::ltr_symmetric;
    switch (type)
    {
        case identiconpp_ltr_symmetric:
        {
            algo = Identiconpp::algorithm::ltr_symmetric;
            break;
        }
        case identiconpp_ltr_asymmetric:
        {
            algo = Identiconpp::algorithm::ltr_asymmetric;
            break;
        }
        case identiconpp_sigil:
        {
            algo = Identiconpp::algorithm::sigil;
            break;
        }
    }

    std::vector<string> vforeground;
    for (uint8_t i = 0; i < foreground_len; ++i)
    {
        vforeground.push_back(foreground[i]);
    }

    try
    {
        identicon = std::make_unique<Identiconpp>(
                    Identiconpp(columns, rows, algo, background, vforeground,
                                { padding[0], padding[1] }));
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        return false;
    }

    return true;
}

uint64_t identiconpp_generate(const char magick[],
                              const char digest[], const uint16_t width)
{
    try
    {
        Magick::Image img = identicon->generate(digest, width);
        Magick::Blob blob;
        img.magick(magick);
        img.write(&blob);
        base64 = blob.base64();
        return blob.base64().length();
    }
    catch (const std::exception &e)
    {
        cerr << e.what() << endl;
        return 0;
    }
}

const char *identiconpp_base64()
{
    return base64.c_str();
}
