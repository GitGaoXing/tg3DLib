#include "tgCallbackUI.h"

namespace tg
{

void (*CallbackUI::m_pCallbackUpdateUI)() = nullptr;
CallbackUI::CallbackUI()
{

}

void CallbackUI::Run(Task::TG_STAT i_eStat)
{
	this->ModifyUI(i_eStat);
	CallbackUI::signUpdateUI();
}

void CallbackUI::DockCallbackUpdateUI(CallbackUpdateUI* i_pCallbackUpdateUI)
{
	m_pCallbackUpdateUI = i_pCallbackUpdateUI;
}

void CallbackUI::ModifyUI(Task::TG_STAT i_eStat)
{

}

void CallbackUI::signUpdateUI(const bool& i_bUpdateScene)
{
	if(m_pCallbackUpdateUI)
	{
		m_pCallbackUpdateUI();
	}
}

}