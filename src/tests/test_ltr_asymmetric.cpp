#include <catch2/catch.hpp>
#include <string>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

using std::string;
#include <iostream>

SCENARIO("ltr_asymmetric")
{
    GIVEN("An identicon instance with 2x2 dots")
    {
        Identiconpp identicon(2, 2, Identiconpp::algorithm::ltr_asymmetric);
        Magick::Image img;
        Magick::Color black("#000000ff");
        Magick::Color white("#ffffffff");

        WHEN("Digest is \"00\"")
        {
            img = identicon.generate("00", 2);
            THEN("Is completely white")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
                REQUIRE(img.pixelColor(0, 1) == white);
                REQUIRE(img.pixelColor(1, 0) == white);
                REQUIRE(img.pixelColor(1, 1) == white);
            }
        }

        WHEN("Digest is \"ff\"")
        {
            img = identicon.generate("ff", 2);
            THEN("Is completely black")
            {
                REQUIRE(img.pixelColor(0, 0) == black);
                REQUIRE(img.pixelColor(0, 1) == black);
                REQUIRE(img.pixelColor(1, 0) == black);
                REQUIRE(img.pixelColor(1, 1) == black);
            }
        }

        WHEN("Digest is \"70\"")
        {
            // 0111 0000 = 01
            //             11
            img = identicon.generate("70", 2);
            THEN("Produces white pixel at 0x0")
            {
                REQUIRE(img.pixelColor(0, 0) == white);
            }
            THEN("Produces black pixel at 1x0")
            {
                REQUIRE(img.pixelColor(1, 0) == black);
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

        WHEN("Digest is \"80\"")
        {
            // 1000 0000 = 10
            //             00
            img = identicon.generate("80", 2);
            THEN("Produces black pixel at 0x0")
            {
                REQUIRE(img.pixelColor(0, 0) == black);
            }
            THEN("Produces white pixel at 1x0")
            {
                REQUIRE(img.pixelColor(1, 0) == white);
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
