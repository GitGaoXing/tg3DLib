#include "tgTask.h"

#include "tgCallbackUI.h"

namespace tg
{

void (*Task::m_oCallbackFinished)(const bool& i_bUpdateScene) = nullptr;
Task::Task() : m_bUpdateScene(true), m_oPreCallback(nullptr), m_oPostCallback(nullptr)
{

}

Task::~Task()
{

}

Task::TG_STAT Task::Run()
{
	if(this->m_oPreCallback)
	{
		this->m_oPreCallback->Run();
	}

	auto l_eStat = this->RunAlg();

	if(this->m_oPostCallback)
	{
		this->m_oPostCallback->Run(l_eStat);
	}

	if(m_oCallbackFinished)
	{
		m_oCallbackFinished(this->m_bUpdateScene);
	}

	return l_eStat;
}

Task::TG_STAT Task::RunAlg()
{
	tg::Core::signDumpLog(tg::Core::Test, true, "Test thread!");
	return Normal;
}

void Task::SetPreCallback(std::shared_ptr<CallbackUI> i_oPreCallback)
{
	this->m_oPreCallback = i_oPreCallback;
}

void Task::SetPostCallback(std::shared_ptr<CallbackUI> i_oPostCallback)
{
	this->m_oPostCallback = i_oPostCallback;
}

void Task::SetUpdateScene(const bool& i_bUpdateScene)
{
	this->m_bUpdateScene = i_bUpdateScene;
}

void Task::DockCallbackFinished(CallbackFinished* i_oCallbackFinished)
{
	m_oCallbackFinished = i_oCallbackFinished;
}

}