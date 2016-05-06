#include "tgConvexHull.h"

namespace tg
{

ConvexHull::ConvexHull() : m_oMeshSource(nullptr), m_oMeshTarget(nullptr), 
	m_oMeshSourceCH(nullptr), m_oMeshTargetCH(nullptr)
{

}

void ConvexHull::SetInput(CMesh* i_oMeshSource, CMesh* i_oMeshTarget)
{
	this->m_oMeshSource = i_oMeshSource;
	this->m_oMeshTarget = i_oMeshTarget;
}
	
void ConvexHull::SetOutput(CMesh* i_oMeshSourceCH, CMesh* i_oMeshTargetCH)
{
	this->m_oMeshSourceCH = i_oMeshSourceCH;
	this->m_oMeshTargetCH = i_oMeshTargetCH;
}

Task::TG_STAT ConvexHull::RunAlg()
{
	if(this->m_oMeshSource == nullptr || this->m_oMeshTarget == nullptr || 
		this->m_oMeshSourceCH == nullptr || this->m_oMeshTargetCH == nullptr)
	{
		return Task::Error;
	}

	this->m_oMeshSourceCH->ClearAll();
	this->m_oMeshTargetCH->ClearAll();

	//////////////////////////////////////
	// convex hull
	this->m_oMeshSourceCH->face.EnableFFAdjacency();
	vcg::tri::ConvexHull<CMesh, CMesh>::ComputeConvexHull(*this->m_oMeshSource, *this->m_oMeshSourceCH);

	this->m_oMeshTargetCH->face.EnableFFAdjacency();
	vcg::tri::ConvexHull<CMesh, CMesh>::ComputeConvexHull(*this->m_oMeshTarget, *this->m_oMeshTargetCH);
	
	//////////////////////////////////////
	return Task::Normal;
}


}