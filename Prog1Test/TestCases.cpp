#define CATCH_CONFIG_MAIN
#pragma pack(1)
#include "..\\prog1\\functions.h"
#include "..\\catch.hpp"

using namespace std;

TEST_CASE("test isNameOrCityError")
{
    char city[] = "Rapid City";
    char city1[] = "Rapid.R City";
    char cityb1[] = "4apid City";
    char cityb2[] = "Rapid Cit8";


    SECTION("TestValidString")
    {
        CHECK(isNameOrCityError(city) == false);
        CHECK(isNameOrCityError(city1) == false);
        CHECK(isNameOrCityError(cityb1) == true);
        CHECK(isNameOrCityError(cityb2) == true);
    }
}
TEST_CASE("test isAddressError")
{
    char city[] = "Rapid City";
    char city1[] = "Rapid.R City";
    char city2[] = "4apid City";
    char city3[] = "Rapid Cit8";
    char city4[] = "Rapid Cit8#";
    char city5[] = "Rapid Cit8%";


    SECTION("TestValidString")
    {
        CHECK(isAddressError(city) == false);
        CHECK(isAddressError(city1) == false);
        CHECK(isAddressError(city2) == false);
        CHECK(isAddressError(city3) == false);
        CHECK(isAddressError(city4) == false);
        CHECK(isAddressError(city5) == true);
    }
}

TEST_CASE("test isStateError")
{
    char city[] = "SD";
    char city1[] = "Sd";
    char city2[] = "sd";
    char city3[] = "sD";
    char city4[] = "RC";
    char city5[] = "rC";

    SECTION("TestValidString")
    {
        CHECK(isStateError(city) == false);
        CHECK(isStateError(city1) == false);
        CHECK(isStateError(city2) == true);
        CHECK(isStateError(city3) == true);
        CHECK(isStateError(city4) == true);
        CHECK(isStateError(city5) == true);
        
    }
}
TEST_CASE("test isZipCodeError")
{
    int num = 4324;
    int num1 = 7589325;
    bool errors[] = { false };

    isZipCodeError(num, errors);
    isZipCodeError(num1, errors);

    SECTION("TestValidString")
    {
        CHECK(errors[5] == false);
        CHECK(errors[6] == false);
        CHECK(errors[7] == false);
    }
}