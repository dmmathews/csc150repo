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
    int num = 224151219;
    int num1 = 32769;
    bool errors[10] = { false };
    bool errors1[10] = { false };

    isZipCodeError(num, errors);
    isZipCodeError(num1, errors1);

    SECTION("TestValidString")
    {
        CHECK(errors[5] == false);
        CHECK(errors[6] == false);
        CHECK(errors1[5] == true);
        CHECK(errors1[6] == true);
    }
}
TEST_CASE("test isBirthDateError")
{
    int num = 4324;
    int num1 = 7851469;
    bool errors[23] = { false };
    bool errors1[23] = { false };

    isBirthDateError(num, errors);
    isBirthDateError(num1, errors1);

    SECTION("TestValidString")
    {
        CHECK(errors[7] == false);
        CHECK(errors[8] == true);
        CHECK(errors[9] == true);
        CHECK(errors1[7] == false);
        CHECK(errors1[8] == false);
        CHECK(errors1[9] == false);
    }
}
TEST_CASE("test isLicenseDateError")
{
    int num = 4324;
    int num1 = 7851469;
    bool errors[23] = { false };
    bool errors1[23] = { false };

    isLicenseDateError(num, errors);
    isLicenseDateError(num1, errors1);

    SECTION("TestValidString")
    {
        CHECK(errors[10] == false);
        CHECK(errors[11] == true);
        CHECK(errors[12] == true);
        CHECK(errors1[10] == false);
        CHECK(errors1[11] == false);
        CHECK(errors1[12] == false);
    }
}
TEST_CASE("test isRadioClassError")
{
    char ch = 'n';
    char ch1 = 'N';
    char ch2 = 'L';
    char ch3 = 'P';
    char ch4 = 't';
    char ch5 = 'T';
    char ch6 = 'h';

    SECTION("TestValidString")
    {
        CHECK(isRadioClassError(ch) == false);
        CHECK(isRadioClassError(ch1) == false);
        CHECK(isRadioClassError(ch2) == true);
        CHECK(isRadioClassError(ch3) == false);
        CHECK(isRadioClassError(ch4) == false);
        CHECK(isRadioClassError(ch5) == false);
        CHECK(isRadioClassError(ch6) == true);
    }
}
TEST_CASE("test isCallSignError")
{
    char ch[6] = "nA1da";
    char ch1[6] = "Na2da";
    char ch2[6] = "KA9PA";
    char ch3[6] = "kA9PA";
    char ch4[6] = "KIDDI";
    char ch5[6] = "WO\0Ld";
    bool errors[23] = { false };
    bool errors1[23] = { false };
    bool errors2[23] = { false };
    bool errors3[23] = { false };
    bool errors4[23] = { false };
    bool errors5[23] = { false };

    isCallSignError(ch, errors);
    isCallSignError(ch1, errors1);
    isCallSignError(ch2, errors2);
    isCallSignError(ch3, errors3);
    isCallSignError(ch4, errors4);
    isCallSignError(ch5, errors5);

    SECTION("nA2da")
    {
        CHECK(errors[18] == true);
        CHECK(errors[19] == true);
        CHECK(errors[20] == false);
        CHECK(errors[21] == true);
    }
    SECTION("Na2da")
    {
        CHECK(errors1[18] == false);
        CHECK(errors1[19] == true);
        CHECK(errors1[20] == false);
        CHECK(errors1[21] == true);
    }
    SECTION("KA9PA")
    {
        CHECK(errors2[18] == false);
        CHECK(errors2[19] == false);
        CHECK(errors2[20] == false);
        CHECK(errors2[21] == false);
    }
    SECTION("kA9PA")
    {
        CHECK(errors3[18] == true);
        CHECK(errors3[19] == false);
        CHECK(errors3[20] == false);
        CHECK(errors3[21] == true);
    }
    SECTION("KIDDI")
    {
        CHECK(errors4[18] == false);
        CHECK(errors4[19] == false);
        CHECK(errors4[20] == true);
        CHECK(errors4[21] == false);
    }
    SECTION("WO\0Ld")
    {
        CHECK(errors5[18] == false);
        CHECK(errors5[19] == true);
        CHECK(errors5[20] == true);
        CHECK(errors5[21] == true);
    }
}


