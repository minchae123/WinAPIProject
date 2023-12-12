#include "pch.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DebugManager.h"
#include "Object.h"
#include "TimeMgr.h"

void SpawnManager::Init()
{
	_time = 0;
	_spawnTime = 10;
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

void SpawnManager::Spawn() // 직사각형 abdc라고 할때
{
	Vector2 spawnPos = SpawnPos();
	Object* enemyObj = new Enemy;
	enemyObj->SetPos(spawnPos);
	enemyObj->SetScale(Vector2(100.f, 100.f));
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
	case 0:		// 0~1 위의 생성
	{
		rx = rand() % (int)(clampMax.x - clampMin.x) + clampMin.x;
		ry = clampMin.y;
	}
	break;
	case 1:		// 1~2 위의 생성
	{
		rx = clampMax.x;
		ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;
	}
	break;
	case 2:		// 2~3 위의 생성
	{
		rx = rand() % (int)(clampMin.x - clampMax.x) + clampMin.x;
		ry = clampMin.y;
	}
	break;
	case 3:		// 3~4 위의 생성
	{
		rx = clampMin.x;
		ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;
	}
	break;
	default:	// 뭔가 이상하긴한데 이건 
		DebugLog(L"ㅋㅋㅋㅋㅋㅋ 버그다");
		break;
	}

	return Vector2(rx, ry);
}
