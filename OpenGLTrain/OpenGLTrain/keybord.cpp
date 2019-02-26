#include "../../include/SpidarAHS/SpidarAHS.h"
#include "SettingValue.h"
#include"GlobalVariable.h"
#include <GL/glut.h>

void keyboard(unsigned char key, int x, int y) {
	static int isActive = 1;
	switch (key) {
	case 'q':
	case 'Q':
	case '\033':
		//endProgram(); //�v���O�����I��������
		exit(0);
		break;
	case 'a':
		//isActive = isActive ? 0 : 1;
		//ahsActive(spidar, isActive);
		//break;
	case 'c':
		//ahsCalib(g_hSpi); //�L�����u���[�V����
		//enX = enY = 0;
		//enZ = HEIGHT_NUM + ENDMILL_R;
		//g_qt[0] = 1;
		//g_qt[1] = 0;
		//g_qt[2] = 0;
		//g_qt[3] = 0;
		break;
	case 'd':
		//cf_direction_flag = cf_direction_flag ? 0 : 1; //�؍��R�����\��
		break;
	case 'e':
		//cf_example_flag = cf_example_flag ? 0 : 1; //�؍�̓T���v���掦
		//g_isScroll = g_isScroll ? 0 : 1; //�����X�N���[���X�C�b�`
		break;
	case 'E':
		//cf_experience_flag = 1; //�̌�����
		//isAutoOperating = 0;
		////cf_experience_flag = cf_experience_flag?0:1; //�̌�����
		//ahsCalib(g_hSpi); //�L�����u���[�V����
		//enX = WIDTH_NUM * 0.5;
		//enY = 0;
		//enZ = HEIGHT_NUM + ENDMILL_R - 1.5;
		//g_qt[0] = 1;
		//g_qt[1] = 0;
		//g_qt[2] = 0;
		//g_qt[3] = 0;
		//g_y_pos_cut_history = 0;
		//g_isHaptic = 0;	//�͊o�v�ZOFF
		//g_isScroll = 0;
		//initVoxel();
		//break;
	case 'h':
		//g_isHaptic = g_isHaptic ? 0 : 1;	//�͊o�掦�������邩�ǂ����̃X�C�b�`
		//break;
	case 'm':
		//isCfMemory = isCfMemory ? 0 : 1;	//�؍��R�L�^�X�C�b�`
		//break;
	case 'o':
		//isAutoOperating = isAutoOperating ? 0 : 1; //�����^�]�X�C�b�`
		//g_isHaptic = 1;
		//one_path_count = 0;
		//auto_tool_path_count = 0;
		//break;
	case 'r':
		//g_isHaptic = 0;	//�͊o�v�ZOFF
		//initVoxel();
		//g_y_pos_cut_history = 0;
		//break;
	case 's':
		//g_isScroll = g_isScroll ? 0 : 1; //�����X�N���[���X�C�b�`
		break;
	case 'S':
		//g_isSample = g_isSample ? 0 : 1; //�T���v���쐬�X�C�b�`
		break;
		//case '0':
		//case '1':
	case '2':
		//case '3':
	case '4':
	case '5':
	case '6':
		//case '7':
	case '8':
		//g_cf_ex_num = key - '0'; //�T���v���掦�X�C�b�`
		break;
	case '9':
		ahsStopHapticLoop(spidar);
		spidar = ahsQuit(spidar);
	default:
		break;
	}
}

/****************** Special_Keyboard�֐� ******************/

void sKeybord(int Key, int x, int y) {
	//switch (Key)
	//{
	//case GLUT_KEY_LEFT: //��
	//	if (glutGetModifiers() == 0) {
	//		enX -= ENDMILL_FEED;	//��X����
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {	//�V�t�g��������
	//	   //rotate_angle -= 0.1;	//����]�p�x
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {		//Ctrl��������Y������
	//	   //����]
	//		double temp_q[4];
	//		double temp_v[3] = { 0,1,0 };
	//		calcQTFromAngleV(temp_q, DegreeToRadian(-1), temp_v);
	//		calcQTProduct(g_qt, g_qt, temp_q);

	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_ALT) {		//Alt�������̓J����x�����_
	//		cam_num = 1;	//����]
	//	}
	//	break;

	//case GLUT_KEY_UP: //��
	//	if (glutGetModifiers() == 0) {
	//		enY += ENDMILL_FEED;	//��Z����
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {		//�V�t�g��������Y������
	//		enZ += ENDMILL_FEED;	//��Y����
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {		//Ctrl��������Y������
	//	   //����]
	//		double temp_q[4];
	//		double temp_v[3] = { 1,0,0 };
	//		calcQTFromAngleV(temp_q, DegreeToRadian(-1), temp_v);
	//		calcQTProduct(g_qt, g_qt, temp_q);

	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_ALT) {		//Alt�������̓J������O���王�_
	//		cam_num = 0;	//����]
	//	}
	//	break;

	//case GLUT_KEY_RIGHT: //��
	//	if (glutGetModifiers() == 0) {
	//		enX += ENDMILL_FEED;	//��X����
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {		//�V�t�g��������
	//	   //rotate_angle += 0.1;	//����]�p�x
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) {		//Ctrl��������Y������
	//	   //����]
	//		double temp_q[4];
	//		double temp_v[3] = { 0,1,0 };
	//		calcQTFromAngleV(temp_q, DegreeToRadian(1), temp_v);
	//		calcQTProduct(g_qt, g_qt, temp_q);
	//	}
	//	break;

	//case GLUT_KEY_DOWN: //��
	//	if (glutGetModifiers() == 0) {
	//		enY -= ENDMILL_FEED;	//��Z����

	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
	//		enZ -= ENDMILL_FEED;	//��Y����
	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_CTRL) { //Ctrl��������Y������
	//	   //����]
	//		double temp_q[4];
	//		double temp_v[3] = { 1,0,0 };
	//		calcQTFromAngleV(temp_q, DegreeToRadian(1), temp_v);
	//		calcQTProduct(g_qt, g_qt, temp_q);

	//	}
	//	else if (glutGetModifiers() == GLUT_ACTIVE_ALT) { //Alt�������̓J����y�����_
	//		cam_num = 2;	//����]
	//	}
	//	break;
	//}
}