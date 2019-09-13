/*  This file is part of identiconpp.
 *  Public Domain / CC-0
 *
 *   Compile with g++ $(pkg-config --libs --cflags identiconpp)
 */

#include <string>
#include <vector>
#include "identiconpp.hpp"
#include <Magick++/Image.h>

int main(int argc, char *argv[])
{
    // sha256(test@example.com)
    std::string digest = "973dfe463ec85785f5f95af5ba3906ee"
                         "db2d931c24e69824a89ea65dba4e813b";
    const std::vector<std::string> colors = 
    {
        "800000ff",
        "008000ff",
        "000080ff",
        "808000ff",
        "008080ff",
        "800080ff"
    };
    Magick::Image img;

    if (argc > 1)
    {
        digest = argv[1];
    }

    {
        Identiconpp identicon(4, 4, Identiconpp::algorithm::ltr_symmetric,
                              "ffffffff", colors, { 20, 20 });
        img = identicon.generate(digest , 200);
        img.write("identicon1.png");
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::algorithm::sigil,
                              "00000080", colors);
        img = identicon.generate(digest , 200);
        img.write("identicon2.png");
    }

    {
        Identiconpp identicon(5, 5, Identiconpp::algorithm::ltr_asymmetric,
                              "000000ff", colors);
        img = identicon.generate(digest , 200);
        img.write("identicon3.png");
    }

    {
        Identiconpp identicon(6, 4, Identiconpp::algorithm::ltr_symmetric,
                              "000000c0", colors, { 10, 10 });
        img = identicon.generate(digest , 200);
        img.write("identicon4.png");
    }

    return 0;
}
