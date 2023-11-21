#include "pch.h"
#include "KeyMgr.h"
#include "Core.h"

void KeyManager::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		_vecKey.push_back(KeyInfo{KEY_STATE::NONE, false});
	}
	_ptMouse = {};
}

void KeyManager::Update()
{
	HWND hWnd = GetFocus();
//	HWND hMainHwnd = Core::GetInst()->GetHwnd();
	if (hWnd != nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			// 키가 눌렸다.
			if (GetAsyncKeyState(_arrKey[i]))
			{
				// 이전에 눌렸어
				if (_vecKey[i].IsPrevCheck)
				{
					_vecKey[i].eState = KEY_STATE::PRESS;
				}
				else // 이전에 안눌렸어. 지금 딱!!! 누름
				{
					_vecKey[i].eState = KEY_STATE::DOWN;
				}
				_vecKey[i].IsPrevCheck = true;
			}
			// 키가 안눌렸다.
			else
			{
				// 이전에 눌려있었다.
				if (_vecKey[i].IsPrevCheck)
				{
					_vecKey[i].eState = KEY_STATE::UP;
				}
				else
				{
					_vecKey[i].eState = KEY_STATE::NONE;
				}
				_vecKey[i].IsPrevCheck = false;
			}
		}
		// Mouse
		GetCursorPos(&_ptMouse); // 마우스 커서 좌표 받기
		// 우리가 가진 윈도우 창 기준으로 좌표 변경
		ScreenToClient(Core::GetInstance()->GetHwnd(), &_ptMouse);
	}

	// 포커싱 해제 alt + tap
	else
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			_vecKey[i].IsPrevCheck = false;
			if (_vecKey[i].eState == KEY_STATE::PRESS ||
				_vecKey[i].eState == KEY_STATE::DOWN)
				_vecKey[i].eState = KEY_STATE::UP;

			if (_vecKey[i].eState == KEY_STATE::UP)
				_vecKey[i].eState = KEY_STATE::NONE;
		}
	}
	

}
