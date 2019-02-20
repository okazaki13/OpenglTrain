#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include"Declaration.h"
#include "LOAD_STLMODEL.h"
#include <GL/glut.h>
#include <iostream>


using namespace std;


#define DISP_LIST_INDEX1 1//�؂�n���f���̃f�B�X�v���C���X�g


void create_cutting_edge() {
	
	


	////�H��n��̕`��	
	LOAD_STLMODEL cutting_edge;
	cutting_edge.get_stl("../../STLmodel/cutting_edge.STL");
	glNewList(DISP_LIST_INDEX1, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.7, 0.2, 0.2, 0.5);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��
	
	for (int i=0; i < cutting_edge.get_polygon_number();i++){
		glNormal3f(cutting_edge.normal_coordinate_x[i], cutting_edge.normal_coordinate_y[i], cutting_edge.normal_coordinate_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate1_x[i] ,cutting_edge.polygon_coordinate1_y[i] ,cutting_edge.polygon_coordinate1_z[i] );
		glVertex3f(cutting_edge.polygon_coordinate2_x[i] ,cutting_edge.polygon_coordinate2_y[i] ,cutting_edge.polygon_coordinate2_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate3_x[i] ,cutting_edge.polygon_coordinate3_y[i] ,cutting_edge.polygon_coordinate3_z[i]);	
	}
	//glVertex3f(0.0f, 0.0f, 0.0f);
	//glVertex3f(5.0f, 5.0f, 5.5f);
	//glVertex3f(0.0f, 0.0f, 10.0f);
	glEnd();
	glEndList();
	

	SCObject SC_cutting_edge;
	SC_cutting_edge.AddTriangles(cutting_edge.SC_vertices, cutting_edge.SC_vertices_num,cutting_edge.SC_triangles,cutting_edge.SC_triangles_num);
	/////�H��n�悱���܂�




}

void matrix_cutting_edge() {

	glPushMatrix();
	glColor4f(0.7, 0.2, 0.2, 0.5);	// ���p�`�̐F(RGBA)
	glTranslated(0,0,0);//���s�ړ��l�̐ݒ�
	glCallList(DISP_LIST_INDEX1);

	glPopMatrix();
	cout << "�����܂�" << endl;

}