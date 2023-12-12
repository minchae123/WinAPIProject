#include "pch.h"
#include "GameEnd_Scene.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ResMgr.h"

void GameEnd_Scene::Init()
{
	backTex = ResourceManager::GetInstance()->TexLoad(L"Background", L"Texture\\EndBack.bmp");
	selectTex = ResourceManager::GetInstance()->TexLoad(L"Select", L"Texture\\Select.bmp");
}

void GameEnd_Scene::Update()
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

	num = std::clamp(num, 0, 1);

	switch (num)
	{
	case 0: // 게임 다시 시작
	{
		y = 395;
	}
	break;
	case 1: // 게임 종료
	{
		y = 485;
	}
	break;
	default:
		break;
	}

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (num)
		{
		case 0: // 게임 다시 시작
		{
			SceneManager::GetInstance()->LoadScene(L"Start_Scene");
		}
		break;
		case 1: // 게임 종료
		{
			PostQuitMessage(0);
		}
		break;
		default:
			break;
		}
	}
}

void GameEnd_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	BitBlt(_dc, (int)(0), (int)(-50), 1280, 780, backTex->GetDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, 400, y, 64, 64, selectTex->GetDC(), 0, 0, 64, 64, RGB(255, 255, 255));
}

void GameEnd_Scene::Release()
{

}
