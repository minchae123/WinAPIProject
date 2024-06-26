#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "Monster.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
#include "PlayerController.h"
#include "DebugManager.h"
#include "Wall.h"
#include "Enemy.h"
#include "SpawnManager.h"
#include "InfoManager.h"
#include "ResultManager.h"

void Start_Scene::Init()
{
	back = ResourceManager::GetInstance()->TexLoad(L"BG", L"Texture\\GameBg.bmp");
	background = ResourceManager::GetInstance()->TexLoad(L"Backgroundd", L"Texture\\Background.bmp");

	//Object* wObj = new Wall;
	//AddObject(wObj, OBJECT_GROUP::WALL);

	Object* pObj = new PlayerController;
	pObj->SetPos((Vector2({ Core::GetInstance()
		->GetResolution().x / 2, Core::GetInstance()->GetResolution().y / 2 })));
	pObj->SetScale(Vector2(5.f, 5.f));
	pObj->SetName(L"Player");
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	InfoManager::GetInstance()->Init();
	/*Object* enemyObj = new Enemy;
	enemyObj->SetPos((Vector2(300, 100)));
	enemyObj->SetScale(Vector2(30.f, 30.f));
	AddObject(enemyObj, OBJECT_GROUP::ENEMY);*/

	ResourceManager::GetInstance()->LoadSound(L"BGM", L"Sound\\BackMusic.wav", true);
	//ResourceManager::GetInstance()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResourceManager::GetInstance()->Play(L"BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionManager::GetInstance()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::BULLET);
	CollisionManager::GetInstance()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::ENEMY);
	SpawnManager::GetInstance()->Init();
	ResultManager::GetInstance()->Init();
}

void Start_Scene::Update()
{
	Scene::Update();
	SpawnManager::GetInstance()->Update();
	ResultManager::GetInstance()->Update();
	InfoManager::GetInstance()->Update();
}

void Start_Scene::Render(HDC _dc)
{
	BitBlt(_dc, 0, 0, 1920, 1080, background->GetDC(), 0, 0, SRCCOPY);
	BitBlt(_dc, 100, 100, 1280, 1700, back->GetDC(), 0, 0, SRCCOPY);
	Scene::Render(_dc);
	InfoManager::GetInstance()->Render(_dc);
	//<<DebugManager::GetInstance()->Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionManager::GetInstance()->CheckReset();
}
