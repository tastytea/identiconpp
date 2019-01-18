#include <catch.hpp>
#include <string>
#include <exception>
#include <vector>
#include <cstdint>
#include <Magick++/Image.h>
#include "identiconpp_c.h"

using std::string;
using std::uint8_t;
using std::uint64_t;

SCENARIO("C interface", "[C]")
{
    GIVEN("The digest: sha256(test@example.com)")
    {
        char digest[65] = "973dfe463ec85785f5f95af5ba3906ee"
                          "db2d931c24e69824a89ea65dba4e813b";
        const uint8_t padding[2] = { 20, 40 };
        bool success = false;

        WHEN("256 bits of entropy is required")
        {
            const char colors[15][9] =
            {
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff",
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff",
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff"
            };

            success = identiconpp_setup(18, 28,
                                        identiconpp_ltr_symmetric,
                                        "ffffffff",
                                        colors, 15, padding);
            uint64_t len = identiconpp_generate("png", digest, 50);
            if (len == 0)
            {
                success = false;
            }
            if (string(identiconpp_base64()).length() != len)
            {
                success = false;
            }

            THEN("Does not crash")
            {
                REQUIRE(success == true);
            }
        }

        WHEN("257 bits of entropy is required")
        {
            const char colors[16][9] =
            {
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff",
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff",
                "000000ff", "000000ff", "000000ff", "000000ff", "000000ff",
                "000000ff"
            };

            success = identiconpp_setup(18, 28,
                                        identiconpp_ltr_symmetric,
                                        "ffffffff",
                                        colors, 16, padding);
            if (identiconpp_generate("png", digest, 50) == 0)
            {
                success = false;
            }

            THEN("Crashes")
            {
                REQUIRE(success == false);
            }
        }
    }
}
