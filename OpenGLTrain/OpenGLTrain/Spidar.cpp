#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")
#include"Declaration.h"
#include"toggle_switch.h"
#include"GlobalVariable.h"

#include<iostream>




float spidar_position[3];//�ʒu,OpenGL�p�Ɋg��ƍ��W�n��]��
float spidar_quaternion[4];//��],OpenGL�p�E����W�n

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
	float spidar_origin_quaternion[4];//�N�H�[�^�j�I��
	float spidar_origin_position[3];//�ʒu
	float spidar_origin_velocity[3];//���x

	SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;
	//float posv[3];

	//�X�p�C�_�[����󂯎���������Q�����Ɋi�[
	ahsGetImpPos(hSpidar, spidar_origin_position);
	ahsGetImpPosVel(hSpidar, spidar_origin_velocity);//���x�A���󖢎g�p
	ahsGetImpOri_wxyz(hSpidar, spidar_origin_quaternion);

	//�O���[�o���ϐ��ւ̊i�[
	value_conversion(spidar_origin_position, spidar_origin_quaternion);


	float force[3] = { 0 };
	float torque[3] = { 0 };

	
	ahsSetImpForce(hSpidar, force);	//[N]
	ahsSetImpTorque(hSpidar, torque);	//[Nm]
}


//�X�p�C�_�[������͂��ꂽ�l��openGL��Ŏg���₷�����ăO���[�o���ϐ��Ɋi�[������
void value_conversion(float position[], float quaternion[]) {
	
	//�l�̊g���OpenGL���W�n�ւ̕ϊ��A�{�c����̖ڕ��ʂ��Q�l��
	spidar_position[0] = position[0] * 2000;
	spidar_position[1] = -position[2] * 2000;
	spidar_position[2] = position[1] * 2000;


	//spidar���瓾��ꂽ�N�H�[�^�j�I���͍���n���W�n�Ȃ̂�
	//OpenGL�p�ɉE����W�n�ɕϊ�������
	spidar_quaternion[0] = quaternion[0];
	spidar_quaternion[1] = quaternion[1];
	spidar_quaternion[2] = -quaternion[3];
	spidar_quaternion[3] = quaternion[2];



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