#include "tgConsole.h"
#include "tgCore.h"
#include <QDateTime>

tgConsole::tgConsole(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->m_nNumOfLog = -1;

	QString l_strInfo = tr("tg3DLib ") + QString::fromLocal8Bit(tg::Core::GetVersion().c_str()) + tr(" (64 bit)");
	this->ui.textEditLog->insertPlainText(l_strInfo);
}

tgConsole::~tgConsole()
{

}

void tgConsole::slotAddLogItem(	int		i_nType,	// log type
								bool	i_bCreate,	// whether to create a new line
								QString i_strLog)	// log context
{
	QTextCursor l_cursorEnd = this->ui.textEditLog->textCursor();
    l_cursorEnd.movePosition(QTextCursor::End);
    this->ui.textEditLog->setTextCursor(l_cursorEnd);

	switch(i_nType)
	{
	case tg::Core::Normal:
		this->ui.textEditLog->setTextColor(Qt::blue);
		break;
	case tg::Core::Error:
		this->ui.textEditLog->setTextColor(Qt::red);
		break;
	case tg::Core::Index:
		this->ui.textEditLog->setTextColor(Qt::black);
		break;
	case tg::Core::Test:
		this->ui.textEditLog->setTextColor(Qt::darkCyan);
		break;
	case tg::Core::Warning:
		this->ui.textEditLog->setTextColor(Qt::darkMagenta);
		break;
	default:
		this->ui.textEditLog->setTextColor(Qt::black);
	};

	if(i_bCreate)
	{
		this->m_nNumOfLog++;
		if(this->m_nNumOfLog > 2000)
		{
			this->ui.textEditLog->clear();
			this->m_nNumOfLog = -1;
		}
		QString l_strTime = QDateTime::currentDateTime().toString("[hh:mm:ss] ");
		this->ui.textEditLog->insertPlainText(QString("\n") + l_strTime + i_strLog);
	}
	else
	{
		this->ui.textEditLog->insertPlainText(i_strLog);
	}

    l_cursorEnd.movePosition(QTextCursor::End);
    this->ui.textEditLog->setTextCursor(l_cursorEnd);

}