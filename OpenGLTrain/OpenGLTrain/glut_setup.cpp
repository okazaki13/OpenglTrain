#include <GL/glut.h>
#include"Declaration.h"


int  WindowPositionX = 100;  //��������E�B���h�E�ʒu��X���W
int  WindowPositionY = 100;  //��������E�B���h�E�ʒu��Y���W
int  WindowWidth = 512;    //��������E�B���h�E�̕�
int  WindowHeight = 512;    //��������E�B���h�E�̍���
char WindowTitle[] = "���E�̎n�܂�";  //�E�B���h�E�̃^�C�g��

//----------------------------------------------------
// �����ݒ�̊֐�
//----------------------------------------------------
void Initialize(void) {
	glClearColor(1.0, 1.0, 1.0, 0.1); //�w�i�F
	glEnable(GL_BLEND);//�f�v�X�o�b�t�@���g�p�FglutInitDisplayMode() �� GLUT_DEPTH ���w�肷��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	gluPerspective(30.0, (double)WindowWidth / (double)WindowHeight, 0.1, 1000.0); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
	gluLookAt(
		20, -200.0, 50.0, // ���_�̈ʒux,y,z;
		20, 0.0, 0.0,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		0.0,0.0, 1.0);  //���E�̏�����̃x�N�g��x,y,z
}




