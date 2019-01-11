#pragma once
class CuttingForce
{
private:
	double Fv;//x²•ûŒüØí—Í‚ç‚µ‚¢
	double Ff;//y²•ûŒüØí—Í‚ç‚µ‚¢

public:
	CuttingForce();
	~CuttingForce();

	double CalculationFv_Ballendmill(double h, double V);
	double CalculationFf_Ballendmill(double h, double V);
};

