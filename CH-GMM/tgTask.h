#ifndef ___tgTask___
#define ___tgTask___

#include "tgCore.h"
#include "tgParam.h"
#include "tgData.h"
#include <memory>

namespace tg
{

class CallbackUI;

class Task
{
public:
	Task();

	~Task();

	enum TG_STAT
	{
		Normal = 1,
		Canceled = 0,
		Error = -1
	};
	TG_STAT Run();

	void SetPreCallback(std::shared_ptr<CallbackUI> i_oPreCallback);
	void SetPostCallback(std::shared_ptr<CallbackUI> i_oPostCallback);

	typedef void CallbackFinished(const bool& i_bUpdateScene);

	void SetUpdateScene(const bool& i_bUpdateScene);

	static void DockCallbackFinished(CallbackFinished* i_oCallbackFinished);

protected:
	virtual TG_STAT RunAlg();

private:
	std::shared_ptr<CallbackUI> m_oPreCallback;
	std::shared_ptr<CallbackUI> m_oPostCallback;

	static CallbackFinished* m_oCallbackFinished;
	bool m_bUpdateScene;

};

}

#endif