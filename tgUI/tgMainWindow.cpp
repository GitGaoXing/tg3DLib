#include "tgMainWindow.h"
#include "tgConsole.h"
#include "tgViewer3D.h"

#include "tgCallbackUI.h"
#include "tgCopy4Render.h"
#include "tgMeshIO.h"

#include "tgData.h"

#include <QFileDialog>
#include <QSettings>


void* tgMainWindow::m_vReceiver = nullptr;
tgMainWindow::tgMainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	this->Init();
}

tgMainWindow::~tgMainWindow()
{
	this->SaveSettings();
	this->m_oThread->Stop();
}

void tgMainWindow::Init()
{
	m_vReceiver = this;
	tg::Core::DockCallbackDumpLog(tgMainWindow::staticDumpLog);
	tg::Core::DockCallbackUpdateProgress(tgMainWindow::staticUpdateProgress);

	tg::CallbackUI::DockCallbackUpdateUI(tgMainWindow::staticUpdateUI);

	tg::Task::DockCallbackFinished(tgMainWindow::staticFinished);

	///////////////////////////////

	this->InitUI();

	this->connect(this, &tgMainWindow::signAddLogItem, this->m_oConsole, &tgConsole::slotAddLogItem);
	this->connect(this, &tgMainWindow::signUpdateProgress, this, &tgMainWindow::slotUpdateProgressBar);
	this->connect(this, &tgMainWindow::signUpdateUI, this, &tgMainWindow::slotUpdateUI);
	this->connect(this, &tgMainWindow::signFinished, this, &tgMainWindow::slotFinished);

	this->connect(this->ui.actionAdd_Source, &QAction::triggered, this, &tgMainWindow::slotAddSource);
	this->connect(this->ui.actionAdd_Target, &QAction::triggered, this, &tgMainWindow::slotAddTarget);

	///////////////////////////////
	QActionGroup* l_oRenderMode = new QActionGroup(this);
	l_oRenderMode->addAction(this->ui.actionRender_Points);
	l_oRenderMode->addAction(this->ui.actionRender_Wire);
	l_oRenderMode->addAction(this->ui.actionRender_FlatWire);
	l_oRenderMode->addAction(this->ui.actionRender_Flat);
	this->ui.actionRender_Points->setChecked(true);

	///////////////////////////////
	QActionGroup* l_oRenderObject = new QActionGroup(this);
	l_oRenderObject->addAction(this->ui.actionShow_Model);
	l_oRenderObject->addAction(this->ui.actionShow_ConvexHull);
	this->ui.actionShow_Model->setChecked(true);

	///////////////////////////////
	this->m_oThread = std::shared_ptr<tg::Thread>(new tg::Thread);

	this->LoadSettings();
}

void tgMainWindow::InitUI()
{
	this->ui.setupUi(this);

	this->SetupStatusBar();

	this->SetupCentralPannels();

	this->SetupDockPannels();
}

void tgMainWindow::SetupStatusBar()
{
	this->ui.statusBar->setContentsMargins(0, 0, 0, 0);
	this->ui.statusBar->setStyleSheet(QString("QStatusBar::item{border: 0px}"));

	//this->m_oStatusLabelRight = new QLabel(this);
	//this->m_oStatusLabelRight->clear();
	//this->ui.statusBar->addPermanentWidget(this->m_oStatusLabelRight);

	//this->m_oStatusLabelLeft = new QLabel(this);
	//this->m_oStatusLabelLeft->clear();
	//this->ui.statusBar->addWidget(this->m_oStatusLabelLeft);

//	this->ui.statusBar->addWidget(this->m_oStatusLabel);

	this->m_nCurProgress = -1;
	this->m_oProgressBar = new QProgressBar(this);
	this->m_oProgressBar->setTextVisible(true);
	this->ui.statusBar->addPermanentWidget(this->m_oProgressBar, 0);
	this->m_oProgressBar->setVisible(false);
}

void tgMainWindow::SetupCentralPannels()
{
	this->m_oViewer3D = new tgViewer3D(this);

	this->setCentralWidget(this->m_oViewer3D);
}

