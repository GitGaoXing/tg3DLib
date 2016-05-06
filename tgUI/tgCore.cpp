#include "tgCore.h"
#include <stdarg.h>
#include <Windows.h>

namespace tg
{
/////////////////////////////////////////////////////////////
// Version
std::string Core::m_strVersion = "20160505-NIGHTLY";

std::string Core::GetVersion()
{
	return Core::m_strVersion;
}

/////////////////////////////////////////////////////////////
// Exe dir
std::string Core::GetExeDir()
{
	char l_cPath[MAX_PATH];
	GetModuleFileNameA(NULL, l_cPath, MAX_PATH);
	std::string l_strPath = l_cPath;
	l_strPath = l_strPath.substr(0, l_strPath.find_last_of("/\\") + 1);
	return l_strPath;
}

/////////////////////////////////////////////////////////////
// Log
 void (*Core::m_pDumpLog)(	const int&			i_nType				,
							const bool&			i_bCreate			,
							const std::string&	i_strLog			) = nullptr;

 void Core::DockCallbackDumpLog(CallbackDumpLog* i_pCallbackDumpLog)
 {
	m_pDumpLog = i_pCallbackDumpLog;
 }

void Core::signDumpLog(	const int&		i_nType				,	// log type
						const bool&		i_bCreate			,	// whether to create a new line
						const char*		i_cFormat			,
						...									)
{
	char l_cLog[MAX_LOG_SIZE];
	va_list args;
	va_start( args , i_cFormat );
	_vsnprintf_s( l_cLog , _TRUNCATE, i_cFormat , args );
	va_end( args );

	if(m_pDumpLog)
	{
		m_pDumpLog(i_nType, i_bCreate, l_cLog);
	}
}

/////////////////////////////////////////////////////////////
// Progress
void (*Core::m_pUpdateProgress)(const int& i_nProgress) = nullptr;

void Core::DockCallbackUpdateProgress(CallbackUpdateProgress* i_pCallbackUpdateProgress)
{
	m_pUpdateProgress = i_pCallbackUpdateProgress;
}

bool Core::signUpdateProgress(const int& i_nProgress)
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

bool Core::CallbackVCG(const int pos, const char* str)
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

}