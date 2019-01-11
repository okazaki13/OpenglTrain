#pragma once
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

private:
	int centor[2];
	int position[2];
	double color[2];
	double size;




	



};

