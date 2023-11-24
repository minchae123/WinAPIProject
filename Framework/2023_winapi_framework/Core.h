#pragma once
// 정적(static)할당.
#include "define.h"
#include "Object.h"
class Core
{
	SINGLE(Core);
public:
	bool Init(HWND hwnd, POINT ptResolution);
	void GameLoop();
	void Release();
public:
	const HWND& GetHwnd() const { return _hWnd; }
	const POINT& GetResolution() const 
	{ return _resolution; }
	const HDC& GetMainDC() const
	{
		return _dc;
	}
	const HBRUSH& GetBrush(BRUSH_TYPE eType)
	{
		return _arrBrush[(UINT)eType];
	}
	const HPEN& GetPen(PEN_TYPE eType)
	{
		return _arrPen[(UINT)eType];
	}
private:
	void Update();
	void Render();
	void CreateGDI();
private:
	HWND	_hWnd;
	HDC		_dc; // 메인 DC
	HDC		_backDC; // 백 버퍼 DC
	HBITMAP	_backBit; // 백 버퍼에 그릴 비트맵
	POINT	_resolution; // 해상도
	HBRUSH  _arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    _arrPen[(UINT)PEN_TYPE::END];
};

