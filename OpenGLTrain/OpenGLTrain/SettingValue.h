#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define WIDTH_NUM	20	//X軸方向
#define LENGTH_NUM	20	//Y軸方向
#define HEIGHT_NUM	20	//Z軸方向

#define ENDMILL_D 10			// 工具直径[mm]
#define ENDMILL_R ENDMILL_D * 0.5
#define HELIX_ANGLE 30			//ねじれ角
#define NUM_OF_CUTTING_EDGE 2	//刃数


#define THETA_FEED 9	// 除去範囲線送り量[dig]
#define THETA_FEED_SAMPLE 0.5	// サンプル作成時の除去範囲線送り量[dig]
#define PHI_FEED 2	// 除去範囲線送り量[dig]
#define ENDMILL_FEED 0.5// エンドミル送り量(キーボード入力時のみ使用)[mm]
#define AUTO_OPERATING_FEED 0.5/*6.94e-4*//*0.278*/ //エンドミル自動送り量(パス読み取り＆再現の際にのみ使用)[mm]

#define SPINDLE_SPEED 600/*1100*/ //主軸回転数[rpm]
#define TABLE_FEED 30/*264*/ //テーブル送り[mm/min]


#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

#define VOXEL_SIZE 0.2	//Voxelのサイズ[mm]
#define VOXEL_NUMBER_X 100 //voxelの数
#define VOXEL_NUMBER_Y 100 //voxelの数
#define VOXEL_NUMBER_Z 100   //voxelの数

#define EPSILON 1e-10	//十分に小さい値
#define INTEGRAL_W 1000	//積分取得幅





#define ARRAY_SIZE 3	//配列サイズ

#define SPEED_OF_CALC 0	//MainLoopの割り込み頻度[ms]

//切削抵抗の補正係数
#define CALC_TARGET_FORCE		10.0	//N 現状未使用
#define CALC_MAXIMUM_FORCE		80.0	//N
#define HAPTIC_TARGET_FORCE		1.0		//N 現状未使用
#define HAPTIC_MAXIMUM_FORCE	4.5		//N

/****************** 切削抵抗計算用関数 ******************/
//HPM1
#define Ktc 3034.45
#define Krc 1093.95
#define Kac 157.05
#define Kte 0.3870
#define Kre 5.2584
#define Kae -4.1048

//加工実験より算出
const double cutting_coef_cv1 = -8890.23659588223 * 0.2;
const double cutting_coef_cv2 = -0.923521849277421 * 24;
const double cutting_coef_cf1 = 2561.90198583976 * 0.4;
const double cutting_coef_cf2 = 10.3227906460308;
const double cutting_coef_Kv = 0.014008256;
const double cutting_coef_Kf = 0.010319079;

/*
const double cutting_coef_cv1 = -8890.23659588223;
const double cutting_coef_cv2 = -0.923521849277421;
const double cutting_coef_cf1 = 2561.90198583976;
const double cutting_coef_cf2 = 10.3227906460308;
const double cutting_coef_Kv = 0.014008256;
const double cutting_coef_Kf = 0.010319079;
*/



//阪大寺本氏
//const double cutting_coef_cv1 = 3525;
//const double cutting_coef_cv2 = 45.0;
//const double cutting_coef_cf1 = 3375;
//const double cutting_coef_cf2 = 60.0;
//const double cutting_coef_Kv = 0.20;
//const double cutting_coef_Kf = 0.20;
//																				 
//const double cutting_coef_dl = 0.06981*0.025;//投影された切れ刃長さ 
//
//白瀬先生の実験(A5025)
//#define Ktc 721.2
//#define Krc 218.3
//#define Kte 19.7
//#define Kre 18.2
//#define Kac 104.5
//#define Kae 0
//Excelで～P.91
//#define Ktc 1806
//#define Krc 363.1
//#define Kte 55.95
//#define Kre 60.17
//#define Kac 198.1
//#define Kae 10.72

const double divide_M_PI = 1 / M_PI;

// ラジアンを度に変換
#define RadianToDegree(radian)	((180.0 * divide_M_PI) * (radian))
// 度をラジアンに変換
#define DegreeToRadian(degree)	((M_PI / 180.0) * (degree))

//#define PRINT_FNC(func)	cout << "func" << func << endl
//
//// ラジアンを度に変換
//inline double RadianToDegree( double radian ){ return ( 180 * divide_M_PI ) * radian; }
//// 度をラジアンに変換
//inline double DegreeToRadian( double degree ){ return ( M_PI * 180 ) * degree; }


