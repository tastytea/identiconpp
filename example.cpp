/*  This file is part of identiconpp.
 *  Public Domain / CC-0
 */

#include <iostream>
#include <string>
#include "identiconpp.hpp"

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[])
{
    string algorithm = "simple";
    if (argc > 1)
    {
        algorithm = argv[1];
    }

    if (algorithm == "simple")
    {
        cout << "You selected the \"simple\" algorithm.\n";
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

        Magick::Image img;
        img = identicon.generate("55502f40dc8b7c769880b10874abc9d0");
        img.write("identicon_example_simple1.png");
        img = identicon.generate
        (
            "973dfe463ec85785f5f95af5ba3906eedb2d931c24e69824a89ea65dba4e813b",
            500
        );
        img.write("identicon_example_simple2.png");
    }
    else if (algorithm == "libravatar")
    {
        cout << "You selected the \"libravatar\" algorithm.\n";
        Identiconpp identicon(10, 10, Identiconpp::identicon_type::libravatar,
            "ffffffff",
            {
                "000000ff",
                "ff0000ff",
                "ffff00ff",
                "00ff00ff",
                "00ffffff",
                "0000ffff"
            });

        Magick::Image img;
        img = identicon.generate("55502f40dc8b7c769880b10874abc9d0");
        img.write("identicon_example_libravatar.png");
    }
    else
    {
        cout << "The algorithm \"" << algorithm << "\" is not known.\n";
        return 1;
    }
    return 0;
}
