#include <catch.hpp>
#include <string>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

using std::string;

SCENARIO("ltr_symmetric: Correct placement", "[ltr_symmetric]")
{
    GIVEN("An identiconpp instance with 2x2 dots")
    {
        Identiconpp identicon(2, 2, Identiconpp::algorithm::ltr_symmetric);
        Magick::Image img;
        Magick::Color black("#000000ff");
        Magick::Color white("#ffffffff");

        WHEN("Digest is \"0\"")
        {
            img = identicon.generate("0", 2);
            THEN("Is completely white")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
                REQUIRE(img.pixelColor(0, 1) == white);
                REQUIRE(img.pixelColor(1, 0) == white);
                REQUIRE(img.pixelColor(1, 1) == white);
            }
        }

        WHEN("Digest is \"f\"")
        {
            img = identicon.generate("f", 2);
            THEN("Is completely black")
            {
                REQUIRE(img.pixelColor(0, 0) == black);
                REQUIRE(img.pixelColor(0, 1) == black);
                REQUIRE(img.pixelColor(1, 0) == black);
                REQUIRE(img.pixelColor(1, 1) == black);
            }
        }

        WHEN("Digest is \"7\"")
        {
            // 0111 = 00
            //        11
            img = identicon.generate("7", 2);
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

        WHEN("Digest is \"8\"")
        {
            // 1000 = 11
            //        00
            img = identicon.generate("8", 2);
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

SCENARIO("ltr_symmetric: Correct color", "[ltr_symmetric]")
{
    GIVEN("An identiconpp instance with 5 foreground colors")
    {
        Identiconpp identicon(1, 1, Identiconpp::algorithm::ltr_symmetric,
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

        WHEN("Digest is \"0\"")
        {   // 0000
            img = identicon.generate("0", 1);
            THEN("Is white")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
            }
        }

        WHEN("Digest is \"8\"")
        {   // 1000
            img = identicon.generate("8", 1);
            THEN("Is red")
            {
                REQUIRE(img.pixelColor(0, 0) == red);
            }
        }

        WHEN("Digest is \"9\"")
        {   // 1001
            img = identicon.generate("9", 1);
            THEN("Is yellow")
            {
                REQUIRE(img.pixelColor(0, 0) == yellow);
            }
        }

        WHEN("Digest is \"a\"")
        {   // 1010
            img = identicon.generate("a", 1);
            THEN("Is green")
            {
                REQUIRE(img.pixelColor(0, 0) == green);
            }
        }

        WHEN("Digest is \"b\"")
        {   // 1011
            img = identicon.generate("b", 1);
            THEN("Is cyan")
            {
                REQUIRE(img.pixelColor(0, 0) == cyan);
            }
        }

        WHEN("Digest is \"c\"")
        {   // 1100
            img = identicon.generate("c", 1);
            THEN("Is blue")
            {
                REQUIRE(img.pixelColor(0, 0) == blue);
            }
        }
    }
}
