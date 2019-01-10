#pragma once
class Voxel
{
public:
	Voxel();
	~Voxel();
	void create_voxel(int offset[2]);
	void create_voxel(int offset_x,int offset_y,int offset_z);
	void set_voxelcolor(double R,double G,double B);

private:
	int centor[2];
	int position[2];
	double color[2];



	



};

