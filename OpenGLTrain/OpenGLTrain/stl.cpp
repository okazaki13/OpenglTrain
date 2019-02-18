#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"

#include "LOAD_STLMODEL.h"

using namespace std;

void create_cutting_edge() {
	LOAD_STLMODEL cutting_edge;
	cutting_edge.get_stl("../../STLmodel/ênêÊÉÇÉfÉã.STL");

	SCObject SC_cutting_edge;
	SC_cutting_edge.AddTriangles(cutting_edge.SC_vertices, cutting_edge.SC_vertices_num,cutting_edge.SC_triangles,cutting_edge.SC_triangles_num);
	
}