#ifndef BMS_CYCLOMATIC_HPP
#define BMS_CYCLOMATIC_HPP
#include<iostream>
#include<vector>
namespace BMS
{
	enum class ParameterCheck
	{
		TEMPERTURE , STATEOFCHARGE, CHARGERATE
	};
	enum class ErrorType { LowerLimitBreached, LowerWarningThreshold,  InRange , UpperWarningThershold ,  UpperLimitBreached };
	enum class Languages { English, German};

	extern Languages prefferedlanguage;
	class Parameter_Validators
	{
	public:
		bool m_ParamOkay = 0;
		ErrorType ParamStatus = ErrorType::InRange;
		virtual bool isParamOkay() = 0;
		//virtual bool checkForEarlyWarning() = 0;
		virtual void display() = 0;
		virtual void setValue(float) = 0;
	};

	class TemperatureValidator : public Parameter_Validators
	{
		float Temperature;
		
		bool isTemperatureValidated = false;
		const float Max_Temp = 45.0f;
		const float Min_Temp = 0.0f;
		const float TempLowerWarningThreshold = 4;
		const float TempUpperWarningThreshold = 40;
		const std::vector<float> temperatureBoundaryValues = { Min_Temp,TempLowerWarningThreshold,TempUpperWarningThreshold,Max_Temp };
		const std::string TemperatureErrorMessgesInEnglish[5] = {
		"Alert! Lower Limit of Temperature Breached ",
		"Warning! Approching Lower Temperature Limit ",
		"All is Well! Temperature in Range ",
		"Warning! Approching Upper Temperature Limit",
		"Alert! Upper Limit of Temperature Breached "
		};
		 const std::string TemperatureErrorMessageInGerman[5] = {
			"Alert! Untere Temperaturgrenze überschritten",
			"Warnung! Annäherung an die untere Temperaturgrenze",
			"Alles ist gut! Temperatur im Bereich",
			"Warnung! Annäherung an die obere Temperaturgrenze",
			"Alert! Obere Temperaturgrenze überschritten"
		};
		 std::vector<const std::string*> AllTempErrorMessges;

	public:
		int temp;
		TemperatureValidator(float temp)
		{
			this->Temperature = temp;
			AllTempErrorMessges.push_back(TemperatureErrorMessgesInEnglish);
			AllTempErrorMessges.push_back(TemperatureErrorMessageInGerman);
		}
		bool isParamOkay()
		{
			allocateTempErrorType();
			isTemperatureValidated = true;
			if (this->Temperature > Min_Temp && this->Temperature < Max_Temp)
			{
				m_ParamOkay = 1;
				return true;
			}
			else
			{
				m_ParamOkay = 0;
				return false;
			}
			
		}
		void allocateTempErrorType()
		{
			bool flag = false;
			int errorIndex = 0;
			ParamStatus = static_cast<ErrorType> (temperatureBoundaryValues.size());
			for (errorIndex = 0; errorIndex < temperatureBoundaryValues.size(); errorIndex++)
			{
				if (Temperature <= temperatureBoundaryValues.at(errorIndex))
				{
					ParamStatus = static_cast<ErrorType> (errorIndex);
					flag = true;
					break;
				}
			}
			
			//std::cout << "Allocated enum as : " << int(ParamStatus) <<std::endl;
		}
		/*bool checkForEarlyWarning()
		{
			//out of range value is already checked by isParamOkay() before this call. so only valid value comes in this function. 
			if (this->Temperature < LowerWarningThreshold )
			{
				ParamStatus = ErrorType::LowerWarningThreshold;
				return true;
			}
			else if(this->Temperature > UpperWarningThreshold)
			{
				ParamStatus = ErrorType::UpperWarningThershold;
				return true;
			}
			else
			{
				ParamStatus = ErrorType::InRange;
				return false;
			}
		}*/
		void setValue(float value)
		{
			m_ParamOkay = 0;
			isTemperatureValidated = false;
			this->Temperature = value;
		}
		void display()
		{
			if (isTemperatureValidated == true)
			{
				std::cout << (AllTempErrorMessges.at(static_cast<int>(prefferedlanguage)))[static_cast<int>(ParamStatus)] <<std::endl;
			}
		}
		
	};

	class SocValidator : public Parameter_Validators
	{
		float stateOfCharge;
		bool isSocValidated = false;
		const float Max_Soc = 80;
		const float Min_Soc = 20;
		const float SocLowerWarningThreshold = 24;
		const float SocUpperWarningThreshold = 76;
		const std::vector<float> socBoundaryValues = { Min_Soc,SocLowerWarningThreshold,SocUpperWarningThreshold,Max_Soc };
		const std::string SocErrorMessgesInEnglish[5] = {
		"Alert! Operating Below charge Limit ",
		"Warning! Approching Discharge Limit ",
		"All is Well! Charge state is in Range ",
		"Warning! Approching Peak charge Limit",
		"Alert! Charge is full overcharging battery "
		};
		const std::string SocErrorMessageInGerman[5] = {
		"Alert! Betrieb unterhalb der Ladegrenze",
		"Warnung! Annäherung an die Entladegrenze",
		"Alles ist gut! Ladezustand ist in Reichweite",
		"Warnung! Höchstladungsgrenze nähert sich",
		"Alert! Charge ist eine vollständige Überladung des Akkus"
		};
		std::vector<const std::string*> AllSocErrorMessges;
	public:
		SocValidator(float soc)
		{
			this->stateOfCharge = soc;
			AllSocErrorMessges.push_back(SocErrorMessgesInEnglish);
			AllSocErrorMessges.push_back(SocErrorMessageInGerman);
		}
		bool isParamOkay()
		{
			allocateSocErrorType();
			isSocValidated = true;
			if (this->stateOfCharge > Min_Soc && this->stateOfCharge < Max_Soc)
			{
				m_ParamOkay = 1;
				return true;
			}
			else
			{
				m_ParamOkay = 0;
				return false;
			}
		}

