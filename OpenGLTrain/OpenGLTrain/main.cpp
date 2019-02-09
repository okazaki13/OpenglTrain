#include"Declaration.h"
#include <GL/glut.h>
#include "../../include/SpidarAHS/SpidarAHS.h"
#pragma comment(lib,"../../Release/SpidarAHS.lib")
#pragma comment(lib,"../../Debug/SpidarAHS.lib")

#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/lib/sc.lib")
#pragma comment(lib,"../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/lib/spo.lib")

#include <stdio.h>


//----------------------------------------------------
// ÉÅÉCÉìä÷êî
//----------------------------------------------------
int main(int argc, char *argv[]) {


	


	check_spidar_being();



	openGL_setup(argc, argv);
	glutMainLoop();

	return 0;
}





								
