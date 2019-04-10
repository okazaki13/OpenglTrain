#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include"Declaration.h"
#include "LOAD_STLMODEL.h"
#include"GlobalVariable.h"
#include"SettingValue.h"
#include <GL/glut.h>
#include <iostream>


using namespace std;


#define DISP_LIST_INDEX1 1//切れ刃モデルのディスプレイリスト
#define DISP_LIST_INDEX2 2//シャンクモデルのディスプレイリスト
#define DISP_LIST_INDEX3 3//ホルダーモデルのディスプレイリスト

SCSceneManager scene(SC_SCENE_MANAGER_TRIANGLE_SOUP);
SPOObject spo_cutting_edge;
SPOObject spo_shank;
SPOObject spo_holder;
SPOObject spo_cube;

SCObject sc_cutting_edge;
SCObject sc_shank;
SCObject sc_holder;


void ready_tool_edge() {




	////工具刃先の描画とコリジョン設定
	LOAD_STLMODEL cutting_edge;
	cutting_edge.get_stl("../../STLmodel/cutting_edge.STL");
	glNewList(DISP_LIST_INDEX1, GL_COMPILE); //コンパイルのみ

	glColor4f(0.0, 1.0, 0.0, 1.0);	// 多角形の色(RGBA)
	glBegin(GL_TRIANGLES);				// 多角形の描画

	for (int i = 0; i < cutting_edge.get_polygon_number(); i++) {
		glNormal3f(cutting_edge.normal_coordinate_x[i], cutting_edge.normal_coordinate_y[i], cutting_edge.normal_coordinate_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate1_x[i], cutting_edge.polygon_coordinate1_y[i], cutting_edge.polygon_coordinate1_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate2_x[i], cutting_edge.polygon_coordinate2_y[i], cutting_edge.polygon_coordinate2_z[i]);
		glVertex3f(cutting_edge.polygon_coordinate3_x[i], cutting_edge.polygon_coordinate3_y[i], cutting_edge.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();
	//cutting_edge.delede_same_coordinate();
	//cutting_edge.labeling();

	cutting_edge.make_spo_vertices();
	cutting_edge.make_spo_triangles();
	cutting_edge.use_spo(spo_cutting_edge);

	//printf("『修正前』close judge = %d (0:nonClosed  1:Closed)\n", spo_cutting_edge.IsClosed());
	//
	//if (spo_cutting_edge.AddTriangles(cutting_edge.SC_vertices, cutting_edge.SC_vertices_num, cutting_edge.SC_triangles, cutting_edge.SC_triangles_num) != SC_NO_ERROR) {};
	//spo_cutting_edge.ConnectVertices(0.001);
	//spo_cutting_edge.SplitEdges(0.01, 5, true);
	//spo_cutting_edge.RemoveRedundantVertices(0.01, 5, true);
	//spo_cutting_edge.ChangeTriangulationPattern(SPO_TRIANGULATION_TYPE_REDUCE_AREA_DIFFERENCE, 1.0, 5);
	//spo_cutting_edge.DecomposeIntoSingleBoundaryPieces();
	//printf("piece count = %d\n", spo_cutting_edge.GetPieceCount());
	//for (int i = 0; i < spo_cutting_edge.GetPieceCount(); i++) {
	//	if (spo_cutting_edge.IsClosed(i) != true) {
	//		printf("piece index %d\n", i);
	//		printf("**Closedなモデルになっていません．ConnectVerticesのパラメータを再考してください**\n");
	//	}
	//}
	//printf("『修正後』close judge = %d (0:nonClosed  1:Closed)\n", spo_cutting_edge.IsClosed());

	//int j = 0,k = 0;
	//for (int i = 0; i < spo_cutting_edge.GetPieceCount(); i++) {
	//	const SPOPiece *temp = spo_cutting_edge.GetPiece(i);
	//	sc_cutting_edge.AddTriangles(SC_OBJECT_TYPE_CLOSED_POLYHEDRON, temp->vertices, temp->vertexSize,
	//		temp->triangles, temp->triangleSize);
	//	j += temp->vertexSize;
	//	k += temp->triangleSize;
	//	printf("\n◇工具モデルオブジェクトの修正◇\n");
	//	printf("修正前 ==> 頂点数:%d, ポリゴン数:%d\n", cutting_edge.SC_vertices_num, cutting_edge.get_polygon_number());
	//	printf("修正後 ==> 頂点数:%d, ポリゴン数:%d\n\n", j, k);

	//}

	/////工具刃先ここまで

}
void ready_tool_shank() {

	/////工具シャンク部の描画とコリジョン設定
	LOAD_STLMODEL shank;
	shank.get_stl("../../STLmodel/shank.STL");
	glNewList(DISP_LIST_INDEX2, GL_COMPILE); //コンパイルのみ

	glColor4f(0.3, 0.7, 0.3, 0.3);	// 多角形の色(RGBA)
	glBegin(GL_TRIANGLES);				// 多角形の描画

	for (int i = 0; i < shank.get_polygon_number(); i++) {
		glNormal3f(shank.normal_coordinate_x[i], shank.normal_coordinate_y[i], shank.normal_coordinate_z[i]);
		glVertex3f(shank.polygon_coordinate1_x[i], shank.polygon_coordinate1_y[i], shank.polygon_coordinate1_z[i]);
		glVertex3f(shank.polygon_coordinate2_x[i], shank.polygon_coordinate2_y[i], shank.polygon_coordinate2_z[i]);
		glVertex3f(shank.polygon_coordinate3_x[i], shank.polygon_coordinate3_y[i], shank.polygon_coordinate3_z[i]);
	}
	glEnd();
	glEndList();


	shank.make_spo_vertices();
	shank.make_spo_triangles();
	shank.use_spo(spo_shank);


	/////工具シャンクここまで
}


void ready_tool_holder(){

	//////工具ホルダー部の描画とコリジョン設定
	//LOAD_STLMODEL holder;
	//holder.get_stl("../../STLmodel/holder.STL");
	//glNewList(DISP_LIST_INDEX3, GL_COMPILE); //コンパイルのみ

	//glColor4f(0.3, 0.7, 0.3, 0.7);	// 多角形の色(RGBA)
	//glBegin(GL_TRIANGLES);				// 多角形の描画

	//for (int i = 0; i < holder.get_polygon_number(); i++) {
	//	glNormal3f(holder.normal_coordinate_x[i], holder.normal_coordinate_y[i], holder.normal_coordinate_z[i]);
	//	glVertex3f(holder.polygon_coordinate1_x[i], holder.polygon_coordinate1_y[i], holder.polygon_coordinate1_z[i]);
	//	glVertex3f(holder.polygon_coordinate2_x[i], holder.polygon_coordinate2_y[i], holder.polygon_coordinate2_z[i]);
	//	glVertex3f(holder.polygon_coordinate3_x[i], holder.polygon_coordinate3_y[i], holder.polygon_coordinate3_z[i]);
	//}
	//glEnd();
	//glEndList();

	//
	//SC_shank.AddTriangles(holder.SC_vertices, holder.SC_vertices_num, holder.SC_triangles, holder.SC_triangles_num);

	//////工具ホルダー部ここまで
}



void ready_cube() {
	/////工具シャンク部の描画とコリジョン設定
	LOAD_STLMODEL cube;
	cube.get_stl("../../STLmodel/cube.STL");




	cube.make_spo_vertices();
	cube.make_spo_triangles();
	cube.use_spo(spo_cube);


	/////工具シャンクここまで
}



















//float spidar_origin_position[3];
//float spidar_origin_quaternion[4];
void make_tool() {
	////位置	
	//float position[3];
	//position[0] = spidar_position[0];
	//position[1] = spidar_position[1];
	//position[2] = spidar_position[2];
	
	//姿勢
	float axis_vector[4];//クォータニオンを回転軸ベクトルと回転方向に変換したものを入れる

	QuaternionToAxisVector(spidar_quaternion, axis_vector);

	glPushMatrix();
	glColor4f(0.7, 0.2, 0.2, 0.5);	// 多角形の色(RGBA)
	

	glTranslatef(spidar_position[0], spidar_position[1], spidar_position[2]);//平行移動値の設定。スパイダーのxyzと座標系を摺合せ

	glRotatef( (RadianToDegree(axis_vector[0]))*3, axis_vector[1], axis_vector[2], axis_vector[3]);
	
	
	glCallList(DISP_LIST_INDEX1);
	glCallList(DISP_LIST_INDEX2);
	glCallList(DISP_LIST_INDEX3);
	glPopMatrix();
	//cout << "ここまで" << endl;

}
void make_SC_tool(SCSceneManager &scene) {
	//姿勢
	float axis_vector[4];//クォータニオンを回転軸ベクトルと回転方向に変換したものを入れる

	QuaternionToAxisVector(spidar_quaternion, axis_vector);

	scene.SetTransformation(1, SC_POSITION_ORIGIN, spidar_position);
	scene.SetTransformation(2, SC_POSITION_ORIGIN, spidar_position);


}

