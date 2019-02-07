#pragma once
#include <vector>
//using namespace std �w�b�_�t�@�C���ł͌�@�x�炵��

class Voxel
{
	/*�{�N�Z������邽�߂̃N���X
	�J���[�ƃT�C�Y���Z�b�g���Đ���
	*/
public:
	Voxel();
	~Voxel();
	void create_voxel(int offset[2]);
	void create_voxel(int offset_x,int offset_y,int offset_z);
	void set_voxelcolor(double R,double G,double B);
	void set_voxelsize(double size);
	void CreateVoxelObject(int a, int b, int c);

private:
	int centor[3];//�{�N�Z�����S�_
	float color[4];//�{�N�Z���̐F.�����͂S��RGBA�iA�͓����x�j
	double size;//�{�N�Z���̑傫��
	std::vector<std::vector<std::vector<bool>>> voxelID;//int�^�R�����z��Ń{�N�Z�����ꂼ��̗L�����Ǘ�



	



};

