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
	glClearColor(1.0, 1.0, 1.0, 1.0); //�w�i�F
	glEnable(GL_DEPTH_TEST);//�f�v�X�o�b�t�@���g�p�FglutInitDisplayMode() �� GLUT_DEPTH ���w�肷��

	gluPerspective(30.0, (double)WindowWidth / (double)WindowHeight, 0.1, 1000.0); //�������e�@�̎��̐�gluPerspactive(th, w/h, near, far);
	gluLookAt(
		0.0, -100.0, 50.0, // ���_�̈ʒux,y,z;
		0.0, 100.0, 0.0,   // ���E�̒��S�ʒu�̎Q�Ɠ_���Wx,y,z
		0.0, 0.0, 1.0);  //���E�̏�����̃x�N�g��x,y,z
}




//openGL�̃Z�b�g�A�b�v���܂Ƃ߂��֐�
void openGL_setup(int argc, char *argv[]) {
	glutInit(&argc, argv);//���̏�����
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(WindowWidth, WindowHeight); //�E�B���h�E�T�C�Y�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(WindowTitle);  //�E�B���h�E�̍쐬
	glutDisplayFunc(Display); //�`�掞�ɌĂяo�����֐����w�肷��i�֐����FDisplay�j
	Initialize(); //�����ݒ�̊֐����Ăяo��
}