#include <assert.h>
#include <iostream>
#include "checker.hpp"
#include "test_checker.hpp"
using namespace std;
namespace BMS
{
    const int numberOfValidation = 3;
    const string errorReason[] = { "Temperature", "State of Charge", "Rate Of charge" };

    void printMessage(int value)
    {
        std::cout << errorReason[value] << " is out of range" << std::endl;
    }
    void fillMemberVarValues(Validate* BaseClassArray[], float temperature, float soc, float chargeRate)
    {
        BaseClassArray[0]->paramValue = temperature;
        BaseClassArray[1]->paramValue = soc;
        BaseClassArray[2]->paramValue = chargeRate;
    }
    bool batteryIsOk(Validate* BaseClassArray[], float temperature, float soc, float chargeRate) {
        bool isParamInRange = false;
        fillMemberVarValues(BaseClassArray, temperature, soc, chargeRate);
        for (int index = 0; index < BMS::numberOfValidation; index++)
        { 
             isParamInRange = BaseClassArray[index]->isParamOkay();
             if (!isParamInRange)
             {
                 printMessage(index);
                 return false;
             }
        }
        return true;
    }
}
    static void fillBaseClassArray(BMS::Validate* validateArrayPtr[])
    {
        static BMS::ValidateTemp tempClassObj = BMS::ValidateTemp();
        static BMS::ValidateSOC socClassObj =  BMS::ValidateSOC();
        static BMS::ValidateROC rocpClassObj = BMS::ValidateROC();
        validateArrayPtr[0] = &tempClassObj;
        validateArrayPtr[1] = &socClassObj;
        validateArrayPtr[2] = &rocpClassObj;

    }
    int main() {
        BMS::Validate* ValidateClsArray[BMS::numberOfValidation];
        fillBaseClassArray(ValidateClsArray);
       // bool ret = BMS::batteryIsOk(ValidateClsArray, 25, 50, 0.5);
       // std::cout << clsarray[0] << " " << clsarray[1] << " "<< clsarray[2];
       // assert(BMS::batteryIsOk(ValidateClsArray,25, 70, 0.7) == true);
        //assert(BMS::batteryIsOk(ValidateClsArray,50, 85, 0) == false);

        testBatteryIsOk(ValidateClsArray);
    }

