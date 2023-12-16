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
#include "ResMgr.h"
#include "Collider.h"
#include "Object.h"
#include "Animator.h"
#include "Animation.h"
#include "Health.h"
#include "ResultManager.h"

Enemy::Enemy(int hp)
	: _texture(nullptr)
	, _hitTexture(nullptr)
	, _time(0)
	, _spawnTime(1.f)
	, _hit(false)
	, _hitTime(0)
	, _hp(hp)
{
	_texture = ResourceManager::GetInstance()->TexLoad(L"Enemy", L"Texture\\Bat.bmp");
	_hitTexture = ResourceManager::GetInstance()->TexLoad(L"Enemy", L"Texture\\Bathit.bmp");
	CreateCollider();
	GetCollider()->SetScale({ 100, 70 });
	GetCollider()->SetOffSetPos({ 0, -20 });

	Object::CreateAnimator();
	GetAnimator()->CreateAnim(L"EnemyIdle", _texture, Vector2(0, 0), Vector2(300, 300), Vector2(300.f, 0.f), 2, 0.5f);
	GetAnimator()->PlayAnim(L"EnemyIdle", true, 100);
	GetAnimator()->CreateAnim(L"EnemyHit", _hitTexture, Vector2(0, 0), Vector2(300, 300), Vector2(300.f, 0.f), 2, 0.5f);

	Object::CreateHealth();
	GetHealth()->SetHP(_hp);
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

	if (_hit)
	{
		_time += DeltaTime;

		if (_time >= 0.5f)
		{
			_hit = false;
			_hitTime = 0;
			ResultManager::GetInstance()->SetMonster();
			GetAnimator()->PlayAnim(L"EnemyIdle", true);
		}
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
	if (other->GetObj()->GetName() == L"Bullet")
	{
		GetHealth()->Damage(1);
		GetAnimator()->PlayAnim(L"EnemyHit", false);
		_hit = true;
	}
}

void Enemy::ShootBullet()
{
	Object* player = SceneManager::GetInstance()->GetCurScene()->GetGroupObject(OBJECT_GROUP::PLAYER)[0];
	Vector2 playerPos = player->GetPos();
	Vector2 pos = GetPos();
	Vector2 dir = Vector2(playerPos.x - pos.x, playerPos.y - pos.y);
	dir = dir.Normalize();
	Vector2 shootPos = Vector2(pos.x + dir.x * 60, pos.y + dir.y * 60);
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(shootPos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"Bullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}
