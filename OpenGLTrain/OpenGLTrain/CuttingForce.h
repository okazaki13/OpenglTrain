#pragma once
class CuttingForce
{
private:
	double Fv;//x軸方向切削力らしい
	double Ff;//y軸方向切削力らしい

public:
	CuttingForce();
	~CuttingForce();

	double CalculationFv_Ballendmill(double h, double V);
	double CalculationFf_Ballendmill(double h, double V);
};

