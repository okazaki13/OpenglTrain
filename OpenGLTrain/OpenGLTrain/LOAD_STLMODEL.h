#pragma once
#include<string>
#include<vector>

#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

class LOAD_STLMODEL
{
private:

	std::string dust;//いらない情報の格納用。何度も使いまわす。
	std::string modeltype;//基本ソリッドモデル
	std::string filename;
	int polygon_number; //合計ポリゴン数


	//getter作るの面倒すぎるのでパブリックに・・・
public:
	//[ポリゴン枚数][座標値]
	std::vector<float> normal_coordinate_x;
	std::vector<float> normal_coordinate_y;
	std::vector<float> normal_coordinate_z;
	std::vector<float>polygon_coordinate1_x;
	std::vector<float>polygon_coordinate1_y;
	std::vector<float>polygon_coordinate1_z;
	std::vector<float>polygon_coordinate2_x;
	std::vector<float>polygon_coordinate2_y;
	std::vector<float>polygon_coordinate2_z;
	std::vector<float>polygon_coordinate3_x;
	std::vector<float>polygon_coordinate3_y;
	std::vector<float>polygon_coordinate3_z;





public:
	LOAD_STLMODEL();
	~LOAD_STLMODEL();

	void get_stl(std::string filepass);
	int get_polygon_number();

	//スマートコリジョンオプティマイザー用
	//ここらへんは先代のシステム流用
	std::vector<float>stlvertex;
	std::vector<float> spo_polygon_coordinate;
	int trianglesvertexnum2[10000]; //頂点用インデックス番号

	int spo_polygon_number;

	void use_spo(SPOObject obj);
	void make_spo_vertices();
	void make_spo_triangles();
	void delede_same_coordinate();
	void labeling();
	//スマートコリジョン用




	//スマートコリジョン用
	SPOfloat *spo_vertices;
	SPOint *spo_triangles;
	SPOint spo_vertices_num;
	SPOint spo_triangles_num;


};

