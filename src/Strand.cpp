#include "Strand.h"

Strand::Strand(MThread& workers) : m_tWorkers(workers), m_mutexHandlerFunc()
{
}

Strand::~Strand()
{
}

int Strand::Post(HandlerFunc handler)
{
	HandlerFunc func = std::bind(&Strand::Warp, this, handler);
    m_tWorkers.Post(func);
    return 0;
}

int Strand::Dispatch(HandlerFunc handler)
{
	HandlerFunc func = std::bind(&Strand::Warp, this, handler);
    m_tWorkers.Dispatch(func);
    return 0;
}

void Strand::Warp(HandlerFunc handler)
{
    std::unique_lock<std::mutex> ul(m_mutexHandlerFunc);
    handler();
}
