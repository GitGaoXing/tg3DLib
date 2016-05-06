#include "tgViewer3D.h"

#include <QMessageBox>
#include <QKeyEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <wrap/qt/trackball.h>

#include "tgData.h"

tgViewer3D::tgViewer3D(QWidget *parent)
	: QGLWidget(parent), m_bBusy(false), m_ptEye(0, 0, 3, 1)
{
	this->m_oWrapSource.m = &this->m_oMeshSourceR;
	this->m_oWrapSource.Update();

	this->m_oWrapTarget.m = &this->m_oMeshTargetR;
	this->m_oWrapTarget.Update();
}

tgViewer3D::~tgViewer3D()
{

}

void tgViewer3D::SetBusy(const bool& i_bBusy)
{
	this->m_bBusy = i_bBusy;
	this->setEnabled(!i_bBusy);
	this->updateGL();
}

// opengl initialization and drawing calls
void tgViewer3D::initializeGL ()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void tgViewer3D::resizeGL (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	this->initializeGL();
}

void tgViewer3D::paintGL()
{
	if(this->m_bBusy)
		return;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->SetRenderConfig(tgViewer3D::width() , tgViewer3D::height());

	///////////////////////////////////////
	// draw background
	this->drawGradient();     

	///////////////////////////////////////
	// draw model
	this->drawModel();

	///////////////////////////////////////
	// draw axis
	this->drawAxis();

	///////////////////////////////////////
	// draw trackball
	this->drawTrackball();

	glPopAttrib();
}

void tgViewer3D::SetRenderConfig(int w,int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective( 60 , (float)w / (float)h , 0.001 , 1000 );	// fov, viewRatio, fAspect, nearPlane, farPlane
	
	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();
	gluLookAt(this->m_ptEye.X(), this->m_ptEye.Y(), this->m_ptEye.Z(), 0, 0, 0, 0, 1, 0);
}

void tgViewer3D::drawGradient()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-1, 1, -1, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_STRIP);

	vcg::Color4b backgroundTopColor = vcg::Color4b(0x40, 0x40, 0x40, 255);
	vcg::Color4b backgroundBotColor = vcg::Color4b(0xc3, 0xc3, 0xff, 255);

	glColor(backgroundTopColor);  	glVertex2f(-1, 1);
	glColor(backgroundBotColor);	glVertex2f(-1, -1);
	glColor(backgroundTopColor);	glVertex2f(1, 1);
	glColor(backgroundBotColor);	glVertex2f(1, -1);
	glEnd();
	glPopAttrib();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
}

void tgViewer3D::drawAxis()
{
	float l_fLocation = 1.40;
	////////////////////////////////////////////////////////
    glPushMatrix();
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND); 
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

	glViewport(this->width() * 0.8 + (this->width() - this->height()) * 0.1, 0.0, this->width() * 0.2, this->height() * 0.2);

	vcg::Matrix44f l_matRotation;
	this->m_oTrackball.track.rot.ToMatrix(l_matRotation);
	glMultMatrix (l_matRotation);

	/////////////////////////////////////
	glLineWidth(1.5);
	glColor3f( 1.0f, 0.0f, 0.0f ); // blue
    glBegin( GL_LINES );
    {
        // x-axis
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 1.0f, 0.0f, 0.0f);
    }
    glEnd();

	glRasterPos3f(1.25f, 0.0f, 0.0f);
    this->drawString("x");

    glColor3f( 0.0f, 1.0f, 0.0f ); // green
    glBegin( GL_LINES );
    {
        // y-axis
        glVertex3f( 0.0f, 0.0f, 0.0f);
        glVertex3f( 0.0f, 1.0f, 0.0f);
    }
    glEnd();

	glRasterPos3f(0.0f, 1.25f, 0.0f);
    this->drawString("y");

    glColor3f( 0.0f, 0.0f, 1.0f ); // red
    glBegin( GL_LINES );
    {
        // z-axis
        glVertex3f( 0.0f, 0.0f, 0.0f );
        glVertex3f( 0.0f, 0.0f, 1.0f );
    }
    glEnd();

	glRasterPos3f(0.0f, 0.0f, 1.25f );
    this->drawString("z");

	glColor3f( 1.0f, 1.0f, 1.0f ); // white

	glViewport(0, 0, (float)this->width(), (float)this->height());
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_BLEND); 
    glPopMatrix();
}

void tgViewer3D::drawString(const char *i_cStr)
{
	static int isFirstCall = 1;
    static GLuint lists;

    if( isFirstCall ) 
	{ 
         isFirstCall = 0;
         lists = glGenLists(256);
         wglUseFontBitmaps(wglGetCurrentDC(), 0, 256, lists);
     }
    for(; *i_cStr!='\0'; ++i_cStr)
         glCallList(lists + *i_cStr);
}

