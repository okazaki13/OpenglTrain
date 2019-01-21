/** @file
	@JP
		@brief AHS Base �N���X��`
		@author �ԉH ���m
	@END_JP
	@EN
		@brief AHS Base Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/1/27
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/

#pragma once
//#include "FFx2USB.h"
//#include "FFx2CyUSB.h"
#include <stdio.h>
#include <string>

/**
@JP
\class	AHS Base ���N���X
@END_JP
@EN
\class	AHS Base  Class
@END_EN
 */
class CFx2Base
{
public:
	CFx2Base(void);				///< @JP �R���X�g���N�^ @END_JP @EN Constructor @END_EN
	virtual ~CFx2Base(void);	///< @JP �f�X�g���N�^	@END_JP @EN Destructor  @END_EN
	/**
	@JP
		�t���O�̐ݒ������ (8bit)

	@param[in] ch �t���O��ݒ肷��`�����l���ԍ�
	@param[in] flag �ݒ肷��t���O�̒l (0 or 1)
	@param[in] prev �t���O�̐ݒ肷��O�̒l
	@return �ݒ��̃t���O�̒l
	@END_JP
	@EN
		Set a value of flags (8bit)

	@param[in] ch Chanel number of the flag
	@param[in] flag Flag value (0 or 1)
	@param[in] prev Previous value of the flag
	@return answer of the flag value
	@END_EN
	*/
	static unsigned char SetFlags8(int ch,int flag,unsigned char prev);

	/**
	@JP
		�t���O�̐ݒ������ (16bit)

	@param[in] ch �t���O��ݒ肷��`�����l���ԍ�
	@param[in] flag �ݒ肷��t���O�̒l (0 or 1)
	@param[in] prev �t���O�̐ݒ肷��O�̒l
	@return �ݒ��̃t���O�̒l
	@END_JP
	@EN
		Set a value of flags (16bit)

	@param[in] ch Chanel number of the flag
	@param[in] flag Flag value (0 or 1)
	@param[in] prev Previous value of the flag
	@return answer of the flag value
	@END_EN
	*/
	static unsigned short SetFlags16(int ch,int flag,unsigned short prev);

	/**
	@JP
		�l�̐ݒ�(a+b)������
	@param[in] a �ݒ�la
	@param[in] b �ݒ�lb
	@param[in] minL �ݒ�l(a+b)�̍Œ�l
	@param[in] maxL �ݒ�l(a+b)�̍ő�l
	@return �ݒ��̒l(a+b)
	@END_JP
	@EN
		Set a value of integer (a+b)
	@param[in] a integer value a
	@param[in] b integer value b
	@param[in] minL minimum value of integer value(a+b)
	@param[in] maxL maximum value of integer value(a+b)
	@return answer of the integer value.
	@END_EN
	*/
	static int SetValInt(int a,int b,int minL,int maxL);

	/**
	@JP
		�l�̎擾������(8bit)
	@param[in] �A�h���X
	@param[in] �`�����l��
	@return �擾�l
	@END_JP
	@EN
		Get a value for 8bit
	@param[in] address
	@param[in] chanel
	@return value
	@END_EN
	*/
	static int GetFlag8(unsigned char* address,int ch);
	/**
	@JP
		�l�̎擾������(16bit)
	@param[in] �A�h���X
	@param[in] �`�����l��
	@return �擾�l
	@END_JP
	@EN
		Get a value for 16bit
	@param[in] address
	@param[in] chanel
	@return value
	@END_EN
	*/
	static int GetFlag16(unsigned short* address,int ch);

	/**
	@JP
		�l�̎擾������(32bit)
	@param[in] �A�h���X
	@param[in] �`�����l��
	@return �擾�l
	@END_JP
	@EN
		Get a value for 32bit
	@param[in] address
	@param[in] chanel
	@return value
	@END_EN
	*/
	static int GetFlag32(unsigned int* address,int ch);
//protected:
//	int GetFlag64(unsigned int* address,int ch);


};
