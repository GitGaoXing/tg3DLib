#include "tgThread.h"
#include "tgTask.h"

namespace tg
{

Thread::Thread() : m_oTask(nullptr), m_bIsStarted(true)
{
	this->m_oThread = std::thread(StaticLoop , (void*)this);
}

Thread::~Thread()
{
	this->m_oThread.join();
}

void Thread::Loop()
{
	while(this->m_bIsStarted)
	{
		std::unique_lock<std::mutex> l_oLock(this->m_oMutex);
		while(this->m_oTask == nullptr && this->m_bIsStarted)
			this->m_oCond.wait(l_oLock);

		if(!this->m_bIsStarted)
			return;

		this->m_oTask->Run();
		this->m_oTask = nullptr;
	}
}

void* Thread::StaticLoop(void *i_vObject)
{
	((Thread*)i_vObject)->Loop();
	return nullptr;
}

void Thread::RunTask(std::shared_ptr<tg::Task> i_oTask)
{
	std::unique_lock<std::mutex> l_oLock(this->m_oMutex);
	this->m_oTask = i_oTask;
	this->m_oCond.notify_all();
}

void Thread::Stop()
{
	std::unique_lock<std::mutex> l_oLock(this->m_oMutex);
	this->m_bIsStarted = false;
	this->m_oCond.notify_all();
}

}