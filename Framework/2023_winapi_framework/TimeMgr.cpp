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
	// ���� ī��Ʈ�� ƽ�� �����´�.(�����ð�)
	// 1�� 2�� �̷� �ʰ� �ƴϾ�. Frequency�� �˾ƾ���.
	QueryPerformanceCounter(&_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ���� ��ȯ�մϴ�.
	// ���� Ÿ�̸Ӱ� �����ϴ� ���ļ��� ��ȯ�մϴ�. 
	// <-> �ֱ�: �ѹ� �����ϴµ� �ɸ��� �ð�
	QueryPerformanceFrequency(&_llFrequency);
}

void TimeManager::Update()
{
	QueryPerformanceCounter(&_llCurCount);

	// Delta Time: �� �����ӿ� �ɸ� �ð�.
	_deltaTime = (float)(_llCurCount.QuadPart - _llPrevCount.QuadPart) / (float)_llFrequency.QuadPart;

	// FPS: Frame Per Second
	_llPrevCount = _llCurCount;
	//	1. / m_dT;
	_frameCount++; // ������ ȣ�� ����
	_accFrameTime += _deltaTime; // �ð� ����
	if (_accFrameTime >= 1.f) // 1��
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
	DebugManager::GetInstance()->SetLog(L" ����");
	return true;
}
