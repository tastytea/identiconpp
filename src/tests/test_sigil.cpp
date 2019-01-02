#include <catch.hpp>
#include <string>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

using std::string;
#include <iostream>

SCENARIO("sigil: Correct placement")
{
    GIVEN("An identicon instance with 2x2 dots")
    {
        Identiconpp identicon(2, 2, Identiconpp::algorithm::sigil);
        Magick::Image img;
        Magick::Color black("#000000ff");
        Magick::Color white("#ffffffff");

        WHEN("Digest is \"000\"")
        {
            img = identicon.generate("000", 2);
            THEN("Is completely white")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
                REQUIRE(img.pixelColor(0, 1) == white);
                REQUIRE(img.pixelColor(1, 0) == white);
                REQUIRE(img.pixelColor(1, 1) == white);
            }
        }

        WHEN("Digest is \"fff\"")
        {
            img = identicon.generate("fff", 2);
            THEN("Is completely black")
            {
                REQUIRE(img.pixelColor(0, 0) == black);
                REQUIRE(img.pixelColor(0, 1) == black);
                REQUIRE(img.pixelColor(1, 0) == black);
                REQUIRE(img.pixelColor(1, 1) == black);
            }
        }

        WHEN("Digest is \"007\"")
        {
            // 0000 0000 0111 = 00
            //                  11
            img = identicon.generate("007", 2);
            THEN("Produces white pixel at 0x0")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
            }
            THEN("Produces white pixel at 1x0")
            {
                REQUIRE(img.pixelColor(1, 0) == white);
            }
            THEN("Produces black pixel at 1x0")
            {
                REQUIRE(img.pixelColor(0, 1) == black);
            }
            THEN("Produces black pixel at 1x1")
            {
                REQUIRE(img.pixelColor(1, 1) == black);
            }
        }

        WHEN("Digest is \"008\"")
        {
            // 0000 0000 1000 = 11
            //                  00
            img = identicon.generate("008", 2);
            THEN("Produces black pixel at 0x0")
            {
                REQUIRE(img.pixelColor(0, 0) == black);
            }
            THEN("Produces black pixel at 1x0")
            {
                REQUIRE(img.pixelColor(1, 0) == black);
            }
            THEN("Produces white pixel at 1x0")
            {
                REQUIRE(img.pixelColor(0, 1) == white);
            }
            THEN("Produces white pixel at 1x1")
            {
                REQUIRE(img.pixelColor(1, 1) == white);
            }
        }
    }
}

SCENARIO("sigil: Correct color")
{
    GIVEN("An identicon instance with 5 foreground colors")
    {
        Identiconpp identicon(1, 1, Identiconpp::algorithm::sigil,
                              "ffffffff",
                              {
                                "ff0000ff",
                                "ffff00ff",
                                "00ff00ff",
                                "00ffffff",
                                "0000ffff"
                              });
        Magick::Image img;
        Magick::Color white("#ffffffff");
        Magick::Color red("#ff0000ff");
        Magick::Color yellow("#ffff00ff");
        Magick::Color green("#00ff00ff");
        Magick::Color cyan("#00ffffff");
        Magick::Color blue("#0000ffff");

        WHEN("Digest is \"000\"")
        {   // 0000 0000 0000
            img = identicon.generate("000", 1);
            THEN("Is white")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
            }
        }

        WHEN("Digest is \"008\"")
        {   // 0000 0000 1000
            img = identicon.generate("008", 1);
            THEN("Is red")
            {
                REQUIRE(img.pixelColor(0, 0) == red);
            }
        }

        WHEN("Digest is \"108\"")
        {   // 0001 0000 1000
            img = identicon.generate("108", 1);
            THEN("Is yellow")
            {
                REQUIRE(img.pixelColor(0, 0) == yellow);
            }
        }

        WHEN("Digest is \"208\"")
        {   // 0010 0000 1000
            img = identicon.generate("208", 1);
            THEN("Is green")
            {
                REQUIRE(img.pixelColor(0, 0) == green);
            }
        }

        WHEN("Digest is \"308\"")
        {   // 0011 0000 1000
            img = identicon.generate("308", 1);
            THEN("Is cyan")
            {
                REQUIRE(img.pixelColor(0, 0) == cyan);
            }
        }

        WHEN("Digest is \"408\"")
        {   // 0100 0000 1000
            img = identicon.generate("408", 1);
            THEN("Is blue")
            {
                REQUIRE(img.pixelColor(0, 0) == blue);
            }
        }
    }
}
