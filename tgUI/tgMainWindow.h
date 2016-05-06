#ifndef TGMAINWINDOW_H
#define TGMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QProgressBar>
#include "ui_tgMainWindow.h"
#include "tgCore.h"
#include "tgThread.h"
#include "tgManagerUI.h"
#include <memory>

class tgConsole;
class tgViewer3D;

class tgMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	tgMainWindow(QWidget *parent = 0);
	~tgMainWindow();

	void UpdateProgress(int i_nProgress);

signals:
	void signAddLogItem(int		i_nType,	// log type
						bool	i_bCreate,	// whether to create a new line
						QString i_strLog);	// log context

	void signUpdateProgress(int i_nProgress);

	void signUpdateUI();
	void signFinished(const bool& i_bUpdateScene);

private slots:
	void slotAddSource();
	void slotAddTarget();

	void slotUpdateProgressBar(int i_nProgress);
	void slotUpdateUI();
	void slotFinished(const bool& i_bUpdateScene);

private:
	void Init();
	void InitUI();
	void SetupStatusBar();
	void SetupCentralPannels();
	void SetupDockPannels();

	void LoadSettings();
	void SaveSettings();

	Ui::tgMainWindowClass		ui;

	QProgressBar				*m_oProgressBar;
	int							m_nCurProgress;

	tgViewer3D					*m_oViewer3D;
	tgConsole					*m_oConsole;

	////////////////////////////////////////////
	std::shared_ptr<tg::Thread> m_oThread;

	////////////////////////////////////////////

	static void* m_vReceiver;

	static void staticDumpLog(		const tg::Core::LogType&	i_eType		,
									const bool&					i_bCreate	,
									const std::string&			i_strLog	);

	static void staticUpdateProgress(const int&		i_nProgress);

	static void staticUpdateUI();

	static void staticFinished(const bool& i_bUpdateScene);

};

#endif // TGMAINWINDOW_H
