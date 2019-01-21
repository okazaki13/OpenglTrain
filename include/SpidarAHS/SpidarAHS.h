/** @file
	@JP
		@brief SpidarAHS �֐���`
		@author �ԉH ���m

		Spidar�𗘗p���邽�߂�C++�֐�API

	@END_JP
	@EN
		@brief SpidarAHS C++ function
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/7/28
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/

#pragma once

#ifdef SPIDARAHS_EXPORTS
#define SPIDARAHS_API __declspec(dllexport)
#else
#define SPIDARAHS_API __declspec(dllimport)
#endif

#include <windows.h>

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidar�̎��ʗp�n���h���D<br>
	�R���g���[��1��ɑ΂���1�̃n���h�����Ή�����D<br>
	<b>SPIDAR-G�̂Ƃ��i8�{���ŕ��i3���R�x�E��]3���R�x�j</b><br>
	�R���g���[��1��ɑ΂���1�g��SPIDAR�����s�\ AHS_SPIDAR_G, ahsCreate_SpidarG()<br>
	<b>SPIDAR-4�̂Ƃ��i4�{���ŕ��i3���R�x�j</b><br>
	�R���g���[��1��ɑ΂���2�g��SPIDAR�����s�\ AHS_SPIDAR_4, ahsCreate_Spidar4()<br>
	<b>SPIDAR-X�̂Ƃ��i8�{����Ɨ��ɑ���j</b><br>
	�R���g���[��1��ɑ΂���8�g��SPIDAR�����s�\ AHS_SPIDAR_X, ahsCreate_SpidarX()<br>
@END_JP
@EN
	@brief Spidar handle
@END_EN
*/
typedef HANDLE SPIDAR_HANDLE;



