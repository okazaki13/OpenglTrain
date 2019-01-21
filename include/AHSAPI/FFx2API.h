#pragma once
/** @file
	@JP
		@brief AHS API 基底クラス定義
		@author 赤羽 克仁
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

// 以下の ifdef ブロックは DLL からのエクスポートを容易にするマクロを作成するための 
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された HBMSAPI_EXPORTS
// シンボルでコンパイルされます。このシンボルは、この DLL を使うプロジェクトで定義することはできません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、 
// HBMSAPI_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef HBMSAPI_EXPORTS
#define AHSAPI_API __declspec(dllexport)
#else
#define AHSAPI_API __declspec(dllimport)
#endif

#include <windows.h>
#include <string>
#include <stdio.h>

// このクラスは AHSAPI.dll からエクスポートされました

/**
@JP
	AHS API 基底クラス
@END_JP
@EN
	AHS API base class
@END_EN
 */
class AHSAPI_API CFx2API
{
	
protected:
	FILE* m_fp_log_ahs_api;		///< @JP AHSAPIのログファイルのファイルポインタ			@END_JP @EN ＊＊＊ @END_EN

protected:
	// データ出力用ファイル
	std::string m_dataFileName;	///< @JP データ出力用ファイルのファイル名				@END_JP @EN ＊＊＊ @END_EN
	FILE* m_fpData;				///< @JP データ出力用ファイルのファイルポインタ			@END_JP @EN ＊＊＊ @END_EN
	void initDataFile();		///< @JP データ出力用ファイルのファイルポインタの初期化	@END_JP @EN ＊＊＊ @END_EN
public:
	FILE* GetFpDataFile();		///< @JP データ出力用ファイルのファイルポインタの取得	@END_JP @EN ＊＊＊ @END_EN


public:
	CFx2API(void);				///< @JP コンストラクタ @END_JP @EN Constructor @END_EN
	virtual ~CFx2API(void);		///< @JP デストラクタ	@END_JP @EN Destructor  @END_EN


public:
	virtual std::string GetAPIStr();	///< @JP API文字列取得関数			@END_JP @EN Get API information str			@END_EN
	std::string GetVersionStr();		///< @JP バージョン文字列取得関数	@END_JP @EN Get version information str		@END_EN
	std::string GetCopyrightStr();		///< @JP コピーライト文字列取得関数	@END_JP @EN Get copyright information str	@END_EN

public:
	static int Locate(HANDLE hOut, int x, int y);
};
