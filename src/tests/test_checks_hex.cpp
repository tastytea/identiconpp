#include <catch.hpp>
#include <string>
#include <vector>
#include <exception>
#include "identiconpp.hpp"

using std::string;

class Testiconpp : private Identiconpp
{
public:
    explicit Testiconpp()
    : Identiconpp(1, 1) {};

    bool test_check_not_hex(const char &c)
    {
        return not_hex(c);
    }
};

SCENARIO("Hex checker check", "[checks][hex]")
{
    GIVEN("Identiconpp instance")
    {
        Testiconpp testicon;

        WHEN("digit is 0-9")
        {
            THEN("Return false")
            {
                for (char c = 0x30; c <= 0x39; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c) == false);
                }
            }
        }

        WHEN("digit is A-F")
        {
            THEN("Return false")
            {
                for (char c = 0x41; c <= 0x46; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c) == false);
                }
            }
        }

        WHEN("digit is a-f")
        {
            THEN("Return false")
            {
                for (char c = 0x61; c <= 0x66; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c) == false);
                }
            }
        }

        WHEN("digit is 0x00 - 0x29")
        {
            Testiconpp testicon;
            THEN("Return true")
            {
                for (char c = 0x00; c <= 0x29; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c));
                }
            }
        }

        WHEN("digit is 0x3a - 0x40")
        {
            Testiconpp testicon;
            THEN("Return true")
            {
                for (char c = 0x3a; c <= 0x40; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c));
                }
            }
        }

        WHEN("digit is 0x47 - 0x60")
        {
            Testiconpp testicon;
            THEN("Return true")
            {
                for (char c = 0x47; c <= 0x60; ++c)
                {
                    REQUIRE(testicon.test_check_not_hex(c));
                }
            }
        }

        WHEN("digit is 0x67 - 0x7f")
        {
            Testiconpp testicon;
            THEN("Return true")
            {
                // We need to use an unsigned char to prevent overflowing
                for (unsigned char c = 0x67; c <= 0x7f; ++c)
                {
                    INFO("c=" << (int)c);
                    REQUIRE(testicon.test_check_not_hex(c));
                }
            }
        }
    }
}
