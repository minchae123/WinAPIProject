#include "pch.h"
#include "PatternMgr.h"
#include "define.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "TimeMgr.h"
#include "DebugManager.h"
#include "KeyMgr.h"

void PatternMgr::Init()
{
	//HeartPattern();
	//SpreadPattern(10);
	//SquarePattern();
}

void PatternMgr::Update()
{
	if (KEY_DOWN(KEY_TYPE::H))
	{
		//SquarePattern();
	}
}

void PatternMgr::CreateBullet(float angle, Vector2 pos)
{
	Vector2 shootPos = pos;
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(angle);
	newBullet->SetName(L"Enemy_Bullet");
	newBullet->SetObj(nullptr);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}

void PatternMgr::CreateBullet(Vector2 dir, Vector2 pos)
{
	Vector2 shootPos = pos;
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"Enemy_Bullet");
	newBullet->SetObj(nullptr);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}


void PatternMgr::HeartPattern()
{
	CreateBullet({ 0,2 }, { 500,500 });
}

void PatternMgr::SpreadPattern(int count)
{
	for (int i = 0; i < count; i++)
	{
		float angle = (360 / count) * i;
		float rad = Deg2Rad(angle);
		CreateBullet(rad, { 500, 500 });
	}
}

void PatternMgr::SquarePattern(Vector2 pos)
{
	DebugLog(L"Square");

	CreateBullet({ 1,0 }, pos);
	CreateBullet({ -1,0 }, pos);
	CreateBullet({ 0,1 }, pos);
	CreateBullet({ 0,-1 }, pos);
}