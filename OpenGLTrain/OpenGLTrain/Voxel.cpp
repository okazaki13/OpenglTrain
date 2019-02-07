#include "Voxel.h"
#include <GL/glut.h>



Voxel::Voxel()
{
	color[0] = 124;
	color[1] = 177;
	color[2] = 255;
	color[3] = 50;
	size = 1;
}


Voxel::~Voxel()
{
}


void Voxel::create_voxel(int offset[3]) {
	//������
	glPushMatrix();
	glClearColor(color[0], color[1], color[2],color[3]);//�F�̐ݒ�.�����͂S��RGBA�iA�͓����x�j
	glTranslated(offset[0], offset[1],offset[2]);//���s�ړ��l�̐ݒ�
	glutSolidCube(size);//�����F(��ӂ̒���)
	glPopMatrix();

}

//cube�������������Ƃ�
void Voxel::create_voxel(int offset_x, int offset_y, int offset_z) {
	//������
	glPushMatrix();
	glClearColor(color[0], color[1], color[2],color[3]);//�F�̐ݒ�B�����͂S��RGBA�iA�͓����x�j
	glTranslated(offset_x, offset_y,offset_z);//���s�ړ��l�̐ݒ�
	glutSolidCube(size);//�����F(��ӂ̒���)
	glPopMatrix();
}

void Voxel::set_voxelcolor(double R, double G, double B) {
	color[0] = R;
	color[1] = G;
	color[2] = B;

}

void Voxel::set_voxelsize(double s) {
	size = s;
}

//�{�N�Z���ŗ����̂������`�̃I�u�W�F�N�g�����Ƃ�
void Voxel::CreateVoxelObject(int a, int b, int c) {
	for (int i; i < a; i++) {
		for (int j; j < b; j++) {
			for (int k; k < c; k++) {
				glPushMatrix();
				glClearColor(color[0], color[1], color[2], color[3]);//�F�̐ݒ�
				glTranslated(i, j, k);//���s�ړ��l�̐ݒ�
				glutSolidCube(size);//�����F(��ӂ̒���)
				voxelID[i][j][k] = true;
				glPopMatrix();
			}
		}
	}
}
