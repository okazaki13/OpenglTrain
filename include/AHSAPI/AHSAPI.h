/** @file
	@JP
		@brief AHSAPIのインクルードファイル
		@author 赤羽 克仁
	@END_JP
	@EN
		@brief Include file of AHSAPI
		@author Katsuhito AKAHANE
	@END_EN

	@date	2009/07/06
 */

/************************************************************************/
/*                                                                      */
/*   AHS                                                               */
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
#include "AHSController.h"
#include "AHSControllerSH4_01.h"

//#include "FFx2_usb_define.h"


typedef CFx2API									CAHSAPI;
typedef CFx2USB									CAHSUSB;
typedef CFx2Base								CAHSBase;
typedef CFx2BaseFunc							CAHSBaseFunc;
typedef CFx2PID									CAHSPID;
typedef CFx2Function							CAHSFunction;

typedef CAHSController							CAHSController;
