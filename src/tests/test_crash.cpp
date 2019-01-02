#include <catch.hpp>
#include <string>
#include <exception>
#include <vector>
#include <Magick++/Image.h>
#include "identiconpp.hpp"

using std::string;

SCENARIO("Please do not crash")
{
    GIVEN("The digest: sha256(test@example.com)")
    {
        string digest = "973dfe463ec85785f5f95af5ba3906ee"
                        "db2d931c24e69824a89ea65dba4e813b";
        bool exception = false;

        WHEN("256 bits of entropy is required")
        {
            try
            {
                Identiconpp identicon(18, 28,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff",
                                      {
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff"
                                      });
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Does not crash")
            {
                REQUIRE(exception == false);
            }
        }

        WHEN("sigil is fed exactly 8 bit of colors")
        {
            try
            {
                std::vector<string> colors(256, "000000ff");
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::sigil,
                                      "ffffffff", colors);
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Does not crash")
            {
                REQUIRE(exception == false);
            }
        }

        WHEN("colors with uppercase hex digits")
        {
            try
            {
                Identiconpp identicon(1, 1, Identiconpp::algorithm::sigil,
                                      "FF00FFFF");
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Does not crash")
            {
                REQUIRE(exception == false);
            }
        }
    }
}

SCENARIO("Please crash")
{
    GIVEN("The digest: sha256(test@example.com)")
    {
        string digest = "973dfe463ec85785f5f95af5ba3906ee"
                        "db2d931c24e69824a89ea65dba4e813b";
        bool exception = false;

        WHEN("257 bits of entropy is required")
        {
            try
            {
                Identiconpp identicon(18, 28,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff",
                                      {
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff", "000000ff", "000000ff",
                                          "000000ff"
                                      });
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("sigil is fed more than 8 bit of colors")
        {
            try
            {
                std::vector<string> colors(257, "000000ff");
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::sigil,
                                      "ffffffff", colors);
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("background color has too many digits")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffffa");
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("background color has not enough digits")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "fffffff");
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("Foreground color has too many digits")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff", { "000000ffa"});
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("Foreground color has not enough digits")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff", { "000000f" });
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("No foreground color")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff", {});
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("Non-hex digits in background color")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffgf");
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }

        WHEN("Non-hex digits in foreground color")
        {
            try
            {
                Identiconpp identicon(1, 1,
                                      Identiconpp::algorithm::ltr_symmetric,
                                      "ffffffff", { "g00000ff" });
                identicon.generate(digest);
            }
            catch (const std::exception &e)
            {
                exception = true;
            }
            THEN("Crashes")
            {
                REQUIRE(exception == true);
            }
        }
    }
}
