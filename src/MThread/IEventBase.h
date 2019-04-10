//////////////////////////////////////////////////////////////////////////
///@file	IEventBase.h												//
///@brief	class IEventBase											//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/04/10													//
//////////////////////////////////////////////////////////////////////////

#pragma once
#include <string>

enum class EventPriority : int 
{
	NORMAL = 0,
	URGENT
};

class IEventBase
{
public:
	IEventBase() {};
	virtual ~IEventBase() {};

public:
	virtual std::string& GetEventKey() = 0;
	virtual EventPriority GetEventPriority() = 0;

protected:
	std::string m_strEventKey;
	EventPriority m_ePriority;
};