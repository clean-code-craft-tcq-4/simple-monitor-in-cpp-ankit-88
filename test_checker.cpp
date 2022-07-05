#include <iostream>
#include <assert.h>
#include "test_bms.hpp"

static void testBatteryTemp(BMS::Validate* BaseClassPtr[], float temp, bool expectedValue);
static void testBatteryStateOfCharge(BMS::Validate* BaseClassPtr[], float soc, bool expectedValue);
static void testBatteryRateOfCharge(BMS::Validate* BaseClassPtr[], float roc, bool expectedValue);
void testBatteryIsOk(BMS::Validate* BaseClassArray[])
{
	testBatteryTemp(BaseClassArray, -10, false);
	testBatteryTemp(BaseClassArray, 0, false);
	testBatteryTemp(BaseClassArray, 5,true);
	testBatteryTemp(BaseClassArray, 20,true);
	testBatteryTemp(BaseClassArray, 45,false);
	testBatteryTemp(BaseClassArray, 50,false);

	testBatteryStateOfCharge(BaseClassArray, -10, false);
	testBatteryStateOfCharge(BaseClassArray, 0, false);
	testBatteryStateOfCharge(BaseClassArray, 20, false);
	testBatteryStateOfCharge(BaseClassArray, 30, true);
	testBatteryStateOfCharge(BaseClassArray, 50, true);
	testBatteryStateOfCharge(BaseClassArray, 80, false);
	testBatteryStateOfCharge(BaseClassArray, 100, false);

	testBatteryRateOfCharge(BaseClassArray, -10.0, false);
	testBatteryRateOfCharge(BaseClassArray, 0.0, false);
	testBatteryRateOfCharge(BaseClassArray, 0.1, true);
	testBatteryRateOfCharge(BaseClassArray, 0.5, true);
	testBatteryRateOfCharge(BaseClassArray, 0.8, false);
	testBatteryRateOfCharge(BaseClassArray, 1.0, false);

}

void testFillMemberVarValues(BMS::Validate* BaseClassArray[], float temperature, float soc, float chargeRate)
{
	BMS::fillMemberVarValues(BaseClassArray, 10, 20, 0.8);
	assert(BaseClassArray[0]->paramValue == 10);
	assert(BaseClassArray[1]->paramValue == 20);
	assert(BaseClassArray[0]->paramValue == 0.8);

	BMS::fillMemberVarValues(BaseClassArray, 4.5, 50, 0.5);
	assert(BaseClassArray[0]->paramValue == 4.5);
	assert(BaseClassArray[1]->paramValue == 50);
	assert(BaseClassArray[0]->paramValue == 0.5);

	BMS::fillMemberVarValues(BaseClassArray, -25, -100, .1);
	assert(BaseClassArray[0]->paramValue == -25);
	assert(BaseClassArray[1]->paramValue == -100);
	assert(BaseClassArray[0]->paramValue == 0.1);
	
}

static void testBatteryTemp(BMS::Validate* BaseClassPtr[], float temperature,bool expectedValue)
{
	assert(BMS::batteryIsOk(BaseClassPtr, temperature, 50, 0.5) == expectedValue);

}
static void testBatteryStateOfCharge(BMS::Validate* BaseClassPtr[], float soc, bool expectedValue)
{
	assert(BMS::batteryIsOk(BaseClassPtr, 25, soc, 0.5) == expectedValue);
}
static void testBatteryRateOfCharge(BMS::Validate* BaseClassPtr[], float roc, bool expectedValue)
{
	assert(BMS::batteryIsOk(BaseClassPtr, 25, 50, roc) == expectedValue);
}