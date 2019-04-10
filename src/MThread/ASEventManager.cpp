#include "ASEventManager.h"
#include <shared_mutex>

ASEventManager::ASEventManager(int workerThreadNum)
{
	if (workerThreadNum > 0) {
		m_ptrWorkerThread = new MThread();
		m_ptrWorkerThread->Start(workerThreadNum);
	}
}

ASEventManager::~ASEventManager()
{
	if (m_ptrWorkerThread) {
		delete m_ptrWorkerThread;
		m_ptrWorkerThread = nullptr;
	}
}

bool ASEventManager::Subscribe(const std::string& strEventKey, const IASEventListener* ptrListener)
{
	std::unique_lock<std::shared_mutex> ul(m_mutexListenerMap);
	m_mapListener[strEventKey].push_back(ptrListener);
	return true;
}

bool ASEventManager::UnSubscribe(const std::string& strEventKey, const IASEventListener* ptrListener)
{
	std::unique_lock<std::shared_mutex> ul(m_mutexListenerMap);
	m_mapListener[strEventKey].remove(ptrListener);
	return true;
}

bool ASEventManager::SendEvent(const std::shared_ptr<IEventBase> ptrEvent)
{
	std::string& key = ptrEvent->GetEventKey();
	EventPriority priority = ptrEvent->GetEventPriority();

	std::shared_lock<std::shared_mutex> sl(m_mutexListenerMap);
	for (auto iter = m_mapListener[key].begin(); iter != m_mapListener[key].end(); ++iter) {
		if (EventPriority::NORMAL == priority) {
			m_ptrWorkerThread->Post(std::bind(&ASEventManager::DispatchEvent, this, *iter, ptrEvent));
		}
		else {
			m_ptrWorkerThread->Dispatch(std::bind(&ASEventManager::DispatchEvent, this, *iter, ptrEvent));
		}
	}

	return true;
}

void ASEventManager::DispatchEvent(const IASEventListener* ptrListener, const std::shared_ptr<IEventBase> ptrEvent)
{
	ptrListener->OnEvent(ptrEvent);
}
