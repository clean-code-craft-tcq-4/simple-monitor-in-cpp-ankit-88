
#include <iostream>
#include <vector>
#include "checker.hpp"
#include "test_checker.hpp"


BMS::Languages BMS::prefferedlanguage = BMS::Languages::English;
bool BMS::isBatteryOkay(BMS::compositeValidator* CompositeValidators)
{
   return CompositeValidators->isParamOkay();
}        
int main()
{
    BMS::compositeValidator* validators = new BMS::compositeValidator();
    
    //Checking language support
    BMS::prefferedlanguage = BMS::Languages::English;
    validators->add(new BMS::TemperatureValidator(25.0f));
    validators->add(new BMS::SocValidator(30.0f));
    validators->add(new BMS::RocValidator(0.5));
    isBatteryOkay(validators);
    validators->display();
   
    BMS::prefferedlanguage = BMS::Languages::German;
    validators->setValue(BMS::ParameterCheck::TEMPERTURE, 3);
    validators->setValue(BMS::ParameterCheck::CHARGERATE, 0.7f);
    validators->setValue(BMS::ParameterCheck::STATEOFCHARGE, 30);
    isBatteryOkay(validators);
    validators->display();

    //Calling testfunction to validate IsBatteryOkay result for differnt values.
    testBMS(validators);
   
    return 0;
}