void tgMainWindow::SetupDockPannels()
{
	this->setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);

	this->m_oConsole = new tgConsole(this);
	this->ui.dockWidgetConsole->setWidget(this->m_oConsole);
}

void tgMainWindow::slotAddSource()
{
	QString l_strFileNameQt;
	l_strFileNameQt = QFileDialog::getOpenFileName(	this,
													tr("Add Source"),
													QString::fromLocal8Bit(tg::Param::Instance()->Get("Path.AddSource.String", std::string("")).toString().c_str()),
													tr("PLY( *.ply )"));

	if(l_strFileNameQt.size() == 0)
		return;

	tg::Param::Instance()->Set("Path.AddSource.String", std::string(l_strFileNameQt.toLocal8Bit()));
	tg::Core::signDumpLog(tg::Core::Normal, true, "Adding Source...");

	////////////////////////////////////////////////
	std::shared_ptr<tg::MeshIO> l_oTask(new tg::MeshIO);
	l_oTask->SetInput(tg::Param::Instance()->Get("Path.AddSource.String", std::string("")).toString().c_str());
	l_oTask->SetOutput(&tg::Data::Instance()->m_oMeshSource);
	std::shared_ptr<tg::LockUI4Add> l_oPreCallback(new tg::LockUI4Add);
	l_oTask->SetPreCallback(l_oPreCallback);
	std::shared_ptr<tg::UnlockUI4Add> l_oPostCallback(new tg::UnlockUI4Add);
	l_oTask->SetPostCallback(l_oPostCallback);

	l_oTask->SetUpdateScene(true);

	this->m_oThread->RunTask(l_oTask);
}

void tgMainWindow::slotAddTarget()
{
	QString l_strFileNameQt;
	l_strFileNameQt = QFileDialog::getOpenFileName(	this,
													tr("Add Target"),
													QString::fromLocal8Bit(tg::Param::Instance()->Get("Path.AddTarget.String", std::string("")).toString().c_str()),
													tr("PLY( *.ply )"));

	if(l_strFileNameQt.size() == 0)
		return;

	tg::Param::Instance()->Set("Path.AddTarget.String", std::string(l_strFileNameQt.toLocal8Bit()));
	tg::Core::signDumpLog(tg::Core::Normal, true, "Adding Target...");

	////////////////////////////////////////////////
	std::shared_ptr<tg::MeshIO> l_oTask(new tg::MeshIO);
	l_oTask->SetInput(tg::Param::Instance()->Get("Path.AddTarget.String", std::string("")).toString().c_str());
	l_oTask->SetOutput(&tg::Data::Instance()->m_oMeshTarget);
	std::shared_ptr<tg::LockUI4Add> l_oPreCallback(new tg::LockUI4Add);
	l_oTask->SetPreCallback(l_oPreCallback);
	std::shared_ptr<tg::UnlockUI4Add> l_oPostCallback(new tg::UnlockUI4Add);
	l_oTask->SetPostCallback(l_oPostCallback);

	l_oTask->SetUpdateScene(true);

	this->m_oThread->RunTask(l_oTask);
}

void tgMainWindow::UpdateProgress(int i_nProgress)
{
	if(i_nProgress != this->m_nCurProgress)
	{
		this->m_nCurProgress = i_nProgress;
		this->signUpdateProgress(this->m_nCurProgress);
	}
}

void tgMainWindow::slotUpdateProgressBar(int i_nProgress)
{
	this->m_oProgressBar->setVisible(true);
	this->m_oProgressBar->setValue(i_nProgress);
	this->update();
}

void tgMainWindow::slotUpdateUI()
{
	// source
	if(tg::ManagerUI::ObjUI[tg::ManagerUI::Action_Add_Source] == 0)
	{
		this->ui.actionAdd_Source->setEnabled(true);
	}
	else
	{
		this->ui.actionAdd_Source->setEnabled(false);
	}
	
	// target
	if(tg::ManagerUI::ObjUI[tg::ManagerUI::Action_Add_Target] == 0)
	{
		this->ui.actionAdd_Target->setEnabled(true);
	}
	else
	{
		this->ui.actionAdd_Target->setEnabled(false);
	}
}

