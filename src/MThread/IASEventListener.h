//////////////////////////////////////////////////////////////////////////
///@file	IASEventListener.h											//
///@brief	class IASEventListener										//
///@author	__ZHUCZ__(zhucz333@163.com)									//
///@date	2019/04/10													//
//////////////////////////////////////////////////////////////////////////

#pragma once
#include "IEventBase.h"
#include <memory>

class IASEventListener
{
public:
	IASEventListener();
	virtual ~IASEventListener();

public:
	virtual void OnEvent(const std::shared_ptr<IEventBase> ptrEvent) const = 0;
};
