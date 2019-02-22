#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include"Declaration.h"
#include "LOAD_STLMODEL.h"
#include"GlobalVariable.h"
#include <GL/glut.h>
#include <iostream>


using namespace std;


#define DISP_LIST_INDEX1 1//�؂�n���f���̃f�B�X�v���C���X�g
#define DISP_LIST_INDEX2 2//�V�����N���f���̃f�B�X�v���C���X�g
#define DISP_LIST_INDEX3 3//�z���_�[���f���̃f�B�X�v���C���X�g


void create_tool() {
	
	


	////�H��n��̕`��ƃR���W�����ݒ�
	LOAD_STLMODEL cutting_edge;
	cutting_edge.get_stl("../../STLmodel/cutting_edge.STL");
	glNewList(DISP_LIST_INDEX1, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.0, 1.0, 0.0, 1.0);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��
	
	for (int i=0; i < cutting_edge.get_polygon_number();i++){
		glNormal3f(cutting_edge.normal_coordinate_x[i], cutting_edge.normal_coordinate_y[i], cutting_edge.normal_coordinate_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate1_x[i] ,cutting_edge.polygon_coordinate1_y[i] ,cutting_edge.polygon_coordinate1_z[i] );
		glVertex3f(cutting_edge.polygon_coordinate2_x[i] ,cutting_edge.polygon_coordinate2_y[i] ,cutting_edge.polygon_coordinate2_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate3_x[i] ,cutting_edge.polygon_coordinate3_y[i] ,cutting_edge.polygon_coordinate3_z[i]);	
	}
	glEnd();
	glEndList();
	
	SCObject SC_cutting_edge;
	SC_cutting_edge.AddTriangles(cutting_edge.SC_vertices, cutting_edge.SC_vertices_num,cutting_edge.SC_triangles,cutting_edge.SC_triangles_num);
	/////�H��n�悱���܂�



	/////�H��V�����N���̕`��ƃR���W�����ݒ�
	LOAD_STLMODEL shank;
	shank.get_stl("../../STLmodel/shank.STL");
	glNewList(DISP_LIST_INDEX2, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.3, 0.7, 0.3, 0.3);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��

	for (int i = 0; i < shank.get_polygon_number(); i++) {
		glNormal3f(shank.normal_coordinate_x[i], shank.normal_coordinate_y[i], shank.normal_coordinate_z[i]);
		glVertex3f(shank.polygon_coordinate1_x[i], shank.polygon_coordinate1_y[i], shank.polygon_coordinate1_z[i]);
		glVertex3f(shank.polygon_coordinate2_x[i], shank.polygon_coordinate2_y[i], shank.polygon_coordinate2_z[i]);
		glVertex3f(shank.polygon_coordinate3_x[i], shank.polygon_coordinate3_y[i], shank.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();

	SCObject SC_shank;
	SC_shank.AddTriangles(shank.SC_vertices, shank.SC_vertices_num, shank.SC_triangles, shank.SC_triangles_num);
	/////�H��V�����N�����܂�





	////�H��z���_�[���̕`��ƃR���W�����ݒ�
	LOAD_STLMODEL holder;
	holder.get_stl("../../STLmodel/holder.STL");
	glNewList(DISP_LIST_INDEX3, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.3, 0.7, 0.3, 0.7);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��

	for (int i = 0; i < holder.get_polygon_number(); i++) {
		glNormal3f(holder.normal_coordinate_x[i], holder.normal_coordinate_y[i], holder.normal_coordinate_z[i]);
		glVertex3f(holder.polygon_coordinate1_x[i], holder.polygon_coordinate1_y[i], holder.polygon_coordinate1_z[i]);
		glVertex3f(holder.polygon_coordinate2_x[i], holder.polygon_coordinate2_y[i], holder.polygon_coordinate2_z[i]);
		glVertex3f(holder.polygon_coordinate3_x[i], holder.polygon_coordinate3_y[i], holder.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();

	SCObject SC_holder;
	SC_shank.AddTriangles(holder.SC_vertices, holder.SC_vertices_num, holder.SC_triangles, holder.SC_triangles_num);

	////�H��z���_�[�������܂�
}



void matrix_tool() {
	//�ʒu
	float spidar_origin_position[3];//�ʒu
	GLfloat position[3];
	position[0] = spidar_origin_position[0];
	position[1] = spidar_origin_position[1];
	position[2] = spidar_origin_position[2];

	//�p��
	float spidar_origin_quaternion[4];
	GLfloat rotation[4];
	rotation[0] = spidar_origin_quaternion[0];
	rotation[1] = spidar_origin_quaternion[1];
	rotation[2] = spidar_origin_quaternion[2];
	rotation[3] = spidar_origin_quaternion[3];

	glPushMatrix();
	glColor4f(0.7, 0.2, 0.2, 0.5);	// ���p�`�̐F(RGBA)
	glTranslatef(position[0],position[1],position[2]);//���s�ړ��l�̐ݒ�
	glRotatef(rotation[3], rotation[0], rotation[1], rotation[2]);
	glCallList(DISP_LIST_INDEX1);
	glCallList(DISP_LIST_INDEX2);
	glCallList(DISP_LIST_INDEX3);
	glPopMatrix();
	//cout << "�����܂�" << endl;

}

