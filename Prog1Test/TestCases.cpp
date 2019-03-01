#define CATCH_CONFIG_MAIN
#pragma pack(1)
#include "..\\prog1\\functions.h"
#include "..\\catch.hpp"

using namespace std;

TEST_CASE("Prog1 functions")
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