#ifndef ___tgVCG___
#define ___tgVCG___

// vcg imports
#include <vcg/math/base.h>
#include <vcg/space/index/grid_static_ptr.h>
#include <vcg/complex/complex.h>
#include <vcg/complex/algorithms/update/bounding.h>
#include <vcg/complex/algorithms/update/normal.h>
#include <vcg/complex/algorithms/update/color.h>
#include <vcg/complex/algorithms/clean.h>
#include <vcg/complex/algorithms/convex_hull.h>
#include <vcg/complex/algorithms/hole.h>
#include <vcg/complex/algorithms/refine.h>
#include <vcg/complex/algorithms/refine_loop.h>
#include <vcg/complex/append.h>
#include <vcg/complex/algorithms/create/advancing_front.h>
#include <vcg/complex/algorithms/create/marching_cubes.h>
#include <vcg/complex/algorithms/create/platonic.h>
#include <vcg/space/box3.h>
#include <vcg/space/fitting3.h>
#include <vcg/space/point_matching.h>

/// wrapper imports
#include "wrap/ply/plylib.h"
#include <wrap/io_trimesh/import.h>
#include <wrap/io_trimesh/export.h>

#include <memory>

class CVertex;
class CEdge;
class CFace;
// Declaration of the semantic of the used types
class CUsedTypes: public vcg::UsedTypes < vcg::Use<CVertex>::AsVertexType,
	vcg::Use<CEdge   >::AsEdgeType,
	vcg::Use<CFace  >::AsFaceType >{};

class CVertex  : public vcg::Vertex< CUsedTypes,
	vcg::vertex::InfoOcf,           /*  4b */
	vcg::vertex::Coord3f,           /* 12b */
	vcg::vertex::BitFlags,          /*  4b */
	vcg::vertex::Normal3f,          /* 12b */
	vcg::vertex::Qualityf,          /*  4b */
	vcg::vertex::Color4b,           /*  4b */
	vcg::vertex::VFAdjOcf,          /*  0b */
	vcg::vertex::MarkOcf,           /*  0b */
	vcg::vertex::TexCoordfOcf,      /*  0b */
	vcg::vertex::CurvaturefOcf,     /*  0b */
	vcg::vertex::CurvatureDirfOcf,  /*  0b */
	vcg::vertex::RadiusfOcf         /*  0b */
>{
};

// Currently it does not contains anything.
class CEdge : public vcg::Edge<CUsedTypes,
	vcg::edge::BitFlags,          /*  4b */
	vcg::edge::EVAdj,
	vcg::edge::EEAdj
>{
};

// Each face needs 32 byte, on 32bit arch. and 48 byte on 64bit arch.
class CFace    : public vcg::Face<  CUsedTypes,
	vcg::face::InfoOcf,              /* 4b */
	vcg::face::VertexRef,            /*12b *///V
	vcg::face::BitFlags,             /* 4b */
	vcg::face::Normal3f,             /*12b *///vcg::Point3f
	vcg::face::QualityfOcf,          /* 0b */
	vcg::face::MarkOcf,              /* 0b */
	vcg::face::Color4bOcf,           /* 0b */
	vcg::face::FFAdjOcf,             /* 0b */
	vcg::face::VFAdjOcf,             /* 0b */
	vcg::face::WedgeTexCoordfOcf     /* 0b */
> {};

class PlyHeader : public vcg::ply::PlyFile
{
public:
	int GetVerticesNum(const char* i_cFileName);
};

/*

CMesh
this class defines a container for 3D mesh with texture 

*/
class CMesh : public vcg::tri::TriMesh< vcg::vertex::vector_ocf<CVertex>, vcg::face::vector_ocf<CFace> >  
{
public:
	///////////////////////////////////////
	// public member functions

	void ClearAll();

	// Update the color variety of the 3D mesh
	float GetColorVariety();

	///////////////////////////////////////
	// public static member functions

	static int OpenPly(CMesh &m, const char * filename, vcg::CallBackPos *cb=0);
	static int OpenPly(CMesh &m, const char * filename, int & loadmask, vcg::CallBackPos *cb =0);
	static int OpenPly(CMesh &m, const char * filename, vcg::tri::io::PlyInfo &pi);

	static int SavePly(CMesh &m, const char * filename, bool binary=true );
	static int SavePly(CMesh &m,  const char * filename, int savemask, bool binary = true, vcg::CallBackPos *cb=0);
	static int SavePly(CMesh &m,  const char * filename, bool binary, vcg::tri::io::PlyInfo &pi, vcg::CallBackPos *cb=0);

	static int GetVerticesNum(const char* i_cFileName);

public:
	///////////////////////////////////////
	// public variables

	double m_dAverageDist;
};
typedef std::shared_ptr<CMesh> CMeshPtr;



#endif