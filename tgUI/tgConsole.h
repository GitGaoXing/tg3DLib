#ifndef TGCONSOLE_H
#define TGCONSOLE_H

#include <QWidget>
#include "ui_tgConsole.h"

class tgConsole : public QWidget
{
	Q_OBJECT

public:
	tgConsole(QWidget *parent = 0);
	~tgConsole();

public slots:
	// this function is to add log item
	void slotAddLogItem(int		i_nType,	// log type
						bool	i_bCreate,	// whether to create a new line
						QString i_strLog);	// log context

private:
	Ui::tgConsole ui;
	int m_nNumOfLog;
};

#endif // TGCONSOLE_H
