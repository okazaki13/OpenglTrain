#pragma once
#include "../../include/SpidarAHS/SpidarAHS.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "SettingValue.h"

extern SPIDAR_HANDLE spidar;

//extern float spidar_origin_quaternion[4];//�N�H�[�^�j�I��
//extern float spidar_origin_position[3];//�ʒu
//extern float spidar_origin_velocity[3];//���x

extern float spidar_position[3];//�ʒu,OpenGL���W�n
extern float spidar_quaternion[4];//��],OpenGL�p�E����W�n

extern bool cube_existence[VOXEL_NUMBER_X][VOXEL_NUMBER_Y][VOXEL_NUMBER_Z];

extern SCObject sc_cutting_edge;
extern SCObject sc_shank;
extern SCObject sc_holder;
extern SCObject SC_cube[VOXEL_NUMBER_X][VOXEL_NUMBER_Y][VOXEL_NUMBER_Z];

