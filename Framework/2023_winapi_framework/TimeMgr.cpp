#include "pch.h"
#include "TimeMgr.h"
#include "Core.h"
#include "DebugManager.h"
//#include <chrono> // ns
void TimeManager::Init()
{
	_llPrevCount = {};
	_llCurCount = {};
	_llFrequency = {};	
	_frameCount = 0;
	_fps = 0;
	_accFrameTime = 0.f;
	// 현재 카운트의 틱을 가져온다.(지난시간)
	// 1초 2초 이런 초가 아니야. Frequency로 알아야해.
	QueryPerformanceCounter(&_llPrevCount);

	// 초당 카운트 횟수를 반환합니다.
	// 현재 타이머가 동작하는 주파수를 반환합니다. 
	// <-> 주기: 한번 진동하는데 걸리는 시간
	QueryPerformanceFrequency(&_llFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&_llCurCount);

	// Delta Time: 한 프레임에 걸린 시간.
	_deltaTime = (float)(_llCurCount.QuadPart - _llPrevCount.QuadPart) / (float)_llFrequency.QuadPart;

	// FPS: Frame Per Second
	_llPrevCount = _llCurCount;
	//	1. / m_dT;
	_frameCount++; // 프레임 호출 누적
	_accFrameTime += _deltaTime; // 시간 누적
	if (_accFrameTime >= 1.f) // 1초
	{
		_fps = (UINT)(_frameCount / _accFrameTime);
		_accFrameTime = 0.f;
		_frameCount = 0;
		static wchar_t titlebuf[50] = {};		
		swprintf_s(titlebuf, L"FPS: %d, DT: %f", _fps, _deltaTime);
		//wsprintf();
		//SetWindowText(Core::GetInst()->GetHwnd(), titlebuf);
	}
}

bool TimeManager::TimePass(float duration)
{
	float time = 0;
	while (time <= duration)
	{
		int a = 0;
		time += _deltaTime;
		continue;
	}
	DebugManager::GetInstance()->SetLog(L" 지남");
	return true;
}
