#include"Declaration.h"
#include <GL/glut.h>
#include<iostream>

using namespace std;

//----------------------------------------------------
// �`��̊֐�
//----------------------------------------------------
void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�o�b�t�@�̏���

	Ground();

	object();//�H���؍함�Ȃǂ�\������֐�
	cout << "�`��" << endl;
	glutSwapBuffers(); //glutInitDisplayMode(GLUT_DOUBLE)�Ń_�u���o�b�t�@�����O�𗘗p��
}

//----------------------------------------------------
// ��n�̕`��
//----------------------------------------------------
void Ground() {
	double ground_max_x = 300.0;
	double ground_max_y = 300.0;
	glColor3d(0.8, 0.8, 0.8);  // ��n�̐F
	glBegin(GL_LINES);
	for (double ly = -ground_max_y; ly <= ground_max_y; ly += 10.0) {
		glVertex3d(-ground_max_x, ly, 0);
		glVertex3d(ground_max_x, ly, 0);
	}
	for (double lx = -ground_max_x; lx <= ground_max_x; lx += 10.0) {
		glVertex3d(lx, ground_max_y, 0);
		glVertex3d(lx, -ground_max_y, 0);
	}
	glEnd();
}


void RedisplayTimer(int value) {

	glutPostRedisplay();
	glutTimerFunc(50, RedisplayTimer, 0); //��P������FPS�w��ims�j
}