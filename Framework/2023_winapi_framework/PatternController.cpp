#include "pch.h"
#include "PatternController.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Bullet.h"
#include "KeyMgr.h"

void PatternController::Init()
{
}

void PatternController::Update()
{
	if (KEY_DOWN(KEY_TYPE::H))
	{
		SpreadPattern(10);
	}
}

void PatternController::CreateBullet(float angle, Vector2 pos)
{
	//Vector2 mousePos = KeyManager::GetInstance()->GetMousePos();
	//Vector2 pos = GetPos();
	//Vector2 dir = Vector2(mousePos.x - pos.x, mousePos.y - pos.y);
	//Vector2 shootPos = Vector2(pos.x + dir.x * 3, pos.y + dir.y * 3);
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
}

void PatternController::HeartPattern()
{
}

void PatternController::SpreadPattern(int count)
{
	for (int i = 0; i < count; i++)
	{
		float angle = (360 / count) * i;
		float rad = Deg2Rad(angle);
		CreateBullet(rad, { 500, 500 });
	}
}

void PatternController::SquarePattern()
{
}
