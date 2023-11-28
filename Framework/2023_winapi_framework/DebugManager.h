#pragma once
class DebugManager
{
	SINGLE(DebugManager);
public:
	void Render(HDC dc);
public:
	void SetLog(wstring log);
private:
	map<wstring, int> _mapLog;
	wstring _debugText = L"����� â";
	int cnt = 0;
};

