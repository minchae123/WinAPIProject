#pragma once
class PathManager
{
	SINGLE(PathManager);
public:
	void Init();
	const wchar_t* GetResPath() const 
	{ return _strResPath; }
private:
	wchar_t _strResPath[255];
};

