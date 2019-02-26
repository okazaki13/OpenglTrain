#include<math.h>

////////////////////////////////////////////////////
//�N�H�[�^�j�I�������]���Ǝ��x�N�g�������߂�֐�
//float quaternion[4]��wxyz�̏�
//float axisvector[4]�̓�xyz�̏��ŕԂ��Ă�
////////////////////////////////////////////////////

void QuaternionToAxisVector(float quaternion[4], float axisvector[4]) {
	axisvector[0] = 2 * acos(quaternion[0]);
	axisvector[1] = quaternion[1] / sin(axisvector[0]);
	axisvector[2] = quaternion[2] / sin(axisvector[0]);
	axisvector[3] = quaternion[3] / sin(axisvector[0]);

}

