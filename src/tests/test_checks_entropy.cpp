#include <catch.hpp>
#include <string>
#include <vector>
#include <exception>
#include "identiconpp.hpp"

using std::string;

class Testiconpp : private Identiconpp
{
public:
    explicit Testiconpp(const uint8_t columns, const uint8_t rows,
                        const Identiconpp::algorithm &type,
                        const vector<string> &foreground = { "000000ff" })
    : Identiconpp(columns, rows, type, "ffffffff", foreground) {};

    bool test_check_entropy(const string &digest)
    {
        try
        {
            check_entropy(digest, _type);
        }
        catch (const std::exception &e)
        {
            return false;
        }
        return true;
    }
};

SCENARIO("Entropy checks: ltr_symmetric", "[checks][ltr_symmetric]")
{
    WHEN("An Identiconpp instance with 1x3 dots")
    {
        Testiconpp testicon(1, 3, Identiconpp::algorithm::ltr_symmetric);
        THEN("Required entropy is <= 4")
        {
            REQUIRE(testicon.test_check_entropy("f"));
        }
    }

    WHEN("An Identiconpp instance with 14x1 dots")
    {
        Testiconpp testicon(14, 1, Identiconpp::algorithm::ltr_symmetric);
        THEN("Required entropy is <= 8")
        {
            REQUIRE(testicon.test_check_entropy("ff"));
        }
    }

    WHEN("An Identiconpp instance with 255x255 dots")
    {
        Testiconpp testicon(255, 255, Identiconpp::algorithm::ltr_symmetric);
        THEN("Required entropy is <= 32644")
        {
            string digest(8161, 'c');
            REQUIRE(testicon.test_check_entropy(digest));
        }
    }

    WHEN("An Identiconpp instance with 7 colors")
    {
        std::vector<string> colors(7, "000000ff");
        Testiconpp testicon(1, 1, Identiconpp::algorithm::ltr_symmetric,
                            colors);
        THEN("Required entropy is <= 4")
        {
            REQUIRE(testicon.test_check_entropy("f"));
        }
    }

    WHEN("An Identiconpp instance with 524287 colors")
    {
        std::vector<string> colors(524287, "000000ff");
        Testiconpp testicon(1, 1, Identiconpp::algorithm::ltr_symmetric,
                            colors);
        THEN("Required entropy is <= 20")
        {
            REQUIRE(testicon.test_check_entropy("fffff"));
        }
    }
}

SCENARIO("Entropy checks: ltr_asymmetric", "[checks][ltr_asymmetric]")
{
    WHEN("An Identiconpp instance with 3x1 dots")
    {
        Testiconpp testicon(3, 1, Identiconpp::algorithm::ltr_asymmetric);
        THEN("Required entropy is <= 4")
        {
            REQUIRE(testicon.test_check_entropy("f"));
        }
    }

    WHEN("An Identiconpp instance with 14x1 dots")
    {
        Testiconpp testicon(1, 7, Identiconpp::algorithm::ltr_asymmetric);
        THEN("Required entropy is <= 8")
        {
            REQUIRE(testicon.test_check_entropy("ff"));
        }
    }

    WHEN("An Identiconpp instance with 255x255 dots")
    {
        Testiconpp testicon(255, 255, Identiconpp::algorithm::ltr_asymmetric);
        THEN("Required entropy is <= 65028")
        {
            string digest(16257, 'c');
            REQUIRE(testicon.test_check_entropy(digest));
        }
    }

    WHEN("An Identiconpp instance with 7 colors")
    {
        std::vector<string> colors(7, "000000ff");
        Testiconpp testicon(1, 1, Identiconpp::algorithm::ltr_asymmetric,
                            colors);
        THEN("Required entropy is <= 4")
        {
            REQUIRE(testicon.test_check_entropy("f"));
        }
    }

    WHEN("An Identiconpp instance with 524287 colors")
    {
        std::vector<string> colors(524287, "000000ff");
        Testiconpp testicon(1, 1, Identiconpp::algorithm::ltr_asymmetric,
                            colors);
        THEN("Required entropy is <= 20")
        {
            REQUIRE(testicon.test_check_entropy("fffff"));
        }
    }
}

SCENARIO("Entropy checks: sigil", "[checks][sigil]")
{
    WHEN("An Identiconpp instance with 4x2 dots")
    {
        Testiconpp testicon(4, 2, Identiconpp::algorithm::sigil);
        THEN("Required entropy is <= 12")
        {
            REQUIRE(testicon.test_check_entropy("fff"));
        }
    }

    WHEN("An Identiconpp instance with 4x4 dots")
    {
        Testiconpp testicon(4, 4, Identiconpp::algorithm::sigil);
        THEN("Required entropy is <= 16")
        {
            REQUIRE(testicon.test_check_entropy("ffff"));
        }
    }

    WHEN("An Identiconpp instance with 255x255 dots")
    {
        Testiconpp testicon(255, 255, Identiconpp::algorithm::sigil);
        THEN("Required entropy is <= 32644")
        {
            string digest(8162, 'c');
            REQUIRE(testicon.test_check_entropy(digest));
        }
    }
}
