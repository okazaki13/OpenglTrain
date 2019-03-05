#include"Declaration.h"
#include"GlobalVariable.h"
#include <GL/glut.h>
#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")

#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/lib/sc.lib")
#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/lib/spo.lib")

#include <stdio.h>




//----------------------------------------------------
// ���C���֐�
//----------------------------------------------------
int main(int argc, char *argv[]) {

	
	check_spidar_being();

	////////////////////////////////////
	//OpenGL�̏����ݒ�
	////////////////////////////////////
	glutInit(&argc, argv);//���̏�����
	int  WindowPositionX = 100;  //��������E�B���h�E�ʒu��X���W
	int  WindowPositionY = 100;  //��������E�B���h�E�ʒu��Y���W
	int  WindowWidth = 512;    //��������E�B���h�E�̕�
	int  WindowHeight = 512;    //��������E�B���h�E�̍���
	char WindowTitle[] = "���E�̎n�܂�";  //�E�B���h�E�̃^�C�g��
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(WindowWidth, WindowHeight); //�E�B���h�E�T�C�Y�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(WindowTitle);  //�E�B���h�E�̍쐬
	glutDisplayFunc(Display); //�`�掞�ɌĂяo�����֐����w�肷��i�֐����FDisplay�j
	glutTimerFunc(1000, RedisplayTimer, 0);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(sKeybord);
	Initialize(); //�����ݒ�̊֐����Ăяo��



	///////////////////////////////////////
	//OpenGL�̃f�B�X�v���C���X�g��SC����
	//////////////////////////////////////
	ready_tool();
	ready_voxel();



	atexit(endHaptic);
	glutMainLoop();

	return 0;
}





								
