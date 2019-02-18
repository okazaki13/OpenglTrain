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
		cout << filepass << "が読み込めませんでしたよー" << endl;
	}

	getline(stlfile, filename);
	stlfile >> modeltype >> filename;



	while (!stlfile.eof()) {
		stlfile >> dust >> dust >> normal_coordinate[0] >> normal_coordinate[1] >> normal_coordinate[2];
		stlfile >> dust >> dust;
		stlfile >> dust >> polygon1_coordinate[0] >> polygon1_coordinate[1] >> polygon1_coordinate[2];
		stlfile >> dust >> polygon2_coordinate[0] >> polygon2_coordinate[1] >> polygon2_coordinate[2];
		stlfile >> dust >> polygon3_coordinate[0] >> polygon3_coordinate[1] >> polygon3_coordinate[2];
		stlfile >> dust;
		stlfile >> dust;

		//メンバ変数へ入れ直し作業
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

	stlfile.close;
	make_SC_vertices();
	make_SC_triangles();

}



//ポリゴンの頂点情報をSC用に纏める。名前が紛らわしい
void LOAD_STLMODEL::make_SC_vertices() {
	int allloop_vertices_number = polygon_number * 9;
	SC_vertices = new float[allloop_vertices_number];

	for (int i=0; i < polygon_number; i++) {
		SC_vertices[(i * 9) + 0] = polygon_coordinate1_x[i];
		SC_vertices[(i * 9) + 1] = polygon_coordinate1_y[i];
		SC_vertices[(i * 9) + 2] = polygon_coordinate1_z[i];
		SC_vertices[(i * 9) + 3] = polygon_coordinate2_x[i];
		SC_vertices[(i * 9) + 4] = polygon_coordinate2_y[i];
		SC_vertices[(i * 9) + 5] = polygon_coordinate2_z[i];
		SC_vertices[(i * 9) + 6] = polygon_coordinate3_x[i];
		SC_vertices[(i * 9) + 7] = polygon_coordinate3_y[i];
		SC_vertices[(i * 9) + 8] = polygon_coordinate3_z[i];
	}

	SC_vertices_num = allloop_vertices_number;
}

//ポリゴンの頂点の関連性をSC用にまとめる。STLデータはポリゴンスープなので考慮しない
void LOAD_STLMODEL::make_SC_triangles() {
	int allloop_triangles_number = polygon_number * 3;
	SC_triangles = new SCint[allloop_triangles_number];



	SC_triangles_num = allloop_triangles_number;
}