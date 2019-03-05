#pragma once
#define _USE_MATH_DEFINES
#include <math.h>

#define WIDTH_NUM	20	//X������
#define LENGTH_NUM	20	//Y������
#define HEIGHT_NUM	20	//Z������

#define ENDMILL_D 10			// �H��a[mm]
#define ENDMILL_R ENDMILL_D * 0.5
#define HELIX_ANGLE 30			//�˂���p
#define NUM_OF_CUTTING_EDGE 2	//�n��


#define THETA_FEED 9	// �����͈͐������[dig]
#define THETA_FEED_SAMPLE 0.5	// �T���v���쐬���̏����͈͐������[dig]
#define PHI_FEED 2	// �����͈͐������[dig]
#define ENDMILL_FEED 0.5// �G���h�~�������(�L�[�{�[�h���͎��̂ݎg�p)[mm]
#define AUTO_OPERATING_FEED 0.5/*6.94e-4*//*0.278*/ //�G���h�~�����������(�p�X�ǂݎ�聕�Č��̍ۂɂ̂ݎg�p)[mm]

#define SPINDLE_SPEED 600/*1100*/ //�厲��]��[rpm]
#define TABLE_FEED 30/*264*/ //�e�[�u������[mm/min]


#define AXIS_X 0
#define AXIS_Y 1
#define AXIS_Z 2

#define VOXEL_SIZE 0.2	//Voxel�̃T�C�Y[mm]
#define VOXEL_NUMBER_X 100 //voxel�̐�
#define VOXEL_NUMBER_Y 100 //voxel�̐�
#define VOXEL_NUMBER_Z 100   //voxel�̐�

#define EPSILON 1e-10	//�\���ɏ������l
#define INTEGRAL_W 1000	//�ϕ��擾��





#define ARRAY_SIZE 3	//�z��T�C�Y

#define SPEED_OF_CALC 0	//MainLoop�̊��荞�ݕp�x[ms]

//�؍��R�̕␳�W��
#define CALC_TARGET_FORCE		10.0	//N ���󖢎g�p
#define CALC_MAXIMUM_FORCE		80.0	//N
#define HAPTIC_TARGET_FORCE		1.0		//N ���󖢎g�p
#define HAPTIC_MAXIMUM_FORCE	4.5		//N

/****************** �؍��R�v�Z�p�֐� ******************/
//HPM1
#define Ktc 3034.45
#define Krc 1093.95
#define Kac 157.05
#define Kte 0.3870
#define Kre 5.2584
#define Kae -4.1048

//���H�������Z�o
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



//��厛�{��
//const double cutting_coef_cv1 = 3525;
//const double cutting_coef_cv2 = 45.0;
//const double cutting_coef_cf1 = 3375;
//const double cutting_coef_cf2 = 60.0;
//const double cutting_coef_Kv = 0.20;
//const double cutting_coef_Kf = 0.20;
//																				 
//const double cutting_coef_dl = 0.06981*0.025;//���e���ꂽ�؂�n���� 
//
//�����搶�̎���(A5025)
//#define Ktc 721.2
//#define Krc 218.3
//#define Kte 19.7
//#define Kre 18.2
//#define Kac 104.5
//#define Kae 0
//Excel�Ł`P.91
//#define Ktc 1806
//#define Krc 363.1
//#define Kte 55.95
//#define Kre 60.17
//#define Kac 198.1
//#define Kae 10.72

const double divide_M_PI = 1 / M_PI;

// ���W�A����x�ɕϊ�
#define RadianToDegree(radian)	((180.0 * divide_M_PI) * (radian))
// �x�����W�A���ɕϊ�
#define DegreeToRadian(degree)	((M_PI / 180.0) * (degree))

//#define PRINT_FNC(func)	cout << "func" << func << endl
//
//// ���W�A����x�ɕϊ�
//inline double RadianToDegree( double radian ){ return ( 180 * divide_M_PI ) * radian; }
//// �x�����W�A���ɕϊ�
//inline double DegreeToRadian( double degree ){ return ( M_PI * 180 ) * degree; }


