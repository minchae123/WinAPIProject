#include "pch.h"
#include "Explain_Scene.h"
#include "ResMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
void Explain_Scene::Init()
{
	backTex = ResourceManager::GetInstance()->TexLoad(L"Explain", L"Texture\\ExTexture.bmp");
}

void Explain_Scene::Update()
{
	if (KEY_DOWN(KEY_TYPE::ESC))
	{
		SceneManager::GetInstance()->LoadScene(L"Intro_Scene");
	}
}

void Explain_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	int Width = backTex->GetWidth();
	int Height = backTex->GetHeight() - 20;
	BitBlt(_dc, 0, -50, Width, Height, backTex->GetDC(), 0, 0, SRCCOPY);
}

void Explain_Scene::Release()
{
}
