#include"Declaration.h"
#include <GL/glut.h>
#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")

#include <stdio.h>


//----------------------------------------------------
// ���C���֐�
//----------------------------------------------------
int main(int argc, char *argv[]) {
	extern int WindowPositionX;  //��������E�B���h�E�ʒu��X���W
	extern int WindowPositionY;  //��������E�B���h�E�ʒu��Y���W
	extern int WindowWidth;   //��������E�B���h�E�̕�
	extern int WindowHeight ;    //��������E�B���h�E�̍���
	extern char WindowTitle[]; //�E�B���h�E�̃^�C�g��

	


	check_spidar_being();



	openGL_setup(argc, argv);
	glutMainLoop();

	return 0;
}





								
