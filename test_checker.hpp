#ifndef TEST_CHECKER_HPP
#define TEST_CHECKER_HPP
#include "checker.hpp"

void testBMS(BMS::compositeValidator* validatorsObj);
void testTemperatureParam(BMS::compositeValidator* validatorsObj);
void testSocParam(BMS::compositeValidator* validatorsObj);
void testRocParam(BMS::compositeValidator* validatorsObj);
void setParamValues(BMS::compositeValidator* validatorsObj, float temp, float soc, float roc);
void testIsBatteryOkay(BMS::compositeValidator* validatorsObj, bool expectedResult);

#endif