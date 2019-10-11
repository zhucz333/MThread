//////////////////////////////////////////////////////////////////////////
///@file	MThread.h													//
///@brief	class MThread												//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/03/04													//
//////////////////////////////////////////////////////////////////////////

#ifndef __MTHREAD_H__
#define __MTHREAD_H__

#include <list>
#include <vector>
#include <thread>
#include <functional>
#include <atomic>
#include <mutex>
#include <condition_variable>

typedef std::function<void()> HandlerFunc;
typedef std::function<void()> ThreadInitFunc;

class MThread 
{
public:
    MThread(ThreadInitFunc init = std::bind(&MThread::ThreadInit));
    ~MThread();

	static void ThreadInit() {};
    int Start(int threadNum = 1);
    int Stop();
	int Clear();
    int Post(HandlerFunc handler);
    int Dispatch(HandlerFunc handler);

private:
    void Worker();
    
private:
    int m_nThreadNum; 
    
	ThreadInitFunc m_pfnInitFunc;
    std::atomic<bool> m_bStart;
    std::list<HandlerFunc> m_listHandlerFunc;
    std::condition_variable m_cvHandlerFunc;
    std::mutex m_mutexHandlerFunc;
    std::list<std::thread*> m_listThread;
} ;

#endif
