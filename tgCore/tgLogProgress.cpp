#include "tgLogProgress.h"
#include <stdarg.h>

namespace tg
{
namespace Core
{

/////////////////////////////////////////////////////////////
// Log
 void (*LogProgress::m_pDumpLog)(	const LogType&		i_eType				,
									const bool&			i_bCreate			,
									const std::string&	i_strLog			) = nullptr;

 void LogProgress::DockCallbackDumpLog(CallbackDumpLog* i_pCallbackDumpLog)
 {
	m_pDumpLog = i_pCallbackDumpLog;
 }

void LogProgress::signDumpLog(	const LogType&		i_eType			,	// log type
								const bool&			i_bCreate		,	// whether to create a new line
								const std::string&	i_strLog		)
{
	if(m_pDumpLog)
	{
		m_pDumpLog(i_eType, i_bCreate, i_strLog);
	}
}

/////////////////////////////////////////////////////////////
// Progress
void (*LogProgress::m_pUpdateProgress)(const int& i_nProgress) = nullptr;

void LogProgress::DockCallbackUpdateProgress(CallbackUpdateProgress* i_pCallbackUpdateProgress)
{
	m_pUpdateProgress = i_pCallbackUpdateProgress;
}

bool LogProgress::signUpdateProgress(const int& i_nProgress)
{
	if(m_pUpdateProgress)
	{
		m_pUpdateProgress(i_nProgress);
		return true;
	}
	else
	{
		return true;
	}
}

bool LogProgress::CallbackVCG(const int pos, const char* str)
{
	if(m_pUpdateProgress)
	{
		m_pUpdateProgress(pos);
		return true;
	}
	else
	{
		return true;
	}
}

void signDumpLog(const LogType&		i_eType				,	// log type
				 const bool&		i_bCreate			,	// whether to create a new line
				 const char*		i_cFormat			,
				 ...									)
{
	char l_cLog[MAX_LOG_SIZE];
	va_list args;
	va_start( args , i_cFormat );
	_vsnprintf_s( l_cLog , _TRUNCATE, i_cFormat , args );
	va_end( args );

	LogProgress::signDumpLog(i_eType, i_bCreate, l_cLog);
}

bool signUpdateProgress(const int& i_nProgress)
{
	return LogProgress::signUpdateProgress(i_nProgress);
}

}
}