void tgMainWindow::slotFinished(const bool& i_bUpdateScene)
{
	this->m_oProgressBar->reset();
	this->m_oProgressBar->setVisible(false);
	this->update();

	/////////////////////////////////////////
	if(i_bUpdateScene)
	{
		std::shared_ptr<tg::Copy4Render> l_oTask(new tg::Copy4Render);
		l_oTask->SetInput(&tg::Data::Instance()->m_oMeshSource, &tg::Data::Instance()->m_oMeshTarget);
		l_oTask->SetOutput(&this->m_oViewer3D->m_oMeshSourceR, &this->m_oViewer3D->m_oMeshTargetR, &this->m_oViewer3D->m_matZoom2Box);
		std::shared_ptr<tg::LockUI4Add> l_oPreCallback(new tg::LockUI4Add);
		l_oTask->SetPreCallback(l_oPreCallback);
		std::shared_ptr<tg::UnlockUI4Add> l_oPostCallback(new tg::UnlockUI4Add);
		l_oTask->SetPostCallback(l_oPostCallback);
		l_oTask->SetUpdateScene(false);
		this->m_oViewer3D->SetBusy(true);
		this->m_oThread->RunTask(l_oTask);
	}
	else
	{
		this->m_oViewer3D->SetBusy(false);	
	}
}

void tgMainWindow::staticDumpLog(	const int&			i_nType		,
									const bool&			i_bCreate	,
									const std::string&	i_strLog	)
{
	tgMainWindow *l_oReceiver = (tgMainWindow *)m_vReceiver;
	l_oReceiver->signAddLogItem(i_nType, i_bCreate, QString::fromLocal8Bit(i_strLog.c_str()));
}

void tgMainWindow::staticUpdateProgress(const int&		i_nProgress)
{
	tgMainWindow *l_oReceiver = (tgMainWindow *)m_vReceiver;
	l_oReceiver->UpdateProgress(i_nProgress);
}

void tgMainWindow::staticUpdateUI()
{
	tgMainWindow *l_oReceiver = (tgMainWindow *)m_vReceiver;
	l_oReceiver->signUpdateUI();
}

void tgMainWindow::staticFinished(const bool& i_bUpdateScene)
{
	tgMainWindow *l_oReceiver = (tgMainWindow *)m_vReceiver;
	l_oReceiver->signFinished(i_bUpdateScene);
}

void tgMainWindow::LoadSettings()
{
	std::string l_strPath = tg::Core::GetExeDir() + "Config.ini";	
	QSettings l_oSettings(QString::fromLocal8Bit(l_strPath.c_str()), QSettings::IniFormat);
	l_oSettings.beginGroup("Config");

	restoreGeometry(l_oSettings.value("Geometry").toByteArray());
	restoreState(l_oSettings.value("State").toByteArray());

	tg::Param::Instance()->Set("Path.AddSource.String", std::string(l_oSettings.value("Path.AddSource.String", "").toString().toLocal8Bit()));
	tg::Param::Instance()->Set("Path.AddTarget.String", std::string(l_oSettings.value("Path.AddTarget.String", "").toString().toLocal8Bit()));

	l_oSettings.endGroup();
}

void tgMainWindow::SaveSettings()
{
	std::string l_strPath = tg::Core::GetExeDir() + "Config.ini";	
	QSettings l_oSettings(QString::fromLocal8Bit(l_strPath.c_str()), QSettings::IniFormat);
	l_oSettings.beginGroup("Config");

	l_oSettings.setValue("Geometry", saveGeometry());
	l_oSettings.setValue("State", saveState());

	l_oSettings.setValue("Path.AddSource.String", QString::fromLocal8Bit(tg::Param::Instance()->Get("Path.AddSource.String", std::string("")).toString().c_str()));
	l_oSettings.setValue("Path.AddTarget.String", QString::fromLocal8Bit(tg::Param::Instance()->Get("Path.AddTarget.String", std::string("")).toString().c_str()));

	l_oSettings.endGroup();
}
