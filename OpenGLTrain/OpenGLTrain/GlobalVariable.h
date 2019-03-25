#pragma once
#include "../../include/SpidarAHS/SpidarAHS.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "SettingValue.h"

extern SPIDAR_HANDLE spidar;

//extern float spidar_origin_quaternion[4];//クォータニオン
//extern float spidar_origin_position[3];//位置
//extern float spidar_origin_velocity[3];//速度

extern float spidar_position[3];//位置,OpenGL座標系
extern float spidar_quaternion[4];//回転,OpenGL用右手座標系

extern bool cube_existence[VOXEL_NUMBER_X][VOXEL_NUMBER_Y][VOXEL_NUMBER_Z];

extern SCObject sc_cutting_edge;
extern SCObject sc_shank;
extern SCObject sc_holder;
extern SCObject SC_cube[VOXEL_NUMBER_X][VOXEL_NUMBER_Y][VOXEL_NUMBER_Z];

