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
	//make_spo_vertices();
	//make_spo_triangles();

}



//�|���S���̒��_����spo�p�ɓZ�߂�B���O������킵��
void LOAD_STLMODEL::make_spo_vertices() {
	int all_vertices_number = polygon_number * 9;
	//spo_vertices = new SPOfloat[allloop_vertices_number];
	spo_vertices = (SPOfloat *)malloc(sizeof(float) * all_vertices_number);
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

	spo_vertices_num = all_vertices_number/3;
}

//�|���S���̒��_�̊֘A����SC�p�ɂ܂Ƃ߂�BSTL�f�[�^�̓|���S���X�[�v�Ȃ̂œK����1���珇�Ƀ|���S�������i�[
void LOAD_STLMODEL::make_spo_triangles() {
	int all_triangles_number = polygon_number *3;
	/*spo_triangles = new SPOint[all_triangles_number];*/
	spo_triangles = (SPOint *)malloc(sizeof(int) * all_triangles_number);

	for (int i = 0; i < polygon_number; i++) {
		spo_triangles[3 * i + 0] = i;
		spo_triangles[3 * i + 1] = i+1;
		spo_triangles[3 * i + 2] = i+2;

	}


	spo_triangles_num = polygon_number;
}

int LOAD_STLMODEL::get_polygon_number() {
	return polygon_number;
}

