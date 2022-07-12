#include <iostream>
#include <assert.h>
#include "test_checker.hpp"

void testBMS(BMS::compositeValidator* validatorsObj)
{
    testTemperatureParam(validatorsObj);
    testSocParam(validatorsObj);
    testRocParam(validatorsObj);
}
void testTemperatureParam(BMS::compositeValidator* validatorsObj)
{
    setParamValues(validatorsObj, -10.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 0.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 3.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 20.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 40.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 45.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 50.0, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);
}

void testSocParam(BMS::compositeValidator* validatorsObj)
{
    setParamValues(validatorsObj, 25, -30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 0.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 20.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 24.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 50.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 76.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 80.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 200.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, false);
}

void testRocParam(BMS::compositeValidator* validatorsObj)
{
    setParamValues(validatorsObj, 25, 30.0f, -10.0f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 30.0f, 0.0f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 30.0f, 0.1f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 30.0f, 0.15f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 30.0f, 0.5f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 30.0f, 0.65f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 30.0f, 0.7f);
    testIsBatteryOkay(validatorsObj, true);

    setParamValues(validatorsObj, 25, 30.0f, 0.8f);
    testIsBatteryOkay(validatorsObj, false);

    setParamValues(validatorsObj, 25, 30.0f, 1.0f);
    testIsBatteryOkay(validatorsObj, false);
}
void setParamValues(BMS::compositeValidator* validatorsObj, float temp, float soc, float roc)
{
    validatorsObj->setValue(BMS::ParameterCheck::TEMPERTURE, temp);
    validatorsObj->setValue(BMS::ParameterCheck::STATEOFCHARGE, soc);
    validatorsObj->setValue(BMS::ParameterCheck::CHARGERATE, roc);
}
void testIsBatteryOkay(BMS::compositeValidator* validatorsObj, bool expectedResult)
{
    assert(BMS::isBatteryOkay(validatorsObj) == expectedResult);
}
