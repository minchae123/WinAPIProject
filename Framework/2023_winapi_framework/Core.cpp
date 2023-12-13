#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include "PatternMgr.h"
#include "PatternController.h"
#include "ResultManager.h"

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

	CreateGDI();
	// ==== Manager Init ====
	PathManager::GetInstance()->Init();
	TimeManager::GetInstance()->Init();
	KeyManager::GetInstance()->Init();
	ResourceManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	PatternMgr::GetInstance()->Init();
	PatternController::GetInstance()->Init();
	ResultManager::GetInstance()->Init();

	return true;
}

void Core::GameLoop()
{
	Update();
	Render();
}


void Core::Update()
{
	// === Manager Update === 
	TimeManager::GetInstance()->Update();
	KeyManager::GetInstance()->Update();
	SceneManager::GetInstance()->Update();
	CollisionManager::GetInstance()->Update();
	PatternMgr::GetInstance()->Update();
	PatternController::GetInstance()->Update();
	ResultManager::GetInstance()->Update();
}

void Core::Render()
{
	// 칠한다.
	PatBlt(_backDC, 0, 0, _resolution.x, _resolution.y, WHITENESS);

	SceneManager::GetInstance()->Render(_backDC);

	// 3. 옮긴다.
	BitBlt(_dc, 0,0, _resolution.x, _resolution.y, 
		_backDC, 0,0, SRCCOPY);
	EventManager::GetInstance()->Update();
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
