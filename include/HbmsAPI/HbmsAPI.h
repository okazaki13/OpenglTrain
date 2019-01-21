/** @file
	@JP
		@brief HbmsAPIのインクルードファイル
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief Include file of HbmsAPI
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/07/06
 */
/************************************************************************/
/*                                                                      */
/*   HBMS                                                               */
/*                                                         Ver 1.0      */
/*                                                                      */
/*                                                                      */
/*                                                                      */
/*   Katsuhito AKAHANE (2009/01/14)                                     */
/*                                                                      */
/************************************************************************/
/*
 * Copyright :Katsuhito AKAHANE 2005-2009. All Rights Reserved.
 * 勝手に変更するな！
*/

#pragma once

#include "FFx2API.h"
#include "FFx2USB.h"
#include "FFx2Base.h"
#include "FFx2BaseFunc.h"
#include "FFx2PID.h"
#include "FFx2Function.h"
#include "HbmsController.h"

//#include "FFx2_usb_define.h"


typedef CFx2API									CHbmsAPI;
typedef CFx2USB									CHbmsUSB;
typedef CFx2Base								CHbmsBase;
typedef CFx2BaseFunc							CHbmsBaseFunc;
typedef CFx2PID									CHbmsPID;
typedef CFx2Function							CHbmsFunction;

typedef CAHSController							CHbmsController;
