#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include"Declaration.h"
#include "LOAD_STLMODEL.h"
#include"GlobalVariable.h"
#include"SettingValue.h"
#include <GL/glut.h>
#include <iostream>


using namespace std;


#define DISP_LIST_INDEX1 1//�؂�n���f���̃f�B�X�v���C���X�g
#define DISP_LIST_INDEX2 2//�V�����N���f���̃f�B�X�v���C���X�g
#define DISP_LIST_INDEX3 3//�z���_�[���f���̃f�B�X�v���C���X�g

SCSceneManager scene(SC_SCENE_MANAGER_TRIANGLE_SOUP);
SPOObject spo_cutting_edge;
SPOObject spo_shank;
SPOObject spo_holder;
SPOObject spo_cube;

SCObject sc_cutting_edge;
SCObject sc_shank;
SCObject sc_holder;


void ready_tool_edge() {




	////�H��n��̕`��ƃR���W�����ݒ�
	LOAD_STLMODEL cutting_edge;
	cutting_edge.get_stl("../../STLmodel/cutting_edge.STL");
	glNewList(DISP_LIST_INDEX1, GL_COMPILE); //�R���p�C���̂�

	glColor4f(0.0, 1.0, 0.0, 1.0);	// ���p�`�̐F(RGBA)
	glBegin(GL_TRIANGLES);				// ���p�`�̕`��

	for (int i = 0; i < cutting_edge.get_polygon_number(); i++) {
		glNormal3f(cutting_edge.normal_coordinate_x[i], cutting_edge.normal_coordinate_y[i], cutting_edge.normal_coordinate_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate1_x[i], cutting_edge.polygon_coordinate1_y[i], cutting_edge.polygon_coordinate1_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate2_x[i], cutting_edge.polygon_coordinate2_y[i], cutting_edge.polygon_coordinate2_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate3_x[i], cutting_edge.polygon_coordinate3_y[i], cutting_edge.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();
	//cutting_edge.delede_same_coordinate();
	//cutting_edge.labeling();

	cutting_edge.make_spo_vertices();
	cutting_edge.make_spo_triangles();
	cutting_edge.use_spo(spo_cutting_edge);

	//printf("�w�C���O�xclose judge = %d (0:nonClosed  1:Closed)\n", spo_cutting_edge.IsClosed());
	//
	//if (spo_cutting_edge.AddTriangles(cutting_edge.SC_vertices, cutting_edge.SC_vertices_num, cutting_edge.SC_triangles, cutting_edge.SC_triangles_num) != SC_NO_ERROR) {};
	//spo_cutting_edge.ConnectVertices(0.001);
	//spo_cutting_edge.SplitEdges(0.01, 5, true);
	//spo_cutting_edge.RemoveRedundantVertices(0.01, 5, true);
	//spo_cutting_edge.ChangeTriangulationPattern(SPO_TRIANGULATION_TYPE_REDUCE_AREA_DIFFERENCE, 1.0, 5);
	//spo_cutting_edge.DecomposeIntoSingleBoundaryPieces();
	//printf("piece count = %d\n", spo_cutting_edge.GetPieceCount());
	//for (int i = 0; i < spo_cutting_edge.GetPieceCount(); i++) {
	//	if (spo_cutting_edge.IsClosed(i) != true) {
	//		printf("piece index %d\n", i);
	//		printf("**Closed�ȃ��f���ɂȂ��Ă��܂���DConnectVertices�̃p�����[�^���čl���Ă�������**\n");
	//	}
	//}
	//printf("�w�C����xclose judge = %d (0:nonClosed  1:Closed)\n", spo_cutting_edge.IsClosed());

	//int j = 0,k = 0;
	//for (int i = 0; i < spo_cutting_edge.GetPieceCount(); i++) {
	//	const SPOPiece *temp = spo_cutting_edge.GetPiece(i);
	//	sc_cutting_edge.AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON, temp->vertices, temp->vertexSize,
	//		temp->triangles, temp->triangleSize);
	//	j += temp->vertexSize;
	//	k += temp->triangleSize;
	//	printf("\n���H��f���I�u�W�F�N�g�̏C����\n");
	//	printf("�C���O ==> ���_��:%d, �|���S����:%d\n", cutting_edge.SC_vertices_num, cutting_edge.get_polygon_number());
	//	printf("�C���� ==> ���_��:%d, �|���S����:%d\n\n", j, k);

	//}

	/////�H��n�悱���܂�

}
void ready_tool_shank() {

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


	shank.make_spo_vertices();
	shank.make_spo_triangles();
	shank.use_spo(spo_shank);


	/////�H��V�����N�����܂�
}


void ready_tool_holder(){

	//////�H��z���_�[���̕`��ƃR���W�����ݒ�
	//LOAD_STLMODEL holder;
	//holder.get_stl("../../STLmodel/holder.STL");
	//glNewList(DISP_LIST_INDEX3, GL_COMPILE); //�R���p�C���̂�

	//glColor4f(0.3, 0.7, 0.3, 0.7);	// ���p�`�̐F(RGBA)
	//glBegin(GL_TRIANGLES);				// ���p�`�̕`��

	//for (int i = 0; i < holder.get_polygon_number(); i++) {
	//	glNormal3f(holder.normal_coordinate_x[i], holder.normal_coordinate_y[i], holder.normal_coordinate_z[i]);
	//	glVertex3f(holder.polygon_coordinate1_x[i], holder.polygon_coordinate1_y[i], holder.polygon_coordinate1_z[i]);
	//	glVertex3f(holder.polygon_coordinate2_x[i], holder.polygon_coordinate2_y[i], holder.polygon_coordinate2_z[i]);
	//	glVertex3f(holder.polygon_coordinate3_x[i], holder.polygon_coordinate3_y[i], holder.polygon_coordinate3_z[i]);
	//}
	//glEnd();
	//glEndList();

	//
	//SC_shank.AddTriangles(holder.SC_vertices, holder.SC_vertices_num, holder.SC_triangles, holder.SC_triangles_num);

	//////�H��z���_�[�������܂�
}



void ready_cube() {
	/////�H��V�����N���̕`��ƃR���W�����ݒ�
	LOAD_STLMODEL cube;
	cube.get_stl("../../STLmodel/cube.STL");




	cube.make_spo_vertices();
	cube.make_spo_triangles();
	cube.use_spo(spo_cube);


	/////�H��V�����N�����܂�
}



















//float spidar_origin_position[3];
//float spidar_origin_quaternion[4];
void make_tool() {
	////�ʒu	
	//float position[3];
	//position[0] = spidar_position[0];
	//position[1] = spidar_position[1];
	//position[2] = spidar_position[2];
	
	//�p��
	float axis_vector[4];//�N�H�[�^�j�I������]���x�N�g���Ɖ�]�����ɕϊ��������̂�����

	QuaternionToAxisVector(spidar_quaternion, axis_vector);

	glPushMatrix();
	glColor4f(0.7, 0.2, 0.2, 0.5);	// ���p�`�̐F(RGBA)
	

	glTranslatef(spidar_position[0], spidar_position[1], spidar_position[2]);//���s�ړ��l�̐ݒ�B�X�p�C�_�[��xyz�ƍ��W�n�𐠍���

	glRotatef( (RadianToDegree(axis_vector[0]))*3, axis_vector[1], axis_vector[2], axis_vector[3]);
	
	
	glCallList(DISP_LIST_INDEX1);
	glCallList(DISP_LIST_INDEX2);
	glCallList(DISP_LIST_INDEX3);
	glPopMatrix();
	//cout << "�����܂�" << endl;

}
void make_SC_tool(SCSceneManager &scene) {
	//�p��
	float axis_vector[4];//�N�H�[�^�j�I������]���x�N�g���Ɖ�]�����ɕϊ��������̂�����

	QuaternionToAxisVector(spidar_quaternion, axis_vector);

	scene.SetTransformation(1, SC_POSITION_ORIGIN, spidar_position);
	scene.SetTransformation(2, SC_POSITION_ORIGIN, spidar_position);


}

