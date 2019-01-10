#include "Voxel.h"
#include <GL/glut.h>



Voxel::Voxel()
{
}


Voxel::~Voxel()
{
}


void Voxel::create_voxel(int offset[2]) {
	//������
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);//�F�̐ݒ�
	glTranslated(offset[0], offset[1],offset[2]);//���s�ړ��l�̐ݒ�
	glutSolidCube(10.0);//�����F(��ӂ̒���)
	glPopMatrix();

}

void Voxel::create_voxel(int offset_x, int offset_y, int offset_z) {
	//������
	glPushMatrix();
	glColor3d(0.0, 1.0, 0.0);//�F�̐ݒ�
	glTranslated(offset_x, offset_y,offset_z);//���s�ړ��l�̐ݒ�
	glutSolidCube(10.0);//�����F(��ӂ̒���)
	glPopMatrix();
}

void Voxel::set_voxelcolor(double R, double G, double B) {
	color[0] = R;
	color[1] = G;
	color[2] = B;

}