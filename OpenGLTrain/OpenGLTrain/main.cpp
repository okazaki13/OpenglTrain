#include"Declaration.h"
#include <GL/glut.h>

//----------------------------------------------------
// ���C���֐�
//----------------------------------------------------
int main(int argc, char *argv[]) {
	extern int WindowPositionX;  //��������E�B���h�E�ʒu��X���W
	extern int WindowPositionY;  //��������E�B���h�E�ʒu��Y���W
	extern int WindowWidth;   //��������E�B���h�E�̕�
	extern int WindowHeight ;    //��������E�B���h�E�̍���
	extern char WindowTitle[]; //�E�B���h�E�̃^�C�g��

	OpenSpidarVoice();//�������{�C�X�̌Ăяo��

	glutInit(&argc, argv);//���̏�����
	glutInitWindowPosition(WindowPositionX, WindowPositionY);//�E�B���h�E�̈ʒu�̎w��
	glutInitWindowSize(WindowWidth, WindowHeight); //�E�B���h�E�T�C�Y�̎w��
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);//�f�B�X�v���C���[�h�̎w��
	glutCreateWindow(WindowTitle);  //�E�B���h�E�̍쐬
	glutDisplayFunc(Display); //�`�掞�ɌĂяo�����֐����w�肷��i�֐����FDisplay�j
	Initialize(); //�����ݒ�̊֐����Ăяo��
	glutMainLoop();
	return 0;
}





								
