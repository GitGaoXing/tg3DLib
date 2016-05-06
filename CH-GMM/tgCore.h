#ifndef ___tgCore___
#define ___tgCore___

#include <string>

const int MAX_LOG_SIZE = 8192;
const int MAX_PATH_SIZE = 1024;
namespace tg
{

class Core
{
public:
	// Version
	static std::string GetVersion(); 

	// exe dir
	static std::string GetExeDir();

	// Log
	enum LogType
	{
		Normal = 0,
		Error = 1,
		Index = 2,
		Test = 3,
		Warning = 4
	};

	typedef void CallbackDumpLog(	const int&			i_nType				,	// log type
									const bool&			i_bCreate			,	// whether to create a new line
									const std::string&	i_strLog			);

	static void DockCallbackDumpLog(CallbackDumpLog* i_pCallbackDumpLog);

	static void signDumpLog(		const int&			i_nType				,	// log type
									const bool&			i_bCreate			,	// whether to create a new line
									const char*			i_cFormat			,
									...									);	

	// Progress 
	typedef void CallbackUpdateProgress(const int& i_nProgress);// range [0, 100]

	static void DockCallbackUpdateProgress(CallbackUpdateProgress* i_pCallbackUpdateProgress);

	static bool signUpdateProgress(	const int& i_nProgress);	// range [0, 100]

	// vcg
	static bool CallbackVCG(const int pos, const char* str);

private:
	static std::string m_strVersion;

	static CallbackDumpLog* m_pDumpLog;

	static CallbackUpdateProgress* m_pUpdateProgress;

};

};

#endif