#ifndef ___tgManagerUI___
#define ___tgManagerUI___

#include "tgCallbackUI.h"
#include <vector>

namespace tg
{

class ManagerUI
{
public:
	enum
	{
		Action_Add_Source = 0,
		Action_Add_Target = 1
	};
	static std::vector<char> ObjUI;	// try using std::map

};

class LockUI4Add : public CallbackUI
{
protected:
	virtual void ModifyUI(Task::TG_STAT i_eStat)
	{
		ManagerUI::ObjUI[ManagerUI::Action_Add_Source] = 1;
		ManagerUI::ObjUI[ManagerUI::Action_Add_Target] = 1;
	}
};

class UnlockUI4Add : public CallbackUI
{
protected:
	virtual void ModifyUI(Task::TG_STAT i_eStat)
	{
		ManagerUI::ObjUI[ManagerUI::Action_Add_Source] = 0;
		ManagerUI::ObjUI[ManagerUI::Action_Add_Target] = 0;
	}
};

}

#endif