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
			// Ű�� ���ȴ�.
			if (GetAsyncKeyState(_arrKey[i]))
			{
				// ������ ���Ⱦ�
				if (_vecKey[i].IsPrevCheck)
				{
					_vecKey[i].eState = KEY_STATE::PRESS;
				}
				else // ������ �ȴ��Ⱦ�. ���� ��!!! ����
				{
					_vecKey[i].eState = KEY_STATE::DOWN;
				}
				_vecKey[i].IsPrevCheck = true;
			}
			// Ű�� �ȴ��ȴ�.
			else
			{
				// ������ �����־���.
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
		GetCursorPos(&_ptMouse); // ���콺 Ŀ�� ��ǥ �ޱ�
		// �츮�� ���� ������ â �������� ��ǥ ����
		ScreenToClient(Core::GetInstance()->GetHwnd(), &_ptMouse);
	}

	// ��Ŀ�� ���� alt + tap
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
