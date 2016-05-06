#ifndef ___tgCopy4Render___
#define ___tgCopy4Render___

#include "tgTask.h"

namespace tg
{

class Copy4Render : public Task
{
public:
	Copy4Render();

	void SetInput(CMesh* i_oMeshSource, CMesh* i_oMeshTarget);
	void SetOutput(CMesh* i_oMeshSourceR, CMesh* i_oMeshTargetR, vcg::Matrix44d* i_matZoom2Box);

protected:
	virtual TG_STAT RunAlg();

	CMesh* m_oMeshSource;
	CMesh* m_oMeshTarget;

	CMesh* m_oMeshSourceR;
	CMesh* m_oMeshTargetR;
	vcg::Matrix44d* m_matZoom2Box;
};

}

#endif