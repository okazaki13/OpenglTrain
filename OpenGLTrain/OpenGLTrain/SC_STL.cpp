#include "SC_STL.h"


//��������I�u�W�F�N�g����stl�̕ۑ��ꏊ�������ɁB
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

//CreateSCobject�Ő��������I�u�W�F�N�g��stl����ǂݍ��񂾎O�p�`��������
void SC_STL::ImportSTL(std::string strage_location){
}