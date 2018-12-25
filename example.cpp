/*  This file is part of identiconpp.
 *  Public Domain / CC-0
 */

#include <iostream>
#include <string>
#include "identiconpp.hpp"

using std::cout;
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

    Identiconpp identicon(5, 5, "ffffffff", {"000000ff", "000000"});

    return 0;
}
