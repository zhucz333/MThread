//////////////////////////////////////////////////////////////////////////
///@file	ASEventManager.h													//
///@brief	class ASEventManager												//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/04/10													//
//////////////////////////////////////////////////////////////////////////

#pragma once

#include "MThread.h"
#include "IEventBase.h"
#include "IASEventListener.h"
#include <unordered_map>
#include <shared_mutex>

class ASEventManager
{
public:
	ASEventManager(int workerThreadNum = 1);
	~ASEventManager();

	bool Subscribe(const std::string& strEventKey, const IASEventListener* ptrListener);
	bool UnSubscribe(const std::string& strEventKey, const IASEventListener* ptrListener);
	bool SendEvent(const std::shared_ptr<IEventBase> ptrEvent);

private:
	void DispatchEvent(const IASEventListener* ptrListener, const std::shared_ptr<IEventBase> ptrEvent);

private:
	std::shared_mutex m_mutexListenerMap;
	MThread* m_ptrWorkerThread;
	std::unordered_map<std::string, std::list<const IASEventListener*>> m_mapListener;
};
