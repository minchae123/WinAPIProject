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

void Start_Scene::Init()
{
	Object* wObj = new Wall;
	AddObject(wObj, OBJECT_GROUP::WALL);

	Object* pObj = new PlayerController;
	pObj->SetPos((Vector2({Core::GetInstance()->GetResolution().x /2, Core::GetInstance()->GetResolution().y / 2})));
	pObj->SetScale(Vector2(100.f,100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	
	Object* enemyObj = new Enemy;
	enemyObj->SetPos((Vector2(300, 100)));
	enemyObj->SetScale(Vector2(30.f, 30.f));
	AddObject(enemyObj, OBJECT_GROUP::ENEMY);

	/*ResourceManager::GetInstance()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResourceManager::GetInstance()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResourceManager::GetInstance()->Play(L"BGM");*/

	// 충돌체크해야되는것들을 설정하자.
	CollisionManager::GetInstance()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::BULLET);
	CollisionManager::GetInstance()->CheckGroup(OBJECT_GROUP::ENEMY, OBJECT_GROUP::BULLET);
}

void Start_Scene::Update()
{
	Scene::Update();
}

void Start_Scene::Render(HDC _dc)
{	
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionManager::GetInstance()->CheckReset();
}
