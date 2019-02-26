#pragma once
#include"SettingValue.h"

class CUTTING_FORCE
{
private:
	double Fv;//x²•ûŒüØí—Í‚ç‚µ‚¢
	double Ff;//y²•ûŒüØí—Í‚ç‚µ‚¢
	
	double array_theta[NUM_OF_CUTTING_EDGE];// Šen‚ÌŠp“xŠi”[—p”z—ñ


public:
	CUTTING_FORCE();
	~CUTTING_FORCE();

	double CalculationFv_Ballendmill(double h, double V);
	double CalculationFf_Ballendmill(double h, double V);

};

