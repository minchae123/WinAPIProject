#include "pch.h"
#include "Level_Scene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "ResMgr.h"
#include "SpawnManager.h"
#include "LevelManager.h"

void Level_Scene::Init()
{
	selectTex = ResourceManager::GetInstance()->TexLoad(L"Select", L"Texture\\Select.bmp");
	backTex = ResourceManager::GetInstance()->TexLoad(L"lBack", L"Texture\\levelBack.bmp");
}

void Level_Scene::Update()
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
	case 0: 
	{
		y = 210;
	}
	break;
	case 1:
	{
		y = 340;
	}
	break;
	case 2: 
	{
		y = 470;
	}
	break;
	default:
		break;
	}

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (num)
		{
		case 0: // 1 레벨
		{
			SceneLoad(L"Start_Scene");
			LevelManager::GetInstance()->Init(2, 150.f, 3);
		}
		break;
		case 1: // 2 레벨
		{
			SceneLoad(L"Start_Scene");
			LevelManager::GetInstance()->Init(4, 200.f, 5);
		}
		break;
		case 2: // 3 레벨
		{
			SceneLoad(L"Start_Scene");
			LevelManager::GetInstance()->Init(6, 250.f, 6);
		}
		break;
		default:
			break;
		}
	}
}

void Level_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	BitBlt(_dc, (int)(0), (int)(-50), 1280, 780, backTex->GetDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, 400, y, 64, 64, selectTex->GetDC(), 0, 0, 64, 64, RGB(255, 255, 255));
}

void Level_Scene::Release()
{
}
