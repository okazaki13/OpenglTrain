#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")
#include"Declaration.h"
#include"toggle_switch.h"

#include<iostream>

SPIDAR_HANDLE spidar_handle;
float spidar_origin_quaternion[4];//クォータニオン
float spidar_origin_position[3];//位置
float spidar_origin_velocity[3];//速度


void init_spidar(){

	char fileName[] = "../../data/spidar_gcc_001.xml";		// SPIDAR-Gのとき
	printf("xmlfile:%s\n", fileName);
	ahsCreate_Spidar(&spidar_handle, fileName, 0);
	
	
	ahsSetImpScale(spidar_handle, 1.0f, 1.0f);	//[m],[rad]
	ahsSetHapticLoopCallBackFunction(spidar_handle, hapticLoop_w3p4);
	ahsStartHapticLoop(spidar_handle);
	//ahsActive(spidar_handle, 1);


}

void CALLBACK hapticLoop_w3p4(DWORD dwUser)
{


	SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;
	//float posv[3];

	//プロトタイプ宣言
	ahsGetImpPos(hSpidar, &spidar_origin_position[3]);
	ahsGetImpPosVel(hSpidar, &spidar_origin_velocity[3]);
	ahsGetImpOri_wxyz(hSpidar, &spidar_origin_quaternion[4]);

	float force[3] = { 0 };
	float torque[3] = { 0 };

	
	ahsSetImpForce(hSpidar, force);	//[N]
	ahsSetImpTorque(hSpidar, torque);	//[Nm]
}

void endHaptic() {
	ahsStopHapticLoop(spidar_handle);
	spidar_handle = ahsQuit(spidar_handle);
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