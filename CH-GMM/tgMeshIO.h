#ifndef ___tgMeshIO___
#define ___tgMeshIO___

#include "tgTask.h"

namespace tg
{

class MeshIO : public Task
{
public:
	MeshIO();

	void SetInput(const std::string& i_strPath);
	void SetOutput(CMesh* i_oMesh);

protected:
	virtual TG_STAT RunAlg();

	CMesh* m_oMesh;
	std::string m_strPath;

};

}

#endif