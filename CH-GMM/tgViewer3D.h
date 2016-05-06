#ifndef TGVIEWER3D_H
#define TGVIEWER3D_H

#include <GL/glew.h>

#include <QGLWidget>

// wrapper imports
#include <wrap/gl/space.h>
#include <wrap/gl/trimesh.h>
#include <wrap/gui/trackball.h>

#include "tgVCG.h"

class tgViewer3D : public QGLWidget
{
	Q_OBJECT

public:
	tgViewer3D(QWidget *parent);
	~tgViewer3D();

	void SetBusy(const bool& i_bBusy);

	CMesh m_oMeshSourceR;
	CMesh m_oMeshTargetR;
	vcg::GlTrimesh<CMesh> m_oWrapSource;
	vcg::GlTrimesh<CMesh> m_oWrapTarget;
	vcg::Matrix44d m_matZoom2Box;	// matrix to transform the mesh to its bounding box

private:
	// opengl initialization and drawing calls
	void initializeGL ();
	void resizeGL (int w, int h);
	void paintGL();

	void SetRenderConfig(int w,int h);

	 /// keyboard and mouse event callbacks
	void keyReleaseEvent(QKeyEvent * e);
	void keyPressEvent(QKeyEvent * e);
	void mousePressEvent(QMouseEvent*e);
	void mouseMoveEvent(QMouseEvent*e);
	void mouseReleaseEvent(QMouseEvent*e);
	void wheelEvent(QWheelEvent*e); 

	void drawGradient();
	void drawAxis();
	void drawString(const char *i_cStr);
	void drawModel();
	void drawTrackball();


	vcg::Trackball						m_oTrackball		;	// the active manipulator
	vcg::Point4d						m_ptEye				;	// eye point

	bool								m_bBusy				;
};

#endif // TGVIEWER3D_H
