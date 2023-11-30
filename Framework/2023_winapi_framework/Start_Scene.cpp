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
	pObj->SetScale(Vector2(30.f,30.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);
	
	Object* enemyObj = new Enemy;
	enemyObj->SetPos((Vector2(100, 100)));
	enemyObj->SetScale(Vector2(30.f, 30.f));
	AddObject(enemyObj, OBJECT_GROUP::ENEMY);

	//Vector2 vResolution = Core::GetInstance()->GetResolution();
	//Monster* pMonster = nullptr;
	//int iMonster = 10;		// 몬스터 수 
	//float fMoveDist = 30.f; // 움직일 거리
	//float fMonsterScale = 50.f; // 몬스터 크기
	//// 해상도x - ( 움직일 거리 + 오브젝트 크기 /2) * 2 / 몬스터수 -1 
	//float fTerm = (vResolution.x - (fMoveDist + fMonsterScale / 2.f) * 2) 
	//				/ (float)(iMonster -1);
	//for (int i = 0; i < iMonster; ++i)
	//{
	//	pMonster = new Monster;
	//	pMonster->SetPos(Vector2(
	//		(fMoveDist + fMonsterScale / 2.f) + i* fTerm
	//		,300.f));
	//	pMonster->SetScale(Vector2(fMonsterScale, fMonsterScale));
	//	pMonster->SetCenterPos(pMonster->GetPos());
	//	pMonster->SetMoveDis(fMoveDist);
	//	AddObject(pMonster, OBJECT_GROUP::MONSTER);
	//}
	// 사운드 세팅

	ResourceManager::GetInstance()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResourceManager::GetInstance()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResourceManager::GetInstance()->Play(L"BGM");

	// 충돌체크해야되는것들을 설정하자.
	CollisionManager::GetInstance()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
}

void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// 씬 변경
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
