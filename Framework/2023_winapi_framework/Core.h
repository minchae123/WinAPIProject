#pragma once
// 하나만, 어디서든 쓸수있어야함.
// 싱글톤을 구현하는 방법이 엄청 많음
// 1학기때 했던걸 다이나믹 싱글톤 = 동적할당
// 장점: 존재하지 않더라도 다시 생성할 수 있다.
// 단점: 동적으로 할당하기에 제거를 해줘야한다.
//private:
//	static Core* m_pInst;
//public:
//	static Core* GetInst()
//	{
//		if (m_pInst == nullptr)
//			m_pInst = new Core;
//		return m_pInst;
//	}
//public:
//	static void DestroyInst()
//	{
//		SAFE_DELETE(m_pInst);

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

