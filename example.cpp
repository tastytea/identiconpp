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
        Identiconpp identicon(13, 10, Identiconpp::identicon_type::simple,
            "ffffff88",
            { 
                "000000ff",
                "ff0000ff",
                "ffff00ff",
                "00ff00ff",
                "00ffffff",
                "0000ffff"
            });
        img = identicon.generate(digest, 500);
        img.write("identicon_example_simple.png");
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::identicon_type::libravatar,
            "ffffffff",
            {
                "000000ff",
                "ff0000ff",
                "ffff00ff",
                "00ff00ff",
                "00ffffff",
                "0000ffff"
            });
        img = identicon.generate("5a105e8b9d40e1329780d62ea2265d8a", 500);
        img.write("identicon_example_libravatar.png");
    }

    return 0;
}
