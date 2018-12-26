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
    }
    else
    {
        cout << "The algorithm \"" << algorithm << "\" is not known.\n";
        return 1;
    }

    Identiconpp identicon(5, 5, 0xffffffff,
                        {
                            0x000000ff,
                            0xff0000ff,
                            0xffff00ff,
                            0x00ff00ff,
                            0x00ffffff,
                            0x0000ffff
                        });
    Identiconpp::Image image;
    image = identicon.generate("2b7dd5def082abfca556d9e8feb1fc29", Identiconpp::identicon_type::simple);
    cout.flush();   // We need to flush before we use /dev/stdout directly.
    image.data.write("/dev/stdout");
    return 0;
}
