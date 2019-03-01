#include "Strand.h"

Strand::Strand(MThread& workers) : m_tWorkers(workers), m_mutexHandlerFunc()
{
}

Strand::~Strand()
{
}

int Strand::Post(HandlerFunc handler)
{
    m_tWorkers.Post(std::bind(&Strand::Warp, this, handler));
    return 0;
}

int Strand::Dispatch(HandlerFunc handler)
{
    m_tWorkers.Dispatch(std::bind(&Strand::Warp, this, handler));
    return 0;
}

void Strand::Warp(HandlerFunc handler)
{
    std::lock_guard<std::mutex> lk(m_mutexHandlerFunc);
    handler();
}
