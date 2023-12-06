#include "pch.h"
#include "Intro_Scene.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "Scene.h"
#include "SceneMgr.h"

void Intro_Scene::Init()
{
	tex = ResourceManager::GetInstance()->TexLoad(L"Background", L"Texture\\Title.bmp");
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

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (num)
		{
		case 0: // 게임 시작
		{
			SceneManager::GetInstance()->LoadScene(L"Start_Scene");
		}
			break;
		case 1: // 게임 방법
		{

		}
			break;
		case 2: // 게임 종료
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
	BitBlt(_dc
		, (int)(0)
		, (int)(-50)
		, 1280, 780, tex->GetDC()
		, 0, 0, SRCCOPY);
}

void Intro_Scene::Release()
{
	Scene::Release();
}
