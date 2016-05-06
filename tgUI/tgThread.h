#ifndef ___tgThread___
#define ___tgThread___

#include <memory>
#include <thread>            
#include <mutex>              
#include <condition_variable> 

namespace tg
{

class Task;

class Thread
{
public:
	Thread();

	~Thread();

	void RunTask(std::shared_ptr<tg::Task> i_oTask);

	void Stop();

protected:
	void Loop();
	static void* StaticLoop(void* i_vObject);

	std::shared_ptr<tg::Task>	m_oTask				;

	std::thread					m_oThread			;
	std::mutex					m_oMutex			;
	std::condition_variable		m_oCond				;
	bool						m_bIsStarted		;

};

}

#endif