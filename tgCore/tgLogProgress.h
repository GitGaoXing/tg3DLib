#ifndef ___tgLogProgress___
#define ___tgLogProgress___

#include "tgPrecompile.h"
#include <string>

const int MAX_LOG_SIZE = 8192;
namespace tg
{
namespace Core
{

enum LogType
{
	Normal = 0,
	Error = 1,
	Index = 2,
	Test = 3,
	Warning = 4
};

class LogProgress
{
public:
	// Log
	typedef void CallbackDumpLog(	const LogType&		i_eType				,	// log type
									const bool&			i_bCreate			,	// whether to create a new line
									const std::string&	i_strLog			);

	TG_EXPORT static void DockCallbackDumpLog(CallbackDumpLog* i_pCallbackDumpLog);

	static void signDumpLog(		const LogType&		i_eType			,	// log type
									const bool&			i_bCreate		,	// whether to create a new line
									const std::string&	i_strLog		);	

	// Progress 
	typedef void CallbackUpdateProgress(const int& i_nProgress);// range [0, 100]

	TG_EXPORT static void DockCallbackUpdateProgress(CallbackUpdateProgress* i_pCallbackUpdateProgress);

	static bool signUpdateProgress(	const int& i_nProgress);	// range [0, 100]

	// vcg
	TG_EXPORT static bool CallbackVCG(const int pos, const char* str);

private:
	static CallbackDumpLog* m_pDumpLog;

	static CallbackUpdateProgress* m_pUpdateProgress;

};

TG_EXPORT void signDumpLog(	const LogType&		i_eType				,	// log type
							 const bool&		i_bCreate			,	// whether to create a new line
							 const char*		i_cFormat			,
							 ...									);	

TG_EXPORT bool signUpdateProgress(const int& i_nProgress);	// range [0, 100]

};
};
#endif