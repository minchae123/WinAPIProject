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
}

void PatternMgr::Update()
{
	if (KEY_DOWN(KEY_TYPE::LEFT))
		HeartPattern();
}

void PatternMgr::CreateBullet(float angle, Vector2 pos)
{
	Bullet* pBullet = new Bullet;
	Vector2 vBulletPos = pos;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vector2(25.f, 25.f));
	pBullet->SetDir(angle);
	pBullet->SetName(L"Enemy_Bullet");
	SceneManager::GetInstance()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void PatternMgr::CreateBullet(Vector2 dir, Vector2 pos)
{
	Bullet* pBullet = new Bullet;
	Vector2 vBulletPos = pos;
	pBullet->SetPos(vBulletPos);
	pBullet->SetScale(Vector2(25.f, 25.f));
	pBullet->SetDir(dir);
	pBullet->SetName(L"Enemy_Bullet");
	SceneManager::GetInstance()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}

void PatternMgr::HeartPattern()
{
	CreateBullet({ 0,2 }, { 500,500 });		
	//CreateBullet({ 2,3 }, { 500,500 });
	//CreateBullet({ -2,3 }, { 500,500 });
	//CreateBullet({ 4,2 }, { 500,500 });
	//CreateBullet({ -4,2 }, { 500,500 });
	//CreateBullet({ 4,0 }, { 500,500 });
	//CreateBullet({ -4,0 }, { 500,500 });
	//CreateBullet({ 2,-2 }, { 500,500 });
	//CreateBullet({ -2,-2 }, { 500,500 });
	//CreateBullet({ 0,-4 }, { 500,500 });
	// 각 점마다 스피드 설정 필요함
}

void PatternMgr::SpreadPattern(int count)
{
	for (int i = 0; i < count; i++)
	{
		float angle = (360 / count) * i;
		float rad = Deg2Rad(angle);
		CreateBullet(rad, { 500, 500 });
		int a = 0;
	}
}
