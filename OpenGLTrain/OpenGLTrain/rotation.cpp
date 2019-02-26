#include<math.h>

////////////////////////////////////////////////////
//クォータニオンから回転軸と軸ベクトルを求める関数
//float quaternion[4]はwxyzの順
//float axisvector[4]はθxyzの順で返してる
////////////////////////////////////////////////////

void QuaternionToAxisVector(float quaternion[4], float axisvector[4]) {
	axisvector[0] = 2 * acos(quaternion[0]);
	axisvector[1] = quaternion[1] / sin(axisvector[0]);
	axisvector[2] = quaternion[2] / sin(axisvector[0]);
	axisvector[3] = quaternion[3] / sin(axisvector[0]);

}

