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
	if (KEY_DOWN(KEY_TYPE::H))
	{
		//SpreadPattern(10 , SpawnRandomPos());
		//SquarePattern(SpawnRandomPos());
		//RhombPattern(SpawnRandomPos());
		//TrianglePattern(SpawnRandomPos());
		//HexagonPattern(SpawnRandomPos());
		RandomPattern(10, SpawnRandomPos());
		//SinPattern(SpawnRandomPos());
	}
}

void PatternController::CreateBullet(float angle, Vector2 pos, float speed = 0)
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

void PatternController::RandomPattern(int count, Vector2 pos)
{
	for (int i = 0; i < count; i++)
	{
		float randAngle = rand() % 360;
		CreateBullet(randAngle, pos);
	}
}

void PatternController::SinPattern(Vector2 pos)
{

}