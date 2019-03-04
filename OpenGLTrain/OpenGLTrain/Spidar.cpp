#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")
#include"Declaration.h"
#include"toggle_switch.h"
#include"GlobalVariable.h"

#include<iostream>




float spidar_position[3];//位置,OpenGL用に拡大と座標系回転済
float spidar_quaternion[4];//回転,OpenGL用右手座標系

SPIDAR_HANDLE spidar;

void init_spidar(){
	
	char fileName[] = "../../data/spidar_gcc_001.xml";		// SPIDAR-Gのとき
	printf("xmlfile:%s\n", fileName);
	ahsCreate_Spidar(&spidar, fileName, 0);
	
	
	ahsSetImpScale(spidar, 1.0f, 1.0f);	//[m],[rad]
	ahsSetHapticLoopCallBackFunction(spidar, hapticLoop_w3p4);
	ahsStartHapticLoop(spidar);
	//ahsActive(spidar_handle, 1);


}

void CALLBACK hapticLoop_w3p4(DWORD dwUser)
{
	float spidar_origin_quaternion[4];//クォータニオン
	float spidar_origin_position[3];//位置
	float spidar_origin_velocity[3];//速度

	SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;
	//float posv[3];

	//スパイダーから受け取った情報を第２引数に格納
	ahsGetImpPos(hSpidar, spidar_origin_position);
	ahsGetImpPosVel(hSpidar, spidar_origin_velocity);//速度、現状未使用
	ahsGetImpOri_wxyz(hSpidar, spidar_origin_quaternion);

	//グローバル変数への格納
	value_conversion(spidar_origin_position, spidar_origin_quaternion);


	float force[3] = { 0 };
	float torque[3] = { 0 };

	
	ahsSetImpForce(hSpidar, force);	//[N]
	ahsSetImpTorque(hSpidar, torque);	//[Nm]
}


//スパイダーから入力された値をopenGL上で使いやすくしてグローバル変数に格納する作業
void value_conversion(float position[], float quaternion[]) {
	
	//値の拡大とOpenGL座標系への変換、本田さんの目分量を参考に
	spidar_position[0] = position[0] * 2000;
	spidar_position[1] = -position[2] * 2000;
	spidar_position[2] = position[1] * 2000;


	//spidarから得られたクォータニオンは左手系座標系なので
	//OpenGL用に右手座標系に変換する作業
	spidar_quaternion[0] = quaternion[0];
	spidar_quaternion[1] = quaternion[1];
	spidar_quaternion[2] = -quaternion[3];
	spidar_quaternion[3] = quaternion[2];



}

void endHaptic() {
	
	ahsStopHapticLoop(spidar);
	spidar = ahsQuit(spidar);
}


//スパイダーを使用するかどうかの確認
//使用するならsetupも行う
void check_spidar_being() {
	if (RUN_HAPTIC) {
		OpenSpidarVoice();//茜ちゃんボイス
		init_spidar();
	}
	else {
		//ハプティックを使わないキーボード操作（建設予定）
	}
}