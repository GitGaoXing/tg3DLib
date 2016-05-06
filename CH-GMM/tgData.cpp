#include "tgData.h"

namespace tg
{
Data::ObjectCreator Data::m_stuObjectCreator;

Data* Data::Instance()
{
	static Data l_oData;
	return &l_oData;
}

Data::Data()
{

}

Data::~Data()
{

}

}