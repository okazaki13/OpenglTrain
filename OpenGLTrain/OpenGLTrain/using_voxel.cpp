#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include"Declaration.h"
#include "LOAD_STLMODEL.h"
#include"GlobalVariable.h"
#include"SettingValue.h"
#include <GL/freeglut.h>
#include <iostream>


using namespace std;


#define DISP_LIST_INDEX4 4//�{�N�Z�����f���̃f�B�X�v���C���X�g



void ready_voxel() {




	////�����̂̕`��ƃR���W�����̂��߂̐ݒ�
	LOAD_STLMODEL cube;
	cube.get_stl("../../STLmodel/cube.STL");
	glNewList(DISP_LIST_INDEX4, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.3, 0.3, 0.7, 0.3);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��

	for (int i = 0; i < cube.get_polygon_number(); i++) {
		glNormal3f(cube.normal_coordinate_x[i], cube.normal_coordinate_y[i], cube.normal_coordinate_z[i]);
		glVertex3f(cube.polygon_coordinate1_x[i], cube.polygon_coordinate1_y[i], cube.polygon_coordinate1_z[i]);
		glVertex3f(cube.polygon_coordinate2_x[i], cube.polygon_coordinate2_y[i], cube.polygon_coordinate2_z[i]);
		glVertex3f(cube.polygon_coordinate3_x[i], cube.polygon_coordinate3_y[i], cube.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();

	SCObject SC_cube;
	SC_cube.AddTriangles(cube.SC_vertices, cube.SC_vertices_num, cube.SC_triangles, cube.SC_triangles_num);
	/////�ݒ肱���܂�




}


void make_voxel() {
	float offset[3] = { 20,-100,0 }; //�����ʒu�̐ݒ�
	
	for (int i = 0; i < VOXEL_NUMBER_X; i++) {
		for (int j = 0; j < VOXEL_NUMBER_Y; j++) {
			for (int k = 0; k < VOXEL_NUMBER_Z; k++) {
				glPushMatrix();
				//glColor4f(0.2, 0.2, 0.7, 0.3);	// ���p�`�̐F(RGBA)
				glTranslatef(i * VOXEL_SIZE+offset[0], j * VOXEL_SIZE+offset[1], k * VOXEL_SIZE+offset[2]);
				//glRotatef((1, 0, 0, 0);
				glCallList(DISP_LIST_INDEX4);

				glPopMatrix();
			}
		}
	}

	for (int i = 0; i < VOXEL_NUMBER_X; i++) {
		for (int j = 0; j < VOXEL_NUMBER_Y; j++) {
			for (int k = 0; k < VOXEL_NUMBER_Z; k++) {
				glPushMatrix();
				
				//glColor4f(0.2, 0.2, 0.7, 0.3);	// ���p�`�̐F(RGBA)
				glTranslatef(i * VOXEL_SIZE + offset[0], j * VOXEL_SIZE + offset[1], k * VOXEL_SIZE + offset[2]);
				//glRotatef((1, 0, 0, 0);
				glCallList(DISP_LIST_INDEX4);

				glPopMatrix();
			}
		}
	}
	//cout << "�����܂�" << endl;

}

