#include "pch.h"
#include "Health.h"
#include "EventMgr.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DebugManager.h"
#include "ResultManager.h"

Health::Health()
	: _hp(0)
	, _ownerObject(nullptr)
{
}

Health::~Health()
{
}

void Health::Update()
{
	if (_hp <= 0)
	{
		if (_ownerObject->GetName() == L"Player")
		{
			ResultManager::GetInstance()->StopTime();
			SceneManager::GetInstance()->LoadScene(L"GameEnd_Scene");
			//DebugLog(L"Player Á×À½");
		}
		else
		{
			EventManager::GetInstance()->DeleteObject(_ownerObject);
		}
	}
}

void Health::Render(HDC dc)
{

}

void Health::Damage(int damage)
{
	_hp -= damage;
}
