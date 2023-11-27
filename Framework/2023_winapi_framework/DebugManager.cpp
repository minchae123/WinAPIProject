#include "pch.h"
#include "DebugManager.h"

void DebugManager::Render(HDC dc)
{
	RECT_RENDER(300, 600, 500, 200, dc);
	TextOut(dc, 80, 495, _debugText.c_str(), _debugText.length());
	for (auto iter : _mapLog)
	{
		TextOut(dc, 80, iter.second, iter.first.c_str(), iter.first.length());
	}
}

void DebugManager::SetLog(wstring log)
{
	_mapLog.insert(_mapLog.end(), { log, 530 + cnt * 30 });
	cnt++;
}
