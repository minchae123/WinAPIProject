#include "pch.h"
#include "Enemy.h"
#include "Texture.h"
#include "DebugManager.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"

Enemy::Enemy()
	: _texture(nullptr)
	, _moveSpeed(200.f)
{
	CreateCollider();
}

Enemy::~Enemy()
{
}

void Enemy::Update()
{
	Move();
	int r = rand() % 10000;

	if (r <= 10)
	{
		DebugLog(L"Shoot");
		ShootBullet();
	}
}

void Enemy::Render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	CIRCLE_RENDER(pos.x, pos.y, scale.x, scale.y, dc);
	Component_Render(dc);
}

void Enemy::Move()
{
	Vector2 pos = GetPos();

	if (pos.x <= GetClampMin().x ||
		pos.x >= GetClampMax().x)
	{
		// ªÛ«œ
	}
	if (pos.y <= GetClampMin().y || 
		pos.y >= GetClampMax().y)
	{
		// ¡¬øÏ
	}
}

void Enemy::ShootBullet()
{
	Object* player = SceneManager::GetInstance()->GetCurScene()->GetGroupObject(OBJECT_GROUP::PLAYER)[0];
	Vector2 playerPos = player->GetPos();
	Vector2 pos = GetPos();
	Vector2 dir = Vector2(playerPos.x - pos.x, playerPos.y - pos.y);
	dir = dir.Normalize();
	Vector2 shootPos = Vector2(pos.x + dir.x * 50, pos.y + dir.y * 50);
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(shootPos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"EnemyBullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}