		void allocateSocErrorType()
		{
			bool flag = false;
			int errorIndex = 0;
			ParamStatus = static_cast<ErrorType> (socBoundaryValues.size());
			for (errorIndex = 0; errorIndex < socBoundaryValues.size(); errorIndex++)
			{
				if (stateOfCharge <= socBoundaryValues.at(errorIndex))
				{
					ParamStatus = static_cast<ErrorType> (errorIndex);
					flag = true;
					break;
				}
			}
			
			//std::cout << "Allocated SOC enum as : " << int(ParamStatus) << std::endl;
		}

		void setValue(float value)
		{
			m_ParamOkay = 0;
			isSocValidated = false;
			this->stateOfCharge = value;
		}
		void display()
		{
			if (isSocValidated)
			{
				std::cout << (AllSocErrorMessges.at(static_cast<int>(prefferedlanguage)))[static_cast<int>(ParamStatus)] << std::endl;
			}
		}
		
	};

	class RocValidator : public Parameter_Validators
	{
		float chargeRate;
		bool isRocValidated = false;
		const float Min_Roc = 0.0f;   // CHARGE REATE CANNOT BE BELOW ZERO
		const float Max_Roc = 0.8f;
		const float RocLowerWarningThreshold = 0.15f;
		const float RocUpperWarningThreshold = 0.65f;
		const std::vector<float> rocBoundaryValues = { Min_Roc,RocLowerWarningThreshold,RocUpperWarningThreshold,Max_Roc };
		const std::string RocErrorMessgesInEnglish[5] = {
		"Alert! Battery Reverse charging ",
		"Warning! Charging rate approching zero ",
		"All is Well! Charge rate is in Range ",
		"Warning! Approching Peak charge Rate",
		"Alert! Charge Rate above acceptable limit "
		};
		const std::string RocErrorMessgesInGerman[5] = {
		"Alert! Batterieumkehrladung ",
		"Warnung! Laderate gegen Null ",
		"Alles ist gut! Die Laderate liegt im Bereich ",
		"Warnung! Annäherung an die Spitzenladerate",
		"Alert! Laderate über akzeptablem Limit "
		};
		std::vector<const std::string*> AllRocErrorMessages;
	public:
		RocValidator(float roc)
		{
			
			this->chargeRate = roc;
			AllRocErrorMessages.push_back(RocErrorMessgesInEnglish);
			AllRocErrorMessages.push_back(RocErrorMessgesInGerman);
		}
		bool isParamOkay()
		{
			allocateRocErrorType();
			isRocValidated = true;
			if (this->chargeRate < Max_Roc && this->chargeRate >Min_Roc)
			{
				m_ParamOkay = 1;
				return true;
			}
			else
			{
				m_ParamOkay = 0;
				return false;
			}
		}
		void allocateRocErrorType()
		{
			bool flag = false;
			int errorIndex = 0;
			ParamStatus = static_cast<ErrorType> (rocBoundaryValues.size());
			for (errorIndex = 0; errorIndex < rocBoundaryValues.size(); errorIndex++)
			{
				if (chargeRate <= rocBoundaryValues.at(errorIndex))
				{
					ParamStatus = static_cast<ErrorType> (errorIndex);
					flag = true;
					break;
				}
			}
			
			//std::cout << "Allocated ROC enum as : " << int(ParamStatus) << std::endl;
		}
		void setValue(float value)
		{
			m_ParamOkay = 0;
			isRocValidated = false;
			this->chargeRate = value;
		}
		void display()
		{
			if (isRocValidated)
			{
				std::cout<<(AllRocErrorMessages.at(static_cast<int>(prefferedlanguage)))[static_cast<int>(ParamStatus)]<<std::endl<<std::endl <<std::endl;
			}
		}
	};

	class compositeValidator 
	{
		std::vector<BMS::Parameter_Validators*> validators;
	public:
		void add(Parameter_Validators* childClassObj)
		{
			validators.push_back(childClassObj);
		}
		bool isParamOkay()
		{
			bool compositeResult = true;
			for (auto iter = validators.begin(); iter != validators.end(); iter++)
			{
				compositeResult &= (* iter)->isParamOkay();
			}
			return compositeResult;  // return s true if all checks passed.
		}
		void setValue(ParameterCheck obj, float value)
		{
			validators.at(static_cast<int>(obj))->setValue(value);
		}
		void display()
		{
			for (int i = 0; i < validators.size(); i++)
			{
				validators.at(i)->display();
			}
		}
		 
	};

	bool isBatteryOkay(BMS::compositeValidator* CompositeValidators);
}



#endif
