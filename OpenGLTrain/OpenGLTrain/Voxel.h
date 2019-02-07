#pragma once
#include <vector>
//using namespace std ヘッダファイルでは御法度らしい

class Voxel
{
	/*ボクセルを作るためのクラス
	カラーとサイズをセットして生成
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
	int centor[3];//ボクセル中心点
	float color[4];//ボクセルの色.引数は４つでRGBA（Aは透明度）
	double size;//ボクセルの大きさ
	std::vector<std::vector<std::vector<bool>>> voxelID;//int型３次元配列でボクセルそれぞれの有無を管理



	



};

