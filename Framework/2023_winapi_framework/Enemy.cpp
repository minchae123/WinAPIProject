#include "pch.h"
#include "Enemy.h"
#include "Texture.h"
#include "DebugManager.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "Timer.h"
#include "TimeMgr.h"
#include "Health.h"
#include "ResMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"

Enemy::Enemy()
	: _texture(nullptr)
	, _moveSpeed(200.f)
	, _time(0)
	, _spawnTime(2.f)
{
	_texture = ResourceManager::GetInstance()->TexLoad(L"Enemy", L"Texture\\Bat.bmp");
	CreateCollider();
	GetCollider()->SetScale({ 100, 70 });
	GetCollider()->SetOffSetPos({ 0, -20 });

	CreateAnimator();
	GetAnimator()->CreateAnim(L"EnemyIdle", _texture, Vector2(0, 0), Vector2(300, 300), Vector2(300.f, 0.f), 2, 0.5f);
	GetAnimator()->PlayAnim(L"EnemyIdle", true);

	CreateHealth();
	GetHealth()->SetHP(10);
	//TimeManager::GetInstance()->TimePass(2.f, this);
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	GetHealth()->Update();

	_time += DeltaTime;

	if (_time >= _spawnTime)
	{
		_time = 0;
		ShootBullet();
	}
}

void Enemy::Render(HDC dc)
{
	Component_Render(dc);
}

void Enemy::EndTimer(Timer* timer)
{
	//ShootBullet();
	//TimeManager::GetInstance()->TimePass(2.f, this);
}

void Enemy::EnterCollision(Collider* other)
{
	GetHealth()->Damage(1);
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
