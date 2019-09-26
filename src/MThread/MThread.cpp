#include "MThread.h"

MThread::MThread(ThreadInitFunc init) : m_mutexHandlerFunc()
{
    m_bStart = false;
    m_nThreadNum = 1;
	m_pfnInitFunc = init;
}

MThread::~MThread()
{
}

int MThread::Start(int threadNum)
{
    if (0 == threadNum) {
        threadNum = std::thread::hardware_concurrency();
    }

    m_nThreadNum = threadNum;

    m_bStart = true;

    for (int i = 0; i < m_nThreadNum; i++) {
        m_listThread.push_back(new std::thread(&MThread::Worker, this));
    }

    return 0;
}

int MThread::Stop()
{
    m_bStart = false;
    
    for (auto var : m_listThread) {
	    var->join();
	    delete var;
    }

    return 0;
}

int MThread::Post(HandlerFunc handler)
{
	{
		std::unique_lock<std::mutex> ul(m_mutexHandlerFunc);
		m_listHandlerFunc.push_back(handler);
	}
	m_cvHandlerFunc.notify_one();

    return 0;
}

int MThread::Dispatch(HandlerFunc handler)
{
	{
		std::unique_lock<std::mutex> ul(m_mutexHandlerFunc);
		m_listHandlerFunc.push_front(handler);
	}
	m_cvHandlerFunc.notify_one();

    return 0;
}

void MThread::Worker()
{
	m_pfnInitFunc();

    while (m_bStart) {
        HandlerFunc func;
        {
            std::unique_lock<std::mutex> ul(m_mutexHandlerFunc);
			if (m_listHandlerFunc.empty()) {
				if (!m_cvHandlerFunc.wait_for(ul, std::chrono::milliseconds(100), [this] {return !m_listHandlerFunc.empty(); })) {
					continue;
				}
			}

            func = m_listHandlerFunc.front();
            m_listHandlerFunc.pop_front();
        }

        func();
    }
}
