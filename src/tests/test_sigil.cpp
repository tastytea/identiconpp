#include <catch.hpp>
#include <string>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

using std::string;
#include <iostream>

SCENARIO("sigil")
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
