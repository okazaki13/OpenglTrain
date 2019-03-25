#include"Declaration.h"
#include"GlobalVariable.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"


bool cube_existence[VOXEL_NUMBER_X][VOXEL_NUMBER_Y][VOXEL_NUMBER_Z];

void calcloop(int value){
	SCSceneManager scene(SC_SCENE_MANAGER_TRIANGLE_SOUP);

	
	scene.AddObject(1, &sc_cutting_edge);
	scene.AddObject(2, &sc_shank);
	scene.AddObject(3, &sc_holder);

	scene.AddObjectToGroup(1, 0);//工具刃先グループ
	scene.AddObjectToGroup(2, 1);//工具刃先以外のグループ
	scene.AddObjectToGroup(3, 1);//工具刃先以外のグループ

	int counter = 4;
	for (int i = 0; i < VOXEL_NUMBER_X; i++) {
		for (int j = 0; j < VOXEL_NUMBER_Y; j++) {
			for (int k = 0; k < VOXEL_NUMBER_Z; k++) {
				if (cube_existence[i][j][k]) {
					scene.AddObject(counter, &SC_cube[i][j][k]);
					scene.AddObjectToGroup(counter, 2);//工具刃先以外のグループ
					counter++;
				}
			}
		}
	}

	make_SC_tool(scene);//コリジョンの移動
}