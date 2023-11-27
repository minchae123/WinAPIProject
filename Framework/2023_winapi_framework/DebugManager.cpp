#include "pch.h"
#include "DebugManager.h"

void DebugManager::Render(HDC dc)
{
	RECT_RENDER(1100, 300, 300, 400, dc);
	TextOut(dc, 1000, 100, _debugText.c_str(), _debugText.length());
	for (auto iter : _mapLog)
	{
		TextOut(dc, 1000, iter.second, iter.first.c_str(), iter.first.length());
	}
}

void DebugManager::SetLog(wstring log)
{
	_mapLog.insert(_mapLog.end(), { log, 130 + cnt++ * 15 });
}
