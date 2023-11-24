#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
bool Core::Init(HWND hWnd, POINT ptResolution)
{
	// === 변수 초기화 === 
	_hWnd = hWnd;
	_resolution = ptResolution;
	_backDC = 0;
	_backBit = 0;


	// 더블버퍼링
	_dc = GetDC(_hWnd);	
	// 1. 생성
	_backBit = CreateCompatibleBitmap(_dc, _resolution.x, _resolution.y);
	_backDC = CreateCompatibleDC(_dc);

	// 2. 연결
	SelectObject(_backDC, _backBit);

//	m_obj.SetPos(Vec2({ m_ptResolution.x / 2, m_ptResolution.y / 2 }));
////	m_obj.m_ptPos = ;
//	m_obj.SetScale(Vec2(150, 150));

	CreateGDI();
	// ==== Manager Init ====
	PathManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();

	return true;
}

void Core::GameLoop()
{
	/*static int count = 0;
	++count;
	static int prev = GetTickCount64();
	int cur = GetTickCount64();
	if (cur - prev > 1000)
	{
		prev = cur;
		count = 0;
	}*/
	Update();
	Render();
	// 깃 테스트
}


void Core::Update()
{

	// === Manager Update === 
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();
//	Vec2 vPos = m_obj.GetPos();
//
////	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
////	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)
//	if(KEY_UP(KEY_TYPE::LEFT))
//	{
////		m_obj.m_ptPos.x -= 1;
//		vPos.x -= 100.f;// *fDT;
//	}
//
////	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
//	if(KEY_DOWN(KEY_TYPE::RIGHT))
//	{
////		m_obj.m_ptPos.x += 1;
//		vPos.x += 100.f * fDT;
//	}
//	m_obj.SetPos(vPos);
}

void Core::Render()
{
	// 칠한다.
	//Rectangle(m_hbackDC, -1,-1,m_ptResolution.x +1,m_ptResolution.y + 1);
	PatBlt(_backDC, 0, 0, _resolution.x, _resolution.y, WHITENESS);

	SceneManager::GetInstance()->Render(_backDC);
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();
	RECT_RENDER(vPos.x, vPos.y, vScale.x, vScale.y, m_hbackDC);*/

	//// cursor test
	//POINT mousepos = KeyMgr::GetInst()->GetMousePos();
	//static wchar_t mousebuf[100] = {};
	//swprintf_s(mousebuf, L"Mouse: x %d, y: %d", mousepos.x, mousepos.y);
	//TextOut(m_hbackDC, 10, 10, mousebuf, wcslen(mousebuf));

	// 3. 옮긴다.
	BitBlt(_dc, 0,0, _resolution.x, _resolution.y, 
		_backDC, 0,0, SRCCOPY);
	EventManager::GetInstance()->Update();


	//TransparentBlt();
	//StretchBlt();
	// 
	//RECT_RENDER(m_obj.m_ptPos.x, m_obj.m_ptPos.y, m_obj.m_ptScale.x, m_obj.m_ptScale.y, m_hDC);
	//Rectangle(m_hDC
	//	, m_obj.m_ptPos.x - ERROR_CANT_CROSS_RM_BOUNDARY,50,150,150);
}

void Core::CreateGDI()
{
	// HOLLOW
	_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	_arrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	_arrBrush[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	_arrPen[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

void Core::Release()
{
	ReleaseDC(_hWnd, _dc);
	DeleteDC(_backDC); // createdc 한거 지우는거
	DeleteObject(_backBit); // createbit 한거 지우는거
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(_arrPen[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(_arrBrush[i]);
	}

	ResourceManager::GetInstance()->Release();
}
