#include "pch.h"
#include "Level_Scene.h"
#include "KeyMgr.h"
#include "SceneMgr.h"

Level_Scene::Level_Scene()
{
}

Level_Scene::~Level_Scene()
{
}

void Level_Scene::Init()
{
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
		case 0: // 1 ����
		{
		}
		break;
		case 1: // 2 ����
		{
		}
		break;
		case 2: // 3 ����
		{
		}
		break;
		default:
			break;
		}
	}
}

void Level_Scene::Render(HDC _dc)
{
}

void Level_Scene::Release()
{
}
