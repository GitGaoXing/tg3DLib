#ifndef ___tgData___
#define ___tgData___

#include "tgVCG.h"

namespace tg
{

class Data
{
public:
	static Data* Instance();

	CMesh m_oMeshSource;
	CMesh m_oMeshTarget;

private:
	Data();

	~Data();

	Data(const Data &);

	Data & operator = (const Data &);

	struct ObjectCreator
	{
		ObjectCreator()
		{
			Data::Instance();
		}
	};
	static ObjectCreator m_stuObjectCreator;
};

}

#endif