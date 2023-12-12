#include "pch.h"
#include "Timer.h"
#include "TimeMgr.h"
#include "Object.h"

Timer::Timer()
	: _curTime(0)
	, _time(0)
	, _onTimer(false)
	, _ownerObject(nullptr)
{
}

Timer::~Timer()
{
}

void Timer::Update()
{
	if (!_onTimer)
		return;

	_time += DeltaTime;

	if (_time >= _curTime)
	{
		TimeManager::GetInstance()->PopTime(_idx);
		if(_ownerObject != nullptr)
			_ownerObject->EndTimer(this);
		_onTimer = false;
	}
}

void Timer::SetTimer(float time, Object* obj)
{
	_curTime = time;
	_ownerObject = obj;
	_onTimer = true;
}