void tgViewer3D::drawModel()
{
	glPushMatrix();
	glMultMatrix (this->m_oTrackball.Matrix());
	glMultMatrix(this->m_matZoom2Box);

	glDisable(GL_CULL_FACE);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);

	if(this->m_oMeshSourceR.face.size() > 0)
	{
		this->m_oWrapSource.Draw<vcg::GLW::DMFlat, vcg::GLW::CMPerVert,vcg::GLW::TMNone> ();
	}
	else if(this->m_oMeshSourceR.vert.size() > 0)
	{
//#define USE_VCG
#ifdef USE_VCG
		this->m_oWrapSource.Draw<vcg::GLW::DMPoints, vcg::GLW::CMPerVert,vcg::GLW::TMNone> ();
#else
		glPointSize(2);
		glBegin(GL_POINTS);  
		for(auto& iter : this->m_oMeshSourceR.vert)
		{
			glColor3ub(iter.C()[0] , iter.C()[1] , iter.C()[2] );
			glVertex3d(iter.P()[0] , iter.P()[1] , iter.P()[2] );
		}
		glEnd();
#endif
	}

	if(this->m_oMeshTargetR.face.size() > 0)
	{
		this->m_oWrapTarget.Draw<vcg::GLW::DMFlat, vcg::GLW::CMPerVert,vcg::GLW::TMNone> ();
	}
	else if(this->m_oMeshTargetR.vert.size() > 0)
	{
#ifdef USE_VCG
		this->m_oWrapTarget.Draw<vcg::GLW::DMPoints, vcg::GLW::CMPerVert,vcg::GLW::TMNone> ();
#else
		glPointSize(2);
		glBegin(GL_POINTS);  
		for(auto& iter : this->m_oMeshTargetR.vert)
		{
			glColor3ub(iter.C()[0] , iter.C()[1] , iter.C()[2] );
			glVertex3d(iter.P()[0] , iter.P()[1] , iter.P()[2] );
		}
		glEnd();
#endif
	}
	glEnable(GL_CULL_FACE);

    glPopMatrix();
}

void tgViewer3D::drawTrackball()
{
	glColor3f( 1.0f, 1.0f, 1.0f ); // white

	this->m_oTrackball.center = vcg::Point3f(0, 0, 0);	
	this->m_oTrackball.radius = 1;
	this->m_oTrackball.GetView();
	this->m_oTrackball.Apply();

	this->m_oTrackball.DrawPostApply();
}

void tgViewer3D::keyReleaseEvent (QKeyEvent * e)
{
	e->ignore ();
	if (e->key () == Qt::Key_Control)
		this->m_oTrackball.ButtonUp (QT2VCG (Qt::NoButton, Qt::ControlModifier));
	if (e->key () == Qt::Key_Shift)
		this->m_oTrackball.ButtonUp (QT2VCG (Qt::NoButton, Qt::ShiftModifier));
	if (e->key () == Qt::Key_Alt)
		this->m_oTrackball.ButtonUp (QT2VCG (Qt::NoButton, Qt::AltModifier));
	this->updateGL ();
}

void tgViewer3D::keyPressEvent (QKeyEvent * e)
{
	e->ignore ();
	if (e->key () == Qt::Key_Control)
		this->m_oTrackball.ButtonDown (QT2VCG (Qt::NoButton, Qt::ControlModifier));
	if (e->key () == Qt::Key_Shift)
		this->m_oTrackball.ButtonDown (QT2VCG (Qt::NoButton, Qt::ShiftModifier));
	if (e->key () == Qt::Key_Alt)
		this->m_oTrackball.ButtonDown (QT2VCG (Qt::NoButton, Qt::AltModifier));
	if (e->key () == Qt::Key_Space)
	{
		this->m_oTrackball.Reset(); 
	}
	this->updateGL ();
}

void tgViewer3D::mousePressEvent (QMouseEvent * e)
{
	e->accept ();
	this->setFocus ();
	this->m_oTrackball.MouseDown (QT2VCG_X(this,e), QT2VCG_Y(this,e), QT2VCG (e->button (), e->modifiers ()));
	this->updateGL ();
}

void tgViewer3D::mouseMoveEvent (QMouseEvent * e)
{
	if (e->buttons ()) 
	{
		this->m_oTrackball.MouseMove (QT2VCG_X(this,e), QT2VCG_Y(this,e));
		this->updateGL ();
	}
}

void tgViewer3D::mouseReleaseEvent (QMouseEvent * e)
{
	this->m_oTrackball.MouseUp (QT2VCG_X(this,e), QT2VCG_Y(this,e), QT2VCG (e->button (), e->modifiers ()));
	this->updateGL ();
}

void tgViewer3D::wheelEvent (QWheelEvent * e)
{
	const int WHEEL_STEP = 120;
	this->m_oTrackball.MouseWheel (e->delta () / float (WHEEL_STEP), QTWheel2VCG (e->modifiers ()));
	this->updateGL ();
}
