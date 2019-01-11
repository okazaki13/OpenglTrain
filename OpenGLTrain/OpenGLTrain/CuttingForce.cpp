#include "CuttingForce.h"

#define _USE_MATH_DEFINES
#include <math.h>


CuttingForce::CuttingForce()
{
}


CuttingForce::~CuttingForce()
{
}


double CalculationFv_Ballendmill(double h, double V) {
	double cf;
	const int PHI_FEED =2;   // œ‹”ÍˆÍü‘—‚è—Ê[dig]
	const int ENDMILL_D = 10;// H‹ï’¼Œa[mm]

	//‰ÁHÀŒ±‚æ‚èZo
	const double cutting_coef_cv1 = -8890.23659588223 * 0.2;
	const double cutting_coef_cv2 = -0.923521849277421 * 24;
	const double cutting_coef_Kv = 0.014008256;

	const double cutting_coef_dl = PHI_FEED * M_PI / 180 * ENDMILL_D / 2/*0.04363*/; //“Š‰e‚³‚ê‚½Ø‚ên’·‚³
	

	cf = (cutting_coef_cv1 * h + cutting_coef_cv2) * (1 - cutting_coef_Kv * V) * cutting_coef_dl;

	return cf;

}


double CalculationFf_Ballendmill(double h, double V) {
	double cf;
	const int PHI_FEED = 2;  // œ‹”ÍˆÍü‘—‚è—Ê[dig]
	const int ENDMILL_D = 10;// H‹ï’¼Œa[mm]


	//‰ÁHÀŒ±‚æ‚èZo
	const double cutting_coef_cf1 = 2561.90198583976 * 0.4;
	const double cutting_coef_cf2 = 10.3227906460308;
	const double cutting_coef_Kf = 0.010319079;
	const double cutting_coef_dl = PHI_FEED * M_PI / 180 * ENDMILL_D / 2/*0.04363*/; //“Š‰e‚³‚ê‚½Ø‚ên’·‚³

	cf = (cutting_coef_cf1 * h + cutting_coef_cf2) * (1 - cutting_coef_Kf * V) * cutting_coef_dl;

	return cf;
}