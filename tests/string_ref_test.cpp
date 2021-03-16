#include <nitro/lang/string_ref.hpp>

#include <catch2/catch.hpp>

#include <iostream>

void test_func(const std::string&)
{
}

TEST_CASE("String ref works", "[lang]")
{
    std::string str("Hello World");

    nitro::lang::string_ref sr = str;

    SECTION("can be printed to stdout")
    {
        std::cout << sr << std::endl;
    }

    SECTION("can implicitly convert to std::string")
    {
        test_func(str);
    }

    SECTION("can be compared to a string")
    {
        REQUIRE(str == sr);
    }

    SECTION("can be nullptr")
    {
        nitro::lang::string_ref sr2(nullptr);

        REQUIRE(sr2.empty() == true);
    }

    SECTION("can be used with string literals")
    {
        nitro::lang::string_ref sr2("literally a string literal");

        REQUIRE(std::string("literally a string literal") == sr2);
    }
}
