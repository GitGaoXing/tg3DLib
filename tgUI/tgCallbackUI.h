#ifndef ___tgCallbackUI___
#define ___tgCallbackUI___

#include "tgTask.h"

namespace tg
{

class CallbackUI
{
public:
	CallbackUI();

	void Run(Task::TG_STAT i_eStat = Task::Normal);

	typedef void CallbackUpdateUI();

	static void DockCallbackUpdateUI(CallbackUpdateUI* i_pCallbackUpdateUI);

protected:
	virtual void ModifyUI(Task::TG_STAT i_eStat);

private:
	static void signUpdateUI(const bool& i_bUpdateScene = true);

	static CallbackUpdateUI* m_pCallbackUpdateUI;
};

}
#endif