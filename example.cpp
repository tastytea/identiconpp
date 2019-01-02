/*  This file is part of identiconpp.
 *  Public Domain / CC-0
 *
 *   Compile with g++ $(Magick++-config --cppflags --ldflags) -lidenticonpp
 */

#include <string>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

int main(int argc, char *argv[])
{
    string digest =
        "973dfe463ec85785f5f95af5ba3906eedb2d931c24e69824a89ea65dba4e813b";
    Magick::Image img;

    if (argc > 1)
    {
        digest = argv[1];
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::algorithm::ltr_symmetric,
            "ffffff80",
            { 
                "000000ff",
                "ff0000ff",
                "ffff00ff",
                "00ff00ff",
                "00ffffff",
                "0000ffff"
            }, { 10, 10 });
        img = identicon.generate(digest, 500);
        img.write("identicon_example_ltr_symmetric.png");
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::algorithm::ltr_asymmetric,
            "00000080",
            { 
                "ffffffc0",
                "ff0000c0",
                "ffff00c0",
                "00ff00c0",
                "00ffffc0",
                "0000ffc0"
            });
        img = identicon.generate(digest, 500);
        img.write("identicon_example_ltr_asymmetric.png");
        img.magick("GIF");
        img.write("identicon_example_ltr_asymmetric.gif");
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::algorithm::sigil,
            "ffffffff",
            {
                "000000ff",
                "ff0000ff",
                "ffff00ff",
                "00ff00ff",
                "00ffffff",
                "0000ffff"
            });
        img = identicon.generate(digest, 500);
        img.write("identicon_example_sigil.png");
        img.write("identicon_example_sigil.jpg");
    }

    return 0;
}