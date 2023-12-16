#include "pch.h"
#include "PatternController.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Bullet.h"
#include "KeyMgr.h"
#include "DebugManager.h"
#include "TimeMgr.h"
#include <cstdio>
#include <ctime>

void PatternController::Init()
{
}


void PatternController::Update()
{
	time += DeltaTime;
	
	if (time >= 5.f)
	{
		time = 0;
		RandomSelectPattern();
	}
}

void PatternController::CreateBullet(Vector2 dir, Vector2 pos, float speed)
{
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetSpeed(speed);
	newBullet->SetName(L"EnemyBullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}

void PatternController::CreateBullet(float angle, Vector2 pos)
{
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(angle);
	newBullet->SetName(L"EnemyBullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}

void PatternController::CreateBullet(Vector2 dir, Vector2 pos)
{
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"EnemyBullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}

Vector2 PatternController::SpawnRandomPos()
{
	Vector2 clampMax = GetClampMax();
	Vector2 clampMin = GetClampMin();

	int rx = rand() % (int)(clampMax.x - clampMin.x) + clampMin.x;
	int ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;

	return { rx, ry };
}

void PatternController::SpreadPattern(int count, Vector2 pos) // 동그랗게 퍼지기
{
	for (int i = 0; i < count; i++)
	{
		float angle = (360 / count) * i;
		float rad = Deg2Rad(angle);
		CreateBullet(rad, pos);
	}
}

void PatternController::SquarePattern(Vector2 pos) // 상하좌우 퍼지는 패턴
{
	CreateBullet({ 1,0 }, pos);
	CreateBullet({ -1,0 }, pos);
	CreateBullet({ 0,1 }, pos);
	CreateBullet({ 0,-1 }, pos);
}

void PatternController::RhombPattern(Vector2 pos) // 사각형 
{
	CreateBullet({ 1,1 }, pos);
	CreateBullet({ -1,1 }, pos);
	CreateBullet({ -1,-1 }, pos);
	CreateBullet({ 1,-1 }, pos);
}

void PatternController::TrianglePattern(Vector2 pos) // 삼각형 
{
	SpreadPattern(3, pos);
}

void PatternController::HexagonPattern(Vector2 pos) // 육각형 
{
	SpreadPattern(6, pos);
}

void PatternController::RandomPattern(int count, Vector2 pos) // 랜덤으로 마구마구
{
	for (int i = 0; i < count; i++)
	{
		float randAngle = rand() % 360;
		CreateBullet(randAngle, pos);
	}
}

void PatternController::HeartPattern(Vector2 pos) // 하트 모양
{
	CreateBullet({ 0,-2 }, pos, 300);
	CreateBullet({ -2,-3 }, pos, 450);
	CreateBullet({ 2,-3 }, pos, 450);
	CreateBullet({ -4,-2 }, pos, 500);
	CreateBullet({ 4,-2 }, pos, 500);
	CreateBullet({ -4,0 }, pos, 550);
	CreateBullet({ 4,0 }, pos, 550);
	CreateBullet({ -2,2 }, pos, 450);
	CreateBullet({ 2,2 }, pos, 450);
	CreateBullet({ 0,4 }, pos, 500);
}

void PatternController::RandomSelectPattern()
{
	int r = rand() % 7;
	switch (r)
	{
	case 0:
	{
		SpreadPattern(10, SpawnRandomPos());
	}
		break;
	case 1:
	{
		SquarePattern(SpawnRandomPos());
	}
		break;
	case 2:
	{
		RhombPattern(SpawnRandomPos());
	}
		break;
	case 3:
	{
		TrianglePattern(SpawnRandomPos());
	}
		break;
	case 4:
	{
		HexagonPattern(SpawnRandomPos());
	}
		break;
	case 5:
	{
		RandomPattern(5, SpawnRandomPos());
	}
		break;
	case 6:
	{
		HeartPattern(SpawnRandomPos());
	}
		break;
	default:
		break;
	}
}
