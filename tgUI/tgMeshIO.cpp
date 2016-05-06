#include "tgMeshIO.h"

namespace tg
{

MeshIO::MeshIO() : m_oMesh(nullptr)
{

}

void MeshIO::SetInput(const std::string& i_strPath)
{
	this->m_strPath = i_strPath;
}

void MeshIO::SetOutput(CMesh* i_oMesh)
{
	this->m_oMesh = i_oMesh;
}

Task::TG_STAT MeshIO::RunAlg()
{
	if(this->m_strPath.empty() || this->m_oMesh == nullptr)
	{
		return Task::Error;
	}

	if(CMesh::OpenPly(*this->m_oMesh, this->m_strPath.c_str(), tg::Core::CallbackVCG))
	{
		return Task::Error;
	}
	return Task::Normal;
}


}