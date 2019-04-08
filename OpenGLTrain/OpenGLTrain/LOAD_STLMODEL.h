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


	//getter���̖ʓ|������̂Ńp�u���b�N�ɁE�E�E
public:
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
	int get_polygon_number();

	//�X�}�[�g�R���W�����I�v�e�B�}�C�U�[�p
	//������ւ�͐��̃V�X�e�����p
	std::vector<float>stlvertex;
	std::vector<float> spo_polygon_coordinate;
	int trianglesvertexnum2[10000]; //���_�p�C���f�b�N�X�ԍ�

	int spo_polygon_number;

	void use_spo(SPOObject obj);
	void make_spo_vertices();
	void make_spo_triangles();
	void delede_same_coordinate();
	void labeling();
	//�X�}�[�g�R���W�����p




	//�X�}�[�g�R���W�����p
	SPOfloat *spo_vertices;
	SPOint *spo_triangles;
	SPOint spo_vertices_num;
	SPOint spo_triangles_num;


};

