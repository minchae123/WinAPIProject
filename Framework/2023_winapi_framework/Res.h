#pragma once
class Res
{
public:
	Res();
	~Res();
public:
	void SetKey(const wstring& key) 
	{	_key = key;	}
	void SetRelativePath(const wstring& path)
	{
		_relativePath = path;
	}
	const wstring& GetKey() const { return _key; }
	const wstring& GetRelativePath() const { return _relativePath; }

private:
	wstring _key; // 키
	wstring _relativePath; // 상대경로
};

