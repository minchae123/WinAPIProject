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

void SpawnManager::Spawn() // ���簢�� abdc��� �Ҷ�
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
	case 0:		// ab ���� ����
	{

	}
	break;
	case 1:		// bd ���� ����
	{

	}
	break;
	case 2:		// dc ���� ����
	{

	}
	break;
	case 3:		// ca ���� ����
	{

	}
	break;
	default:	// ���� �̻��ϱ��ѵ� �̰� 
		DebugLog(L"������������ ���״�");
		break;
	}

	return Vector2();
}
