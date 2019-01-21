/** @file
	@JP
		@brief AHS Base クラス定義
		@author 赤羽 克仁
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
\class	AHS Base 基底クラス
@END_JP
@EN
\class	AHS Base  Class
@END_EN
 */
class CFx2Base
{
public:
	CFx2Base(void);				///< @JP コンストラクタ @END_JP @EN Constructor @END_EN
	virtual ~CFx2Base(void);	///< @JP デストラクタ	@END_JP @EN Destructor  @END_EN
	/**
	@JP
		フラグの設定をする (8bit)

	@param[in] ch フラグを設定するチャンネル番号
	@param[in] flag 設定するフラグの値 (0 or 1)
	@param[in] prev フラグの設定する前の値
	@return 設定後のフラグの値
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
		フラグの設定をする (16bit)

	@param[in] ch フラグを設定するチャンネル番号
	@param[in] flag 設定するフラグの値 (0 or 1)
	@param[in] prev フラグの設定する前の値
	@return 設定後のフラグの値
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
		値の設定(a+b)をする
	@param[in] a 設定値a
	@param[in] b 設定値b
	@param[in] minL 設定値(a+b)の最低値
	@param[in] maxL 設定値(a+b)の最大値
	@return 設定後の値(a+b)
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
		値の取得をする(8bit)
	@param[in] アドレス
	@param[in] チャンネル
	@return 取得値
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
		値の取得をする(16bit)
	@param[in] アドレス
	@param[in] チャンネル
	@return 取得値
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
		値の取得をする(32bit)
	@param[in] アドレス
	@param[in] チャンネル
	@return 取得値
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
