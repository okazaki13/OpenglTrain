#pragma once
#include "../../include/SpidarAHS/SpidarAHS.h"

extern SPIDAR_HANDLE spidar;

//extern float spidar_origin_quaternion[4];//クォータニオン
//extern float spidar_origin_position[3];//位置
//extern float spidar_origin_velocity[3];//速度

extern float spidar_position[3];//位置,OpenGL座標系
extern float spidar_quaternion[4];//回転,OpenGL用右手座標系