/**
@JP
	@brief ��������SPIDAR�^�C�v
@END_JP
@EN
	@brief 
@END_EN
*/
enum AhsSpidarTypeEnum{
	AHS_SPIDAR_4,				/**< @JP SPIDAR_4:���i3���R�x��4�{���Ńx�[�V�b�N�ȃ^�C�v @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_G,				/**< @JP SPIDAR_G:���i�E��]6���R�x��8�{���ŃO���b�v�^�C�v @END_JP @EN Dummy. @END_EN*/
	AHS_SH_SPIDAR_G,			/**< @JP SPIDAR_G:���i�E��]6���R�x��8�{���ŃO���b�v�^�C�v��SH�� @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_8,				/**< @JP SPIDAR_8:���i3���R�x��3�{���Ń|�C���^�^�C�v��8�Z�b�g�i����4�w�{�E��4�w�j @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_X,				/**< @JP SPIDAR_X:���[�U���C�ӂŎ��̃R���g���[��������Ƃ��Ɏg���^�C�v @END_JP @EN Dummy. @END_EN*/
	AHS_SPIDAR_TYPE_ENUM_MAX	/**< @JP �񋓌^�̃T�C�Y�擾�̂��߂̃_�~�[ @END_JP @EN Dummy. @END_EN*/
};



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidar�̂��߂̃v���O�����̋N���Ə����������D<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0�̂ݐݒ�\�j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	xmlFileName SPIDAR�̐ݒ�t�@�C����(.xml) SPIDAR�̃^�C�v��xml���Œ�`(Spidar,Spidar-G)
	@param[in]	isVoice		�����ē��i1:�L���A0:�����j�i�ȗ��j
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar(SPIDAR_HANDLE* handle,char* xmlFileName,int isVoice = 1, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �y����p�~�iahsCreate_Spidar(SPIDAR_HANDLE* handle,char* xmlFileName)���g���Ă��������j�z<br>
	Spidar�̂��߂̃v���O�����̋N���Ə����������D<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0�̂ݐݒ�\�j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	type		SPIDAR�̃^�C�v(Spidar,Spidar-G)
	@param[in]	xmlFileName SPIDAR�̐ݒ�t�@�C����(.xml)
	@param[in]	isVoice		�����ē��i1:�L���A0:�����j�i�ȗ��j
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar(SPIDAR_HANDLE* handle, AhsSpidarTypeEnum type, char* xmlFileName,int isVoice = 1, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �y����p�~�iahsCreate_Spidar���g���Ă��������j�z<br>
	SpidarG(���i�E��]6���R�x��8�{���ŃO���b�v�^�C�v)�̂��߂̃v���O�����̋N���Ə����������D<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0�̂ݐݒ�\�j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	xmlFileName SPIDAR�̐ݒ�t�@�C����(.xml)
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_EN
*/
SPIDARAHS_API int ahsCreate_SpidarG(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �y����p�~�iahsCreate_Spidar���g���Ă��������j�z<br>
	SPIDAR_8:���i3���R�x��3�{���Ń|�C���^�^�C�v��8�Z�b�g�i����4�w�{�E��4�w�j<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0�̂ݐݒ�\�j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	xmlFileName SPIDAR�̐ݒ�t�@�C����(.xml)
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize SpidarG
	@param[out]	handle spidar handle
	@param[in]	xmlFileName SPIDAR configulation file name(.xml)
	@param[in]	usb_id usb id ()
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar8(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �y����p�~�iahsCreate_Spidar���g���Ă��������j�z<br>
	Spidar4(���i3���R�x��4�{���Ńx�[�V�b�N�ȃ^�C�v)�̂��߂̃v���O�����̋N���Ə����������D<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0��������1��ݒ�\�j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	xmlFileName SPIDAR�̐ݒ�t�@�C����(.xml)
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize Spidar4
@END_EN
*/
SPIDARAHS_API int ahsCreate_Spidar4(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �y����p�~�iahsCreate_Spidar���g���Ă��������j�z<br>
	SpidarX(���[�U���C�ӂŎ��̃R���g���[��������Ƃ��Ɏg���^�C�v)�̂��߂̃v���O�����̋N���Ə����������D<br>
	�R���g���[���̓d���𓊓����������œ��Y�R���g���[����handle���擾�ł���D<br>
	�i�ق��̊֐��Ŏw��ł���spidar_id��0����7�܂ł�ݒ�\�j
	�i���܂��e�X�g�s���j
	@param[out]	handle		�N���E����������SPIDAR�̃n���h��
	@param[in]	xmlFileName	SPIDAR�̐ݒ�t�@�C����(.xml)
	@param[in]	usb_id		�擾USB�@���ID�i�ȗ��E�ȗ������j
	@return		������������0,���s��������0�ȊO��Ԃ�
@END_JP
@EN
	@brief Create and initialize SpidarX
@END_EN
*/
SPIDARAHS_API int ahsCreate_SpidarX(SPIDAR_HANDLE* handle, char* xmlFileName, int usb_id = -1);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �͊o�񎦐��䃋�[�v�̊J�n<br>
	�}���`���f�B�A�^�C�}�ɂ��1kHz�̍X�V���g���i�ݒ�t�@�C���ɂ��X�V���g���̕ύX���\�j<br>
	�����ӁF�R���g���[���P�ʁiSPIDAR_HANDLE�P�ʁj�Ń^�C�}���N������K�v������B<br>
	������R���g���[����ڑ�����ꍇ�A�R���g���[���̑䐔�����䃋�[�v����邱�ƂɂȂ�B

	@param[in]	handle �ΏۂƂȂ�SPIDAR�̃n���h��
@END_JP
@EN
	@brief Start haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsStartHapticLoop(SPIDAR_HANDLE pAHS);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �͊o�񎦐����L���E�����ɂ���
	@param[in]	handle �ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	isActive �͊o�����L���ɂ���Ƃ�1, �����ɂ���Ƃ�0
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID<br>
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�j<br>
							<b>SpidarG�̂Ƃ�</b>��1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j<br>
							<b>Spidar4�̂Ƃ�</b>��2�䕪����ł���̂�0����1���w��\<br>
							<b>SpidarX�̂Ƃ�</b>��8�{���̎��𐧌�ł���̂�0����7���w��\<br>
@END_JP
@EN
	@brief Start haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsActive         (SPIDAR_HANDLE pAHS,int isActive,   int spidar_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spidar�̃L�����u���[�V�������s��
	@param[in]	handle �ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID<br>
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�j<br>
							<b>SpidarG�̂Ƃ�</b>��1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j<br>
							<b>Spidar4�̂Ƃ�</b>��2�䕪����ł���̂�0����1���w��\<br>
							<b>SpidarX�̂Ƃ�</b>��8�{���̎��𐧌�ł���̂�0����7���w��\<br>
@END_JP
@EN
	@brief Make calibration of Spidar
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsCalib          (SPIDAR_HANDLE pAHS,                int spidar_id = -1);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �͊o�񎦐��䃋�[�v�̒�~
	@param[in]	handle �ΏۂƂȂ�SPIDAR�̃n���h��
@END_JP
@EN
	@brief Stop haptic control loop
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API void ahsStopHapticLoop (SPIDAR_HANDLE pAHS);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief Spiar�̏I������<br>
	�����ӁF�v���O�����̏I�����ɂ͕K�����s���Đ�����SpidarAPI���I�����Ă�������
	@param[in]	handle �ΏۂƂȂ�SPIDAR�̃n���h��
@END_JP
@EN
	@brief Quit Spidar
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API SPIDAR_HANDLE ahsQuit  (SPIDAR_HANDLE pAHS);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ���i���x�̎擾�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	posVel[3]	���i���x�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpPosVel   (SPIDAR_HANDLE pAHS,float posVel[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ��]���x�̎擾�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	posVel[3]	��]���x�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpOriVel   (SPIDAR_HANDLE pAHS,float posVel[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ���i�ʒu�̎擾�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	pos[3]		���i�ʒu�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpPos      (SPIDAR_HANDLE pAHS,float pos[3],   int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ��]�p���̎擾�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	ori[4]		�N�I�[�^�j�I��(quaternion)�ɂ���]�p���̒l(w,x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetImpOri_wxyz (SPIDAR_HANDLE pAHS,float ori[4],   int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ���i�񎦗͂̐ݒ�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	force[3]	���i�񎦗͂̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpForce    (SPIDAR_HANDLE pAHS,float force[3] ,int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ��]�񎦃g���N�̐ݒ�i�C���s�[�_���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	torque[3]	��]�񎦃g���N�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpTorque   (SPIDAR_HANDLE pAHS,float torque[3],int spidar_id = 0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �͊o�|�C���^�̃X�P�[���̐ݒ�i�C���s�[�_���X����p�j
	@param[in]	handle			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	posGripScale	���i�����̃X�P�[��
	@param[in]	oriGripScale	��]�����̃X�P�[��
	@param[in]	spidar_id		�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetImpScale(SPIDAR_HANDLE pAHS,
								 float posGripScale,
								 float oriGripScale,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief VC�̃I�u�W�F�N�g���̕��i�͂Ɖ�]�͂̃X�P�[���̐ݒ�i�C���s�[�_���X����p�j
	@param[in]	handle			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	forceObjScale	���i�͂̃X�P�[��
	@param[in]	torqueObjScale	��]�͂̃X�P�[��
	@param[in]	spidar_id		�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsVcSetFTscale(SPIDAR_HANDLE pAHS,
								 float forceObjScale,
								 float torqueObjScale,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �o�[�`�����J�b�v�����O�p�����[�^�ݒ�i�C���s�[�_���X���䎞�j
	@param[in]	handle			�ΏۂƂȂ�SPIDAR�̃n���h��
	
	@param[in]	posK			���i�����̍����W��
	@param[in]	posB			���i�����̔S���W��

	@param[in]	oriK			��]�����̍����W��
	@param[in]	oriB			��]�����̔S���W��
	
	@param[in]	spidar_id		�ݒ�ΏۂƂȂ�Spidar��ID
								�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/

SPIDARAHS_API void ahsVcSetKB(SPIDAR_HANDLE pAHS,
								 float posK,float posB,
								 float oriK,float oriB,
								 int spidar_id = 0);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �o�[�`�����J�b�v�����O�̍X�V�i�C���s�[�_���X���䎞�j
	@param[in]	handle			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	isCoupling		�J�b�v�����O���v�Z���邩�ǂ��� 1�Ȃ�Όv�Z�A0�Ȃ�Όv�Z���Ȃ�

	@param[in]	posObj[3]		���݂̃I�u�W�F�N�g�̈ʒu�ix,y,z�̏��j
	@param[in]	posVelObj[3]	���݂̃I�u�W�F�N�g�̑��x�ix,y,z�̏��j
	@param[out]	forceObj[3]		�J�b�v�����O�ɂ�蓾��ꂽ�́ix,y,z�̏��j

	@param[in]	oriObj[4]		���݂̃I�u�W�F�N�g�̎p���i�N�I�[�^�[�j�I���Fw,x,y,z�̏��j
	@param[in]	oriVelObj[3]	���݂̃I�u�W�F�N�g�̎p���̊p���x�ix,y,z�̏��j
	@param[out]	torqueObj[3]	�J�b�v�����O�ɂ�蓾��ꂽ�g���N�ix,y,z�̏��j

	@param[in]	spidar_id		�ݒ�ΏۂƂȂ�Spidar��ID
								�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
								SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
								Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
								SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
								�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsVcUpdate(SPIDAR_HANDLE pAHS,
							   int isCoupling,	float simHz,
							   float posObj[3],float posVelObj[3],float forceObj[3], 
							   float oriObj[4]/*wxyz*/,float oriVelObj[3],float torqueObj[3],
							   int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ���i�񎦗͂̎擾�i�A�h�~�b�^���X����p�j
	@brief Spidar�̗͊o�񎦕��ɂ�������i�͂��擾����
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	force[3]	���i�񎦗͂̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetAdmForce    (SPIDAR_HANDLE pAHS,float force[3], int spidar_id =  0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ��]�񎦃g���N�̎擾�i�A�h�~�b�^���X����p�j
	@brief Spidar�̗͊o�񎦕��ɂ������]�g���N���擾����
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	torque[3]	��]�񎦃g���N�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetAdmTorque   (SPIDAR_HANDLE pAHS,float torque[3],int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ���i�ʒu�̐ݒ�i�A�h�~�b�^���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	pos[3]		���i�ʒu�̒l(x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetAdmPos      (SPIDAR_HANDLE pAHS,float pos[3],   int spidar_id = 0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief ��]�p���̐ݒ�i�A�h�~�b�^���X����p�j
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[out]	ori[4]		�N�I�[�^�j�I��(quaternion)�ɂ���]�p���̒l(w,x,y,z�̏���)
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID
							�i�ȗ��E�ȗ����͂��ׂĂ�Spidar_id���ΏۂƂȂ�
							SpidarG�̂Ƃ���1�䕪�݂̂Ȃ̂�0���w��i�ȗ������j�C
							Spidar4�̂Ƃ���2�䕪����ł���̂�0����1���w��\�C
							SpidarX�̂Ƃ���8�{���̎��𐧌�ł���̂�0����7���w��\
							�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetAdmOri_wxyz (SPIDAR_HANDLE pAHS,float ori[4],   int spidar_id = 0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �O���X�C�b�`���͒l�̎擾�i�f�W�^���X�C�b�`�p�j
	@brief �y�������z
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	ch			�X�C�b�`�̃`�����l���ԍ�
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID�i�ȗ��E�ȗ������j
	@return		�ΏۃX�C�b�`�̒l
@END_JP
@EN
	@brief Get external switch value (for digital switch)
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API int   ahsGetDigitalSw  (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);



//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �O���X�C�b�`���͒l�̎擾�i�A�i���O�X�C�b�`�p�C�^�b�`�X�C�b�`�Ɠ����Ń}���`�v���N�X�j
	@brief �y�������z
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	ch			�X�C�b�`�̃`�����l���ԍ�
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID�i�ȗ��E�ȗ������j
	@return		�ΏۃX�C�b�`�̒l
@END_JP
@EN
	@brief Get external switch value (for analog switch)
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API float ahsGetAnalogSw	 (SPIDAR_HANDLE pAHS,int ch,         int spidar_id =  0);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �^�b�`�X�C�b�`���͒l�̎擾�i�A�i���O�X�C�b�`�Ɠ����Ń}���`�v���N�X�j
	@brief �y�������z
	@param[in]	handle		�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	ch			�X�C�b�`�̃`�����l���ԍ��i�ő�:3ch�j
	@param[in]	spidar_id	�ݒ�ΏۂƂȂ�Spidar��ID�i�ȗ��E�ȗ������j
	@return		�ΏۃX�C�b�`�̒l
@END_JP
@EN
	@brief Get Touch switch value
	@param[in]	handle SPIDAR handle
@END_EN
*/
SPIDARAHS_API int ahsGetTouchSw	(SPIDAR_HANDLE pAHS,int ch,	int spidar_id = 0 );


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief �͊o�񎦐��䃋�[�v�̒��Ŏ��s���郆�[�U�֐��i�R�[���o�b�N�֐��j�̐ݒ�
	@brief�@��j�C���s�[�_���X���䎞�ɂ�����o�[�`�����J�b�v�����O�̎����Ȃ�
	@param[in]	handle	�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	pf		���䃋�[�v���Ŏ��s����R�[���o�b�N�֐�<br>
						�֐�pf���ň�����dwUser���g����<br>
						SPIDAR_HANDLE hSpidar = (SPIDAR_HANDLE)dwUser;<br>
						�Ƃ��邱�ƂŁA�֐�pf���őΉ�����SPIDAR_HANDLE���擾�ł��܂��B<br>
						����ɂ��n���h��hSpidar���g���đΉ�����Spidar�̈ʒu���E�͏��Ȃǂ��擾�E�ݒ�ł��܂��B
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetHapticLoopCallBackFunction(SPIDAR_HANDLE pAHS,  void (CALLBACK *pf)(DWORD dwUser));


//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// �g���@�\

/**
@JP
	@brief �y�g���@�\�z�l�擾�g���@�\�̂��߂̎�ڒ萔<br>
			����ǉ��\��
@END_JP
@EN
@END_EN
*/
enum AhsGetEnum{
	GET_SPIDAR_NUM_IV1,				/**< @JP �{�R���g���[���Ő���ł���Spidar�̐����擾		(int�^�A�x�N�g���z��A�T�C�Y�F1) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_PHS_ALL8CH_CV8,			/**< @JP 8�`�����l�����ׂẴG���R�[�_�̑����̎擾		(char�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_COUNT_ALL8CH_FV8,		/**< @JP 8�`�����l�����ׂẴG���R�[�_�J�E���g�l�̎擾	(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ENC_COUNT_ALL8x3CH_FV24,	/**< @JP 24(8x3)�`�����l�����ׂẴG���R�[�_�J�E���g�l�̎擾	(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_WIRE_LENGTH_ALL8CH_FV8,		/**< @JP 8�`�����l�����ׂẴ��C���̒����̎擾			(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_MOTOR_POS0_ALL8CH_FV3x8,	/**< @JP 8�`�����l�����ׂẴ��[�^�̈ʒu�̎擾			(float�^�A�x�N�g���z��A�T�C�Y�F3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_MOTOR_POS0_ALL8x3CH_FV3x24,	/**< @JP 24(8x3)�`�����l�����ׂẴ��[�^�̈ʒu�̎擾	(float�^�A�x�N�g���z��A�T�C�Y�F3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_GRIP_POS0_ALL8CH_FV3x8,		/**< @JP 8�`�����l�����ׂẴO���b�v��̃��C���ڑ��ʒu�i�O���b�v���z�[���|�W�V�����̎��j�̎擾 (float�^�A�x�N�g���z��A�T�C�Y�F3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_GRIP_POS0_ALL8x3CH_FV3x24,	/**< @JP 24(8x3)�`�����l�����ׂẴO���b�v��̃��C���ڑ��ʒu�i�O���b�v���z�[���|�W�V�����̎��j�̎擾 (float�^�A�x�N�g���z��A�T�C�Y�F3x8=24) @END_JP @EN Get all motor position. @END_EN*/
	GET_PWM_DUTY_ALL8CH_FV8,
	GET_ADC_FORCE_ALL8CH_FV8,
	GET_ADC_RAW_ALL8CH_IV8,
	GET_ADC_FIR_RAW_ALL8CH_IV8,


	GET_PID_TARGET_ALL8CH_IV8,		/**< @JP 8�`�����l�����ׂĂ�PID�ڕW�l�̒l���擾			(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_PID_AMP_TEST_ALL8CH_FV8,	/**< @JP PID�e�X�g�p									(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	
	GET_ADM_PID_PV_TEST_ALL8CH_IV8,		/**< @JP PID�e�X�g�p PID�̐���ʁi�v���l�j				(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PID�e�X�g�p PID�̖ڕW�l						(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��P���W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��I�ϕ��W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_ADM_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��D�����W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/

	GET_IMP_PID_PV_TEST_ALL8CH_IV8,		/**< @JP PID�e�X�g�p PID�̐���ʁi�v���l�j				(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PID�e�X�g�p PID�̖ڕW�l						(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��P���W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��I�ϕ��W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	GET_IMP_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��D�����W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/

	GET_VC_POS_ORI_NORM_FV2,			/**< @JP VC�̈ʒu�p���̃m����(float�^�A�x�N�g���z��A�T�C�Y�F2) @END_JP @EN Get all encoder count. @END_EN*/

	GET_HAPTIC_LOOP_MSEC_IV1,		/**< @JP �n�v�e�B�b�N���[�v�̍X�V�����̎擾[msec]			(int�^�A�x�N�g���z��A�T�C�Y�F1) @END_JP @EN Get all motor position. @END_EN*/

	GET_SH_SEND_DATA_LEN_UCV1,
	GET_SH_RECEIVE_DATA_LEN_UCV1,

	GET_API_VER_STR_CV128,
	GET_API_COPY_RIGHT_STR_CV128,
	AHS_GET_ENUM_MAX				/**< @JP �񋓌^�̃T�C�Y�擾�̂��߂̃_�~�[ @END_JP @EN Dummy. @END_EN*/
};

/**
@JP
	@brief �y�g���@�\�z�l�ݒ�g���@�\�̂��߂̎�ڒ萔<br>
			����ǉ��\��
@END_JP
@EN
@END_EN
*/
enum AhsSetEnum{

	SET_PWM_DUTY_PERCENT_ALL8CH_FV8,
	SET_PID_SV_TEST_ALL8CH_IV8,		/**< @JP PID�e�X�g�p PID�̖ڕW�l						(int�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KP_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��P���W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KI_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��I�ϕ��W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_KD_TEST_ALL8CH_FV8,		/**< @JP PID�e�X�g�p PID��D�����W��						(float�^�A�x�N�g���z��A�T�C�Y�F8) @END_JP @EN Get all encoder count. @END_EN*/
	SET_PID_MODE_IV8,

	SET_SH_HAPTIC_RENDERING_TYPE_CV1,
	AHS_SET_ENUM_MAX			/**< @JP �񋓌^�̃T�C�Y�擾�̂��߂̃_�~�[ @END_JP @EN Dummy. @END_EN*/
};


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>�y�g���@�\�z</b>�l�̎擾�֐�
	@param[in]	pAHS			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	AhsGetEnum		�擾�������l�̎�ڒ萔�@��ڒ萔�̍Ō�̕����ɂ��f�[�^�^�A�f�[�^���Ȃǂ����肳��Ă���<br>
								��j�G���R�[�_�̒l��8�`�����l�����擾����<br>
								GET_ENC_COUNT_ALL8CH_IV8<br>
								I:int�^�̃f�[�^<br>
								V:�x�N�g���z��<br>
								8:8�f�[�^��<br>
								���Ӗ�����B
	@param[out]	param			�擾����l�i�|�C���^�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsGetVal(SPIDAR_HANDLE pAHS,AhsGetEnum cap,void* param);

//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>�y�g���@�\�z</b>�l�̐ݒ�֐�
	@param[in]	pAHS			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	AhsGetEnum		�ݒ肵�����l�̎�ڒ萔�@��ڒ萔�̍Ō�̕����ɂ��f�[�^�^�A�f�[�^���Ȃǂ����肳��Ă���<br>
								��j�G���R�[�_�̒l��8�`�����l�����擾����<br>
								GET_ENC_COUNT_ALL8CH_IV8<br>
								I:int�^�̃f�[�^<br>
								V:�x�N�g���z��<br>
								8:8�f�[�^��<br>
								���Ӗ�����B
	@param[in]	param			�ݒ肷��l�i�|�C���^�j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API void ahsSetVal(SPIDAR_HANDLE pAHS,AhsSetEnum cap,void* param);





//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>�ySH �g���@�\�zSH���ڑ�����Ă��Ȃ��V�X�e���ł͖����C</b>SH1�ւ̒l�̐ݒ�Ǝ擾�֐�
	@param[in]	pAHS			�ΏۂƂȂ�SPIDAR�̃n���h��
	@param[in]	w_size			SH1�ɐݒ肷��f�[�^�̃T�C�Y(Byte)
	@param[in]	w_address		SH1�ɐݒ肷��f�[�^�̃A�h���X�iSH1�̃A�h���X�j
	@param[in]	w_data			SH1�ɐݒ肷��f�[�^
	@param[in]	r_address		SH1����擾����f�[�^�̃A�h���X
	@param[out]	r_data			SH1����擾�����f�[�^
	@return		SH1����擾����r_address�Ԓn�̃f�[�^r_data���L�����ǂ����i0�����F1�L���j
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API int ahsSh1SetGetVal(SPIDAR_HANDLE pAHS,unsigned char w_size,unsigned long w_address,unsigned char w_data[48],unsigned long r_address,unsigned char r_data[52],unsigned char id = 0x0c);


//////////////////////////////////////////////////////////////////////////////
/**
@JP
	@brief <b>�ySH �g���@�\�zSH���ڑ�����Ă��Ȃ��V�X�e���ł͖���
@END_JP
@EN
@END_EN
*/
SPIDARAHS_API unsigned long ahsSh1GetAddress(SPIDAR_HANDLE pAHS,int id);
