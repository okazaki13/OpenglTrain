/** @file
	@JP
		@brief CAHSControllerSH4_01 ÉNÉâÉXíËã`
		@author ê‘âH çéêm
	@END_JP
	@EN
		@brief CAHSFunction Class interface
		@author Katsuhito AKAHANE
	@END_EN

	@date	2010/6/17
 */
/*
 * Copyright : Katsuhito AKAHANE 2005-2009. All Rights Reserved.
*/

#pragma once
#include "ahscontroller.h"

class AHSAPI_API CAHSControllerSH4_01 :
	public CAHSController
{
public:
	CAHSControllerSH4_01(void);
	virtual ~CAHSControllerSH4_01(void);

public:
	virtual unsigned char* GetSh0ReceiveData();
	virtual unsigned char* GetSh0SendData();

public:
	virtual unsigned char* GetSh1ReceiveData();
	virtual unsigned char* GetSh1SendData();

public:
	virtual void SetSh0Data(unsigned char id,unsigned char info,unsigned char w_size,unsigned long w_address,unsigned char* w_data,unsigned long r_address);
	virtual void SetSh1Data(unsigned char id,unsigned char info,unsigned char w_size,unsigned long w_address,unsigned char* w_data,unsigned long r_address);
public:
	virtual int GetSh0Data(unsigned char& id,unsigned char& info,unsigned char& info2,unsigned long& r_address,unsigned char* r_data);
	virtual int GetSh1Data(unsigned char& id,unsigned char& info,unsigned char& info2,unsigned long& r_address,unsigned char* r_data);

public:
	virtual void GetSh0DataFromSh1(unsigned char& id,unsigned char& info,unsigned char& w_size,unsigned long& w_address,unsigned char* w_data,unsigned char& r_size,unsigned long& r_address);
};
