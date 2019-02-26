#pragma once
#include"SettingValue.h"

class CUTTING_FORCE
{
private:
	double Fv;//x�������؍�͂炵��
	double Ff;//y�������؍�͂炵��
	
	double array_theta[NUM_OF_CUTTING_EDGE];// �e�n�̊p�x�i�[�p�z��


public:
	CUTTING_FORCE();
	~CUTTING_FORCE();

	double CalculationFv_Ballendmill(double h, double V);
	double CalculationFf_Ballendmill(double h, double V);

};

