#include "CUTTING_FORCE.h"
#define _USE_MATH_DEFINES
#include <math.h>


CUTTING_FORCE::CUTTING_FORCE()
{
}


CUTTING_FORCE::~CUTTING_FORCE()
{
}


double CalculationFv_Ballendmill(double h, double V) {
	double cf;
	const double cutting_coef_dl = PHI_FEED * M_PI / 180 * ENDMILL_D / 2/*0.04363*/; //ìäâeÇ≥ÇÍÇΩêÿÇÍêní∑Ç≥
	cf = (cutting_coef_cv1 * h + cutting_coef_cv2) * (1 - cutting_coef_Kv * V) * cutting_coef_dl;

	return cf;

}


double CalculationFf_Ballendmill(double h, double V) {
	double cf;
	const double cutting_coef_dl = PHI_FEED * M_PI / 180 * ENDMILL_D / 2/*0.04363*/; //ìäâeÇ≥ÇÍÇΩêÿÇÍêní∑Ç≥
	cf = (cutting_coef_cf1 * h + cutting_coef_cf2) * (1 - cutting_coef_Kf * V) * cutting_coef_dl;
	return cf;
}