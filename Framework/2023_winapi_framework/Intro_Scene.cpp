#include "pch.h"
#include "Intro_Scene.h"
#include "ResMgr.h"


void Intro_Scene::Init()
{
	tex = ResourceManager::GetInstance()->TexLoad(L"Background", L"Texture\\Title.bmp");
}

void Intro_Scene::Update()
{
	Scene::Update();
}

void Intro_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	BitBlt(_dc
		, (int)(0)
		, (int)(0)
		, 1280, 720, tex->GetDC()
		, 0, 0, SRCCOPY);
}

void Intro_Scene::Release()
{
	Scene::Release();
}
