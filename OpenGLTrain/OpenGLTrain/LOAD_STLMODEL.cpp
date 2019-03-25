#include "LOAD_STLMODEL.h"
#include<fstream>
#include<iostream>

using namespace std;


LOAD_STLMODEL::LOAD_STLMODEL()
{
}


LOAD_STLMODEL::~LOAD_STLMODEL()
{
}




void LOAD_STLMODEL::get_stl(string filepass) {
	fstream stlfile;

	float normal_coordinate[3];
	float polygon1_coordinate[3];
	float polygon2_coordinate[3];
	float polygon3_coordinate[3];
	polygon_number = 0;


	stlfile.open(filepass, ios::in);
	if (!stlfile.is_open()) {
		cout << filepass << "���ǂݍ��߂܂���ł�����[" << endl;
	}

	
	stlfile >> modeltype >> filename;



	while (true) {
		stlfile >> dust;//�P�s�ڂ̓������A�Ō��endsolid���c��̂ŁA���O�ɂ����������dust�ɂ����
		//�ŁAif���ŏI��肩�ǂ����`�F�b�N
		if (stlfile.eof()) {
			break;
		}
		stlfile >> dust >> normal_coordinate[0] >> normal_coordinate[1] >> normal_coordinate[2];
		stlfile >> dust >> dust;
		stlfile >> dust >> polygon1_coordinate[0] >> polygon1_coordinate[1] >> polygon1_coordinate[2];
		stlfile >> dust >> polygon2_coordinate[0] >> polygon2_coordinate[1] >> polygon2_coordinate[2];
		stlfile >> dust >> polygon3_coordinate[0] >> polygon3_coordinate[1] >> polygon3_coordinate[2];
		stlfile >> dust;
		stlfile >> dust;

		//�����o�ϐ��֓��꒼�����
		normal_coordinate_x.emplace_back(normal_coordinate[0]);
		normal_coordinate_y.emplace_back(normal_coordinate[1]);
		normal_coordinate_z.emplace_back(normal_coordinate[2]);
		polygon_coordinate1_x.emplace_back(polygon1_coordinate[0]);
		polygon_coordinate1_y.emplace_back(polygon1_coordinate[1]);
		polygon_coordinate1_z.emplace_back(polygon1_coordinate[2]);
		polygon_coordinate2_x.emplace_back(polygon2_coordinate[0]);
		polygon_coordinate2_y.emplace_back(polygon2_coordinate[1]);
		polygon_coordinate2_z.emplace_back(polygon2_coordinate[2]);
		polygon_coordinate3_x.emplace_back(polygon3_coordinate[0]);
		polygon_coordinate3_y.emplace_back(polygon3_coordinate[1]);
		polygon_coordinate3_z.emplace_back(polygon3_coordinate[2]);
	



		
		polygon_number++;


	}

	stlfile.close();
	make_spo_vertices();
	make_spo_triangles();

}



//�|���S���̒��_����spo�p�ɓZ�߂�B���O������킵��
void LOAD_STLMODEL::make_spo_vertices() {
	int allloop_vertices_number = polygon_number * 9;
	spo_vertices = new float[allloop_vertices_number];

	for (int i=0; i < polygon_number; i++) {
		spo_vertices[(i * 9) + 0] = polygon_coordinate1_x[i];
		spo_vertices[(i * 9) + 1] = polygon_coordinate1_y[i];
		spo_vertices[(i * 9) + 2] = polygon_coordinate1_z[i];
		spo_vertices[(i * 9) + 3] = polygon_coordinate2_x[i];
		spo_vertices[(i * 9) + 4] = polygon_coordinate2_y[i];
		spo_vertices[(i * 9) + 5] = polygon_coordinate2_z[i];
		spo_vertices[(i * 9) + 6] = polygon_coordinate3_x[i];
		spo_vertices[(i * 9) + 7] = polygon_coordinate3_y[i];
		spo_vertices[(i * 9) + 8] = polygon_coordinate3_z[i];
		//cout << polygon_coordinate1_x[i] << endl;
		//cout << SC_vertices[(i * 9) + 0] << endl;

	}

	spo_vertices_num = allloop_vertices_number/3;
}

//�|���S���̒��_�̊֘A����SC�p�ɂ܂Ƃ߂�BSTL�f�[�^�̓|���S���X�[�v�Ȃ̂ōl�����Ȃ�
void LOAD_STLMODEL::make_spo_triangles() {
	int allloop_triangles_number = polygon_number *3;
	spo_triangles = new SCint[allloop_triangles_number];

	for (int i = 0; i < polygon_number; i++) {
		spo_triangles[(i*3) + 0] = normal_coordinate_x[i];
		spo_triangles[(i*3) + 1] = normal_coordinate_y[i];
		spo_triangles[(i*3) + 2] = normal_coordinate_z[i];
	}


	spo_triangles_num = allloop_triangles_number/3;
}

int LOAD_STLMODEL::get_polygon_number() {
	return polygon_number;
}

void LOAD_STLMODEL::use_spo(SPOObject obj) {
	printf("�w�C���O�xclose judge = %d (0:nonClosed  1:Closed)\n",obj.IsClosed());

	if (obj.AddTriangles(spo_vertices, spo_vertices_num, spo_triangles, spo_triangles_num) != SC_NO_ERROR) {
		
		printf("piece count = %d\n", obj.GetPieceCount());
		obj.ConnectVertices(0.001);
		obj.SplitEdges(0.01, 5, true);
		obj.RemoveRedundantVertices(0.01, 5, true);
		obj.ChangeTriangulationPattern(SPO_TRIANGULATION_TYPE_REDUCE_AREA_DIFFERENCE, 1.0, 5);
		obj.DecomposeIntoSingleBoundaryPieces();
		printf("piece count = %d\n", obj.GetPieceCount());
		for (int i = 0; i < obj.GetPieceCount(); i++) {
			if (obj.IsClosed(i) != true) {
				printf("piece index %d\n", i);
				printf("**Closed�ȃ��f���ɂȂ��Ă��܂���DConnectVertices�̃p�����[�^���čl���Ă�������**\n");
			}
		}
		printf("�w�C����xclose judge = %d (0:nonClosed  1:Closed)\n", obj.IsClosed());

		int j = 0, k = 0;
		for (int i = 0; i < obj.GetPieceCount(); i++) {
			const SPOPiece *temp = obj.GetPiece(i);
			//sc_cutting_edge.AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON, temp->vertices, temp->vertexSize,temp->triangles, temp->triangleSize);
			j += temp->vertexSize;
			k += temp->triangleSize;
			printf("\n���H��f���I�u�W�F�N�g�̏C����\n");
			printf("�C���O ==> ���_��:%d, �|���S����:%d\n", spo_vertices_num, get_polygon_number());
			printf("�C���� ==> ���_��:%d, �|���S����:%d\n\n", j, k);
		}
	}
	else {cout<< "error"<<endl; }
}