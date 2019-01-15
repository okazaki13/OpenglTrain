#include "Tool.h"
#include <GL/glut.h>
#define _USE_MATH_DEFINES
#include <math.h>


Tool::Tool()
{
}


Tool::~Tool()
{
}


float Tool::get_endmill_D() {
	return endmill_D;
}


void Tool::create_ballendmill(int offset[2]) {
	// �{�[���G���h�~����`��
	glPushMatrix();
	glColor4d(0.8, 0.8, 0.8, 1);
	glScalef(1, 1, 1);//�g��
	glTranslated(offset[0], offset[1], offset[2]);
	glutSolidSphere(endmill_R/**1.05*/, 20, 20);
	drawCylinder(endmill_R, endmill_R, 20);
	glPopMatrix();
}




void Tool::create_ballendmill(int offset_x, int offset_y, int offset_z) {
	// �{�[���G���h�~����`��
	glPushMatrix();
	glColor4d(0.8, 0.8, 0.8, 1);
	glScalef(1, 1, 1);//�g��
	glTranslated(offset_x, offset_y, offset_z);
	glutSolidSphere(endmill_R/**1.05*/, 20, 20);
	drawCylinder(endmill_R, endmill_R, 20);
	glPopMatrix();
}

/****************** �G���h�~���\���pdrawCylinder�֐� ******************/

void Tool::drawCylinder(float radius, float height, int slides) //���a�C����(��ʂ���)�C��ʂ̉~�̕�����
{
	//����
	glNormal3d(0.0, 0.0, -1.0);
	glBegin(GL_POLYGON);
	for (double i = slides; i > 0; --i) {
		double t = M_PI * 2 / slides * (double)i;
		glVertex3d(radius * cos(t), radius * sin(t), 0);
	}
	glEnd();
	//����
	glBegin(GL_TRIANGLE_STRIP);
	for (double i = 0; i <= slides; i++) {
		double t = i * 2 * M_PI / slides;
		glNormal3f((GLfloat)cos(t), (GLfloat)sin(t), 0);
		glVertex3f((GLfloat)(radius*cos(t)), (GLfloat)(radius*sin(t)), height);
		glVertex3f((GLfloat)(radius*cos(t)), (GLfloat)(radius*sin(t)), 0);
	}
	glEnd();
	//���
	glNormal3d(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (double i = 0; i < slides; ++i) {
		double t = M_PI * 2 / slides * (double)i;
		glVertex3d(radius * cos(t), radius * sin(t), height);
	}
	glEnd();
}