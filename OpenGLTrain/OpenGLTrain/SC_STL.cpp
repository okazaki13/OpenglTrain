#include "SC_STL.h"


//生成するオブジェクト名とstlの保存場所を引数に。
SC_STL::SC_STL(std::string objectname, std::string strage_location)
{
	CreateSCobject(objectname);
	ImportSTL(strage_location);

}


SC_STL::~SC_STL()
{
}


void SC_STL::CreateSCobject(std::string objectname) {
	SCObject objectname(SC_OBJECT_TYPE_CLOSED_POLYHEDRA);
}

//CreateSCobjectで生成したオブジェクトにstlから読み込んだ三角形を代入する
void SC_STL::ImportSTL(std::string strage_location){
}