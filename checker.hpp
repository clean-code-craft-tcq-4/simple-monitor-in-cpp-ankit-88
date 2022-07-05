#ifndef CHECKER_HPP
#define CHECKER_HPP

namespace BMS
{
    class Validate
    {
    public:
        float paramValue;
        bool issueNotFound;

       virtual bool isParamOkay() = 0;

    };

    class ValidateTemp : public Validate
    {
    public:
        bool isParamOkay()
        {
            if (paramValue > 0 && paramValue < 45)
            {
                this->issueNotFound = true;

            }
            else
            {
                this->issueNotFound = false;

            }
            return this->issueNotFound;
        }
    };

    class ValidateSOC : public Validate
    {
    public:
        bool isParamOkay()
        {
            if (paramValue > 20 && paramValue < 80)
            {
                this->issueNotFound = true;
            }
            else
            {
                this->issueNotFound = false;
            }
            return this->issueNotFound;
        }

    };

    class ValidateROC : public Validate
    {
    public:
        bool isParamOkay()
        {
            if (paramValue > 0 && paramValue < 0.8)
            {
                this->issueNotFound = true;
            }
            else
            {
                this->issueNotFound = false;
            }
            return this->issueNotFound;
        }
    };

    bool batteryIsOk(Validate* BaseClassArray[], float temperature, float soc, float chargeRate);
    void fillMemberVarValues(Validate* BaseClassArray[], float temperature, float soc, float chargeRate);
}  


#endif