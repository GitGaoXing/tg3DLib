#include "tgCopy4Render.h"

namespace tg
{

Copy4Render::Copy4Render() : m_oMeshSource(nullptr), m_oMeshTarget(nullptr), 
	m_oMeshSourceR(nullptr), m_oMeshTargetR(nullptr), m_matZoom2Box(nullptr)
{

}

void Copy4Render::SetInput(CMesh* i_oMeshSource, CMesh* i_oMeshTarget)
{
	this->m_oMeshSource = i_oMeshSource;
	this->m_oMeshTarget = i_oMeshTarget;
}
	
void Copy4Render::SetOutput(CMesh* i_oMeshSourceR, CMesh* i_oMeshTargetR, vcg::Matrix44d* i_matZoom2Box)
{
	this->m_oMeshSourceR = i_oMeshSourceR;
	this->m_oMeshTargetR = i_oMeshTargetR;
	this->m_matZoom2Box = i_matZoom2Box;
}

Task::TG_STAT Copy4Render::RunAlg()
{
	if(this->m_oMeshSource == nullptr || this->m_oMeshTarget == nullptr || 
		this->m_oMeshSourceR == nullptr || this->m_oMeshTargetR == nullptr || this->m_matZoom2Box == nullptr)
	{
		return Task::Error;
	}

	this->m_oMeshSourceR->ClearAll();
	this->m_oMeshTargetR->ClearAll();
	vcg::tri::Append<CMesh, CMesh>::Mesh(*this->m_oMeshSourceR, *this->m_oMeshSource);
	vcg::tri::UpdateNormal<CMesh>::PerVertexNormalizedPerFace(*this->m_oMeshSourceR);
    vcg::tri::UpdateNormal<CMesh>::PerFaceNormalized(*this->m_oMeshSourceR);

	vcg::tri::Append<CMesh, CMesh>::Mesh(*this->m_oMeshTargetR, *this->m_oMeshTarget);
	vcg::tri::UpdateNormal<CMesh>::PerVertexNormalizedPerFace(*this->m_oMeshTargetR);
    vcg::tri::UpdateNormal<CMesh>::PerFaceNormalized(*this->m_oMeshTargetR);
	//////////////////////////////////////

	double l_dScale;
	vcg::Point3d l_ptCenter;

	vcg::Box3f	l_oBoundBox;	// AABBox

	for(auto& iter : this->m_oMeshSourceR->vert)
	{
		l_oBoundBox.Add(iter.P());
	}

	for(auto& iter : this->m_oMeshTargetR->vert)
	{
		l_oBoundBox.Add(iter.P());
	}

	l_ptCenter = vcg::Point3d((double)l_oBoundBox.Center().X(), (double)l_oBoundBox.Center().Y(), (double)l_oBoundBox.Center().Z());		
	l_dScale = 3.0f / l_oBoundBox.Diag();

	this->m_matZoom2Box->SetScale(l_dScale, l_dScale, l_dScale);
	this->m_matZoom2Box->SetColumn(3, -l_ptCenter * l_dScale);

	return Task::Normal;
}


}