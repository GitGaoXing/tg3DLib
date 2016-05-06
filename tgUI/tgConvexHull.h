#ifndef ___tgConvexHull___
#define ___tgConvexHull___

#include "tgTask.h"

namespace tg
{

class ConvexHull : public Task
{
public:
	ConvexHull();

	void SetInput(CMesh* i_oMeshSource, CMesh* i_oMeshTarget);
	void SetOutput(CMesh* i_oMeshSourceCH, CMesh* i_oMeshTargetCH);

protected:
	virtual TG_STAT RunAlg();

	CMesh* m_oMeshSource;
	CMesh* m_oMeshTarget;

	CMesh* m_oMeshSourceCH;
	CMesh* m_oMeshTargetCH;
};

}

#endif