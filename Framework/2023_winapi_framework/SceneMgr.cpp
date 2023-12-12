#include "pch.h"
#include "SceneMgr.h"
#include "Start_Scene.h"
#include "Game_Scene.h"
#include "Intro_Scene.h"
#include "GameEnd_Scene.h"
#include "DebugManager.h"

void SceneManager::Init()
{
	_pCurScene = nullptr;
	// ¾À µî·Ï
	RegisterScene(L"Start_Scene",std::make_shared<Start_Scene>());
	RegisterScene(L"Game_Scene", std::make_shared<Game_Scene>());
	RegisterScene(L"Intro_Scene", std::make_shared<Intro_Scene>());
	RegisterScene(L"GameEnd_Scene", std::make_shared<GameEnd_Scene>());
	
	// Ã¹ ¾À ÁöÁ¤
	LoadScene(L"Intro_Scene");
}

void SceneManager::Update()
{
	_pCurScene->Update();
	_pCurScene->FinalUpdate();
}

void SceneManager::Render(HDC dc)
{
	_pCurScene->Render(dc);
}

void SceneManager::LoadScene(const wstring& scenename)
{
	// ¾ÀÀÌ ÀÖÀ¸¸é
	if (_pCurScene != nullptr)
	{
		_pCurScene->Release();
		_pCurScene = nullptr;
	}

	auto iter = _mapScene.find(scenename);
	if (iter != _mapScene.end())
	{
		_pCurScene = iter->second;
		_pCurScene->Init();
	}
}

void SceneManager::RegisterScene(const wstring& scenename, std::shared_ptr<Scene> scene)
{
	_mapScene.insert(_mapScene.end(), {scenename, scene});
}
