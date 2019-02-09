#pragma once
#include<string>
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/include/sc.h"
#include "../../SmartCollisionSDK/SmartCollisionSDK 2.01/spo/include/spo.h"
class SC_STL
{
public:
	SC_STL(std::string objectname, std::string strage_location);
	~SC_STL();

	void CreateSCobject(std::string objectname);
	void ImportSTL(std::string strage_location);

private:




};

