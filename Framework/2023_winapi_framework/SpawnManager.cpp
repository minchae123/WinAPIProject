#include "pch.h"
#include "SpawnManager.h"
#include "Enemy.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "DebugManager.h"
#include "Object.h"

void SpawnManager::Update()
{
}

void SpawnManager::Spawn() // 직사각형 abdc라고 할때
{
	Vector2 spawnPos = SpawnPos();
	Object* enemyObj = new Enemy;
	enemyObj->SetPos(spawnPos);
	enemyObj->SetScale(Vector2(30.f, 30.f));
	SceneManager::GetInstance()->GetCurScene()->AddObject(enemyObj, OBJECT_GROUP::ENEMY);
}

Vector2 SpawnManager::SpawnPos()
{
	int r = rand() % 4;
	POINT point[4] = {};
	Object* newObj = new Object;
	Vector2 clampMin = newObj->GetClampMin();
	Vector2 clampMax = newObj->GetClampMax();
	point[0] = {(long)clampMin.x, (long)clampMin.y};
	point[1] = {(long)clampMin.x, (long)clampMin.y};
	point[2] = {(long)clampMin.x, (long)clampMin.y};
	point[3] = {(long)clampMin.x, (long)clampMin.y};
	switch (r)
	{
	case 0:		// ab 위의 생성
	{

	}
	break;
	case 1:		// bd 위의 생성
	{

	}
	break;
	case 2:		// dc 위의 생성
	{

	}
	break;
	case 3:		// ca 위의 생성
	{

	}
	break;
	default:	// 뭔가 이상하긴한데 이건 
		DebugLog(L"ㅋㅋㅋㅋㅋㅋ 버그다");
		break;
	}

	return Vector2();
}
