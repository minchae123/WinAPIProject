#include "pch.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DebugManager.h"
#include "Object.h"
#include "TimeMgr.h"
#include "LevelManager.h"

void SpawnManager::Init()
{
	_time = 0;
	_spawnTime = 6;
	Spawn();
}

void SpawnManager::Update()
{
	_time += TimeManager::GetInstance()->GetDeltaTime();

	if (_time >= _spawnTime)
	{
		Spawn();
		_time = 0;
	}
}

void SpawnManager::Spawn()
{
	Vector2 spawnPos = SpawnPos();
	Object* enemyObj = new Enemy(LevelManager::GetInstance()->GetEnemyHP());
	enemyObj->SetPos(spawnPos);
	enemyObj->SetScale(Vector2(3.f, 3.f));
	SceneManager::GetInstance()->GetCurScene()->AddObject(enemyObj, OBJECT_GROUP::ENEMY);
}

Vector2 SpawnManager::SpawnPos()
{
	int r = rand() % 4;
	Object* newObj = new Object;
	Vector2 clampMin = newObj->GetClampMin();
	Vector2 clampMax = newObj->GetClampMax();
	DebugLog(Text(clampMin.y) + L" " + Text(clampMax.y));
	int rx = 0;
	int ry = 0;
	switch (r)
	{
	case 0:		// 0~1 是税 持失
	{
		rx = rand() % (int)(clampMax.x - clampMin.x) + clampMin.x;
		ry = clampMin.y;
	}
	break;
	case 1:		// 1~2 是税 持失
	{
		rx = clampMax.x;
		ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;
	}
	break;
	case 2:		// 2~3 是税 持失
	{
		rx = rand() % (int)(clampMin.x - clampMax.x) + clampMin.x;
		ry = clampMin.y;
	}
	break;
	case 3:		// 3~4 是税 持失
	{
		rx = clampMin.x;
		ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;
	}
	break;
	default:	// 杭亜 戚雌馬延廃汽 戚闇 
		DebugLog(L"せせせせせせ 獄益陥");
		break;
	}

	return Vector2(rx, ry);
}
