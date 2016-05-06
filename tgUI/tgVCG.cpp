#include "tgVCG.h"
#include <limits> 

int PlyHeader::GetVerticesNum(const char* i_cFileName)
{
	if(this->OpenRead(i_cFileName) == -1)
		return -1;
	vcg::ply::PlyElement* l_oVertex = this->FindElement("vertex");

	if(l_oVertex == NULL)
		return -1;

	return l_oVertex->number;
}

void CMesh::ClearAll()
{
	CMesh l_oMeshClean, l_oMeshClean_1;
	l_oMeshClean.vert.swap(this->vert);
	l_oMeshClean.face.swap(this->face);
	l_oMeshClean.edge.swap(this->edge);
	l_oMeshClean_1.face.AF.swap(this->face.AF);
	l_oMeshClean_1.face.AV.swap(this->face.AV);
	this->Clear();
}

float CMesh::GetColorVariety()
{
	if(this->vert.size() == 0)
	{
		return 0;
	}

	float l_fVariety = 0;
	std::vector<unsigned char> l_lstDis(this->vert.size());
	for(auto j = 0; j < 3; ++j)
	{
		for(auto i = 0; i < this->vert.size(); ++i)
		{
			auto& l_oColor = this->vert[i].C();
			l_lstDis[i] = this->vert[i].C()[j];
		}
		std::sort(l_lstDis.begin(), l_lstDis.end());

		int l_nMinIndex = 0.1 * this->vert.size();
		int l_nMaxIndex = 0.9 * this->vert.size();

		l_fVariety += (l_lstDis[l_nMinIndex] - l_lstDis[l_nMaxIndex]) * (l_lstDis[l_nMinIndex] - l_lstDis[l_nMaxIndex]);
	}
	return sqrt(l_fVariety);
}

int CMesh::OpenPly(CMesh &m, const char * filename, vcg::CallBackPos *cb)
{
	return vcg::tri::io::ImporterPLY<CMesh>::Open(m, filename, cb);
}

int CMesh::OpenPly(CMesh &m, const char * filename, int & loadmask, vcg::CallBackPos *cb)
{
	return vcg::tri::io::ImporterPLY<CMesh>::Open(m, filename, loadmask, cb);
}

int CMesh::OpenPly(CMesh &m, const char * filename, vcg::tri::io::PlyInfo &pi)
{
	return vcg::tri::io::ImporterPLY<CMesh>::Open(m, filename, pi);
}

int CMesh::SavePly(CMesh &m, const char * filename, bool binary )
{
	return vcg::tri::io::ExporterPLY<CMesh>::Save(m, filename, binary);
}

int CMesh::SavePly(CMesh &m,  const char * filename, int savemask, bool binary, vcg::CallBackPos *cb)
{
	return vcg::tri::io::ExporterPLY<CMesh>::Save(m, filename, savemask, binary, cb);
}

int CMesh::SavePly(CMesh &m,  const char * filename, bool binary, vcg::tri::io::PlyInfo &pi, vcg::CallBackPos *cb)
{
	return vcg::tri::io::ExporterPLY<CMesh>::Save(m, filename, binary, pi, cb);
}

int CMesh::GetVerticesNum(const char* i_cFileName)
{
	PlyHeader l_oPlyHeader;

	return l_oPlyHeader.GetVerticesNum(i_cFileName);
}
