#pragma once
// ����(static)�Ҵ�.
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
	HDC		_dc; // ���� DC
	HDC		_backDC; // �� ���� DC
	HBITMAP	_backBit; // �� ���ۿ� �׸� ��Ʈ��
	POINT	_resolution; // �ػ�
	HBRUSH  _arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    _arrPen[(UINT)PEN_TYPE::END];
};

