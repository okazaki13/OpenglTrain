#pragma once
class CuttingForce
{
private:
	double Fv;//x�������؍�͂炵��
	double Ff;//y�������؍�͂炵��

public:
	CuttingForce();
	~CuttingForce();

	double CalculationFv_Ballendmill(double h, double V);
	double CalculationFf_Ballendmill(double h, double V);
};

