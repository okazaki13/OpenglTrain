#pragma once
#include<string>
#include<vector>

#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

class LOAD_STLMODEL
{
private:

	std::string dust;//����Ȃ����̊i�[�p�B���x���g���܂킷�B
	std::string modeltype;//��{�\���b�h���f��
	std::string filename;
	int polygon_number; //���v�|���S����




	//[�|���S������][���W�l]
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

	//�X�}�[�g�R���W�����p
	void make_SC_vertices();
	void make_SC_triangles();

	//�X�}�[�g�R���W�����p
	SCfloat* SC_vertices;
	SCint* SC_triangles;
	SCint SC_vertices_num;
	SCint SC_triangles_num;


};
