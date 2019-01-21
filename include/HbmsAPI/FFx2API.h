#pragma once
/** @file
	@JP
		@brief AHS API ���N���X��`
		@author �ԉH ���m
	@END_JP
	@EN
		@brief AHS API Base Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2008/11/11
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2012. All Rights Reserved.
*/

// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ HBMSAPI_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// HBMSAPI_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef HBMSAPI_EXPORTS
#define AHSAPI_API __declspec(dllexport)
#else
#define AHSAPI_API __declspec(dllimport)
#endif

#include <windows.h>
#include <string>
#include <stdio.h>

// ���̃N���X�� AHSAPI.dll ����G�N�X�|�[�g����܂���

/**
@JP
	AHS API ���N���X
@END_JP
@EN
	AHS API base class
@END_EN
 */
class AHSAPI_API CFx2API
{
	
protected:
	FILE* m_fp_log_ahs_api;		///< @JP AHSAPI�̃��O�t�@�C���̃t�@�C���|�C���^			@END_JP @EN ������ @END_EN

protected:
	// �f�[�^�o�͗p�t�@�C��
	std::string m_dataFileName;	///< @JP �f�[�^�o�͗p�t�@�C���̃t�@�C����				@END_JP @EN ������ @END_EN
	FILE* m_fpData;				///< @JP �f�[�^�o�͗p�t�@�C���̃t�@�C���|�C���^			@END_JP @EN ������ @END_EN
	void initDataFile();		///< @JP �f�[�^�o�͗p�t�@�C���̃t�@�C���|�C���^�̏�����	@END_JP @EN ������ @END_EN
public:
	FILE* GetFpDataFile();		///< @JP �f�[�^�o�͗p�t�@�C���̃t�@�C���|�C���^�̎擾	@END_JP @EN ������ @END_EN


public:
	CFx2API(void);				///< @JP �R���X�g���N�^ @END_JP @EN Constructor @END_EN
	virtual ~CFx2API(void);		///< @JP �f�X�g���N�^	@END_JP @EN Destructor  @END_EN


public:
	virtual std::string GetAPIStr();	///< @JP API������擾�֐�			@END_JP @EN Get API information str			@END_EN
	std::string GetVersionStr();		///< @JP �o�[�W����������擾�֐�	@END_JP @EN Get version information str		@END_EN
	std::string GetCopyrightStr();		///< @JP �R�s�[���C�g������擾�֐�	@END_JP @EN Get copyright information str	@END_EN

public:
	static int Locate(HANDLE hOut, int x, int y);
};
