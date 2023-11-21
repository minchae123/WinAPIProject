#pragma once
class PathMgr
{
	SINGLE(PathMgr);
public:
	void Init();
	const wchar_t* GetResPath() const 
	{ return _strResPath; }
private:
	wchar_t _strResPath[255];
};

