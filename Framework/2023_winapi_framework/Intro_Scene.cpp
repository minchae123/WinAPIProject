#include "pch.h"
#include "Intro_Scene.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "Scene.h"
#include "SceneMgr.h"

void Intro_Scene::Init()
{
	backTex = ResourceManager::GetInstance()->TexLoad(L"Background", L"Texture\\Title.bmp");
	selectTex = ResourceManager::GetInstance()->TexLoad(L"Select", L"Texture\\Select.bmp");
}

void Intro_Scene::Update()
{
	Scene::Update();

	if (KEY_DOWN(KEY_TYPE::UP))
	{
		num--;
	}
	if (KEY_DOWN(KEY_TYPE::DOWN))
	{
		num++;
	}

	num = std::clamp(num, 0, 2);

	switch (num)
	{
	case 0: // ���� ����
	{
		y = 395;
	}
	break;
	case 1: // ���� ���
	{
		y = 485;
	}
	break;
	case 2: // ���� ����
	{
		y = 570;
	}
	break;
	default:
		break;
	}

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (num)
		{
		case 0: // ���� ����
		{
			SceneManager::GetInstance()->LoadScene(L"Start_Scene");
			//SceneLoad(L"Menu_Scene");
		}
			break;
		case 1: // ���� ���
		{
		}
			break;
		case 2: // ���� ����
		{
			PostQuitMessage(0); 
		}
			break;
		default:
			break;
		}
	}
}

void Intro_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	BitBlt(_dc, (int)(0), (int)(-50), 1280, 780, backTex->GetDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, 400, y, 64, 64, selectTex->GetDC(), 0, 0, 64, 64, RGB(255, 255, 255));
}

void Intro_Scene::Release()
{
	Scene::Release();
}