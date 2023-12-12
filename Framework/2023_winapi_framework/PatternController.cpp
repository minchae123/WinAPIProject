#include "pch.h"
#include "PatternController.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Bullet.h"
#include "KeyMgr.h"
#include "DebugManager.h"

void PatternController::Init()
{
}

void PatternController::Update()
{
	if (KEY_DOWN(KEY_TYPE::H))
	{
		//SpreadPattern(10);
		SquarePattern(SpanwRandomPos());
	}
}

void PatternController::CreateBullet(float angle, Vector2 pos)
{
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	//newBullet->SetDir(angle);
	newBullet->SetDir({1,2});
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

Vector2 PatternController::SpanwRandomPos()
{
	Vector2 clampMax = GetClampMax();
	Vector2 clampMin = GetClampMin();

	int rx = rand() % (int)(clampMax.x - clampMin.x) + clampMin.x;
	int ry = rand() % (int)(clampMax.y - clampMin.y) + clampMin.y;

	return { rx, ry };
}

void PatternController::HeartPattern()
{

}

void PatternController::SpreadPattern(int count) // 동그랗게 퍼지는 패턴
{
	for (int i = 0; i < count; i++)
	{
		float angle = (360 / count) * i;
		float rad = Deg2Rad(angle);
		CreateBullet(rad, { 500, 500 });
	}
}

void PatternController::SquarePattern(Vector2 pos) // 네방향으로 퍼지는 패턴
{
	CreateBullet({ 1,0 }, pos);
	CreateBullet({ -1,0 }, pos);
	CreateBullet({ 0,1 }, pos);
	CreateBullet({ 0,-1 }, pos);
}
