#pragma once
class Tool
{
private:
	float endmill_D = 10; //H‹ï’¼Œa[mm]
	int endmill_R = endmill_D * 0.5;

public:
	Tool();
	~Tool();

	float get_endmill_D();


	void create_ballendmill(int offset[2]);
	void create_ballendmill(int offset_x, int offset_y, int offset_z);
	void drawCylinder(float radius, float height, int slides);
};

