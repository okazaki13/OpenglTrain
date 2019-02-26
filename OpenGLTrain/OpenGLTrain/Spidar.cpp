#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")
#include"Declaration.h"
#include"toggle_switch.h"
#include"GlobalVariable.h"

#include<iostream>


float spidar_origin_quaternion[4];//�N�H�[�^�j�I��
float spidar_origin_position[3];//�ʒu
float spidar_origin_velocity[3];//���x
SPIDAR_HANDLE spidar;

void init_spidar(){
	
	char fileName[] = "../../data/spidar_gcc_001.xml";		// SPIDAR-G�̂Ƃ�
	printf("xmlfile:%s\n", fileName);
	ahsCreate_Spidar(&spidar, fileName, 0);
	
	
	ahsSetImpScale(spidar, 1.0f, 1.0f);	//[m],[rad]
	ahsSetHapticLoopCallBackFunction(spidar, hapticLoop_w3p4);
	ahsStartHapticLoop(spidar);
	//ahsActive(spidar_handle, 1);


}

void CALLBACK hapticLoop_w3p4(DWORD dwUser)
{


	SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;
	//float posv[3];

	//�v���g�^�C�v�錾
	ahsGetImpPos(hSpidar, spidar_origin_position);
	ahsGetImpPosVel(hSpidar, spidar_origin_velocity);
	ahsGetImpOri_wxyz(hSpidar, spidar_origin_quaternion);

	float force[3] = { 0 };
	float torque[3] = { 0 };

	
	ahsSetImpForce(hSpidar, force);	//[N]
	ahsSetImpTorque(hSpidar, torque);	//[Nm]
}

void endHaptic() {
	
	ahsStopHapticLoop(spidar);
	spidar = ahsQuit(spidar);
}


//�X�p�C�_�[���g�p���邩�ǂ����̊m�F
//�g�p����Ȃ�setup���s��
void check_spidar_being() {
	if (RUN_HAPTIC) {
		OpenSpidarVoice();//�������{�C�X
		init_spidar();
	}
	else {
		//�n�v�e�B�b�N���g��Ȃ��L�[�{�[�h����i���ݗ\��j
	}
}