void LOAD_STLMODEL::use_spo(SPOObject obj) {
	
	printf("�w�C���O�xclose judge = %d (0:nonClosed  1:Closed)\n",obj.IsClosed());

	if (obj.AddTriangles(spo_vertices, spo_vertices_num, spo_triangles, spo_triangles_num) != SC_NO_ERROR) {
		cout << "error" << endl;
		
	}
	else {
		printf("piece count = %d\n", obj.GetPieceCount());
		obj.ConnectVertices(0);
		
		//obj.SplitEdges(0.01, 5, true);
		//obj.RemoveRedundantVertices(0.01, 5, true);
		//obj.ChangeTriangulationPattern(SPO_TRIANGULATION_TYPE_REDUCE_AREA_DIFFERENCE, 1.0, 5);
		obj.CloseHoles();
		//obj.DecomposeIntoSingleBoundaryPieces();//�s�[�X�̕���
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
}

//�ȉ��~�Î��̗��p�B�悭�����ł��Ă��炸
//void LOAD_STLMODEL::delede_same_coordinate() {
//	//bool same=0;
//	//spo_polygon_number = 0;
//	//for (int i=0; i < polygon_number; i++) {
//	//	for (int d=i+1; d < polygon_number - i-1; d++) {
//	//		if (polygon_coordinate1_x[i] == polygon_coordinate1_x[d] ||
//	//			polygon_coordinate1_y[i] == polygon_coordinate1_y[d] ||
//	//			polygon_coordinate1_z[i] == polygon_coordinate1_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate1_x[i] == polygon_coordinate2_x[d] ||
//	//			polygon_coordinate1_y[i] == polygon_coordinate2_y[d] ||
//	//			polygon_coordinate1_z[i] == polygon_coordinate2_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate1_x[i] == polygon_coordinate3_x[d] ||
//	//			polygon_coordinate1_y[i] == polygon_coordinate3_y[d] ||
//	//			polygon_coordinate1_z[i] == polygon_coordinate3_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate2_x[i] == polygon_coordinate1_x[d] ||
//	//			polygon_coordinate2_y[i] == polygon_coordinate1_y[d] ||
//	//			polygon_coordinate2_z[i] == polygon_coordinate1_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate2_x[i] == polygon_coordinate2_x[d] ||
//	//			polygon_coordinate2_y[i] == polygon_coordinate2_y[d] ||
//	//			polygon_coordinate2_z[i] == polygon_coordinate2_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate2_x[i] == polygon_coordinate3_x[d] ||
//	//			polygon_coordinate2_y[i] == polygon_coordinate3_y[d] ||
//	//			polygon_coordinate2_z[i] == polygon_coordinate3_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate3_x[i] == polygon_coordinate1_x[d] ||
//	//			polygon_coordinate3_y[i] == polygon_coordinate1_y[d] ||
//	//			polygon_coordinate3_z[i] == polygon_coordinate1_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate3_x[i] == polygon_coordinate2_x[d] ||
//	//			polygon_coordinate3_y[i] == polygon_coordinate2_y[d] ||
//	//			polygon_coordinate3_z[i] == polygon_coordinate2_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//		if (polygon_coordinate3_x[i] == polygon_coordinate3_x[d] ||
//	//			polygon_coordinate3_y[i] == polygon_coordinate3_y[d] ||
//	//			polygon_coordinate3_z[i] == polygon_coordinate3_z[d]) {
//	//			same = 1;
//	//			break;
//	//		}
//	//	}
//
//	//
//	//	if (same == 0) {
//	//		spo_polygon_coordinate1_x.emplace_back(polygon_coordinate1_x[i]);
//	//		spo_polygon_coordinate1_y.emplace_back(polygon_coordinate1_y[i]);
//	//		spo_polygon_coordinate1_z.emplace_back(polygon_coordinate1_z[i]);
//	//		spo_polygon_coordinate2_x.emplace_back(polygon_coordinate2_x[i]);
//	//		spo_polygon_coordinate2_y.emplace_back(polygon_coordinate2_y[i]);
//	//		spo_polygon_coordinate2_z.emplace_back(polygon_coordinate2_z[i]);
//	//		spo_polygon_coordinate3_x.emplace_back(polygon_coordinate3_x[i]);
//	//		spo_polygon_coordinate3_y.emplace_back(polygon_coordinate3_y[i]);
//	//		spo_polygon_coordinate3_z.emplace_back(polygon_coordinate3_z[i]);
//	//		spo_polygon_number++;
//	//	}
//	//	else {
//	//		same = 0;
//	//	}
//	//}
//	
//	
//	for (int i = 0; i < polygon_number; i++) {
//		spo_polygon_coordinate[3 * i]=polygon_coordinate1_x[i];
//		spo_polygon_coordinate[3 * i + 1] = polygon_coordinate1_y[i];
//		spo_polygon_coordinate[3 * i + 2] = polygon_coordinate1_z[i];
//		spo_polygon_coordinate[3 * i + 3] = polygon_coordinate2_x[i];
//		spo_polygon_coordinate[3 * i + 4] = polygon_coordinate2_y[i];
//		spo_polygon_coordinate[3 * i + 5] = polygon_coordinate2_z[i];
//		spo_polygon_coordinate[3 * i + 6] = polygon_coordinate3_x[i];
//		spo_polygon_coordinate[3 * i + 7] = polygon_coordinate3_y[i];
//		spo_polygon_coordinate[3 * i + 8] = polygon_coordinate3_z[i];
//	}
//
//	spo_vertices[0] = spo_polygon_coordinate[0];
//	spo_vertices[1] = spo_polygon_coordinate[1];
//	spo_vertices[2] = spo_polygon_coordinate[2];
//	spo_vertices[3] = spo_polygon_coordinate[3];
//	spo_vertices[4] = spo_polygon_coordinate[4];
//	spo_vertices[5] = spo_polygon_coordinate[5];
//	spo_vertices[6] = spo_polygon_coordinate[6];
//	spo_vertices[7] = spo_polygon_coordinate[7];
//	spo_vertices[8] = spo_polygon_coordinate[8];
//
//	trianglesvertexnum2[0] = 0;
//	trianglesvertexnum2[1] = 1;
//	trianglesvertexnum2[2] = 2;
//
//	spo_vertices_num = 3;
//
//	bool hantei=0;
//	float temporary[3];
//	for (int d = 3; d <= polygon_number * 3; d++) {//stlfacevertex[d]�̍��W�ŏd�����Ȃ����J�E���g
//		for (int c = 0; c < d; c++) {
//			if (spo_polygon_coordinate[3 * d] == spo_vertices[3 * c]
//				&& spo_polygon_coordinate[3 * d + 1] == spo_vertices[3 * c + 1]
//				&& spo_polygon_coordinate[3 * d + 2] == spo_vertices[3 * c + 2]) {
//
//				hantei++;
//				//printf("���Ԃ��Ă܂� \n");
//				break;
//
//			}
//			else {
//				temporary[0] = spo_polygon_coordinate[3 * d];
//				temporary[1] = spo_polygon_coordinate[3 * d + 1];
//				temporary[2] = spo_polygon_coordinate[3 * d + 2];
//				//printf("vvtest \n");
//			}
//			//printf("%e %e %e \n",temporary[0],temporary[1],temporary[2]);
//			//printf("\n[%d]  %d\n",d, hantei);
//
//		}
//		if (hantei == 0) {
//			spo_vertices[3 * spo_vertices_num] = temporary[0];
//			spo_vertices[3 * spo_vertices_num + 1] = temporary[1];
//			spo_vertices[3 * spo_vertices_num + 2] = temporary[2];
//			trianglesvertexnum2[spo_vertices_num] = spo_vertices_num;
//			spo_vertices_num++;
//			hantei = 0;
//			//printf("�i�[���܂���");
//		}
//
//	}
//
//
//}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//�|���S���̊e���_�Ƀ��x�����O����
//void LOAD_STLMODEL::labeling() {
//
//	int c;
//	int d;
//
//	spo_triangles = new int[3 * polygon_number];  // �������̈�̊m�� 
//
//
//
//
//	for (c = 0; c < 3 * polygon_number; c++) {
//
//		for (d = 0; d < spo_vertices_num; d++) {
//			if (   spo_polygon_coordinate[3 * c + 0] == stlvertex[3 * d]
//				&& spo_polygon_coordinate[3 * c + 1] == stlvertex[3 * d + 1]
//				&& spo_polygon_coordinate[3 * c + 2] == stlvertex[3 * d + 2])
//			{
//				spo_triangles[c] = trianglesvertexnum2[d];
//				//trianglesindex[c]=trianglesvertexnum1[d];
//
//				break;
//			}
//		}
//	}
//	
//	spo_triangles_num = polygon_number;
//}