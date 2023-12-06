#include "pch.h"
#include "PlayerController.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "DebugManager.h"
#include "KeyMgr.h"
#include "Health.h"
#include "CollisionMgr.h"

PlayerController::PlayerController()
	: _texture(nullptr)
	, _moveSpeed(200.f)
{
	CreateCollider();
	CreateHealth();
	GetHealth()->SetHP(5);
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
	Move();
	//GetAnimator()->Update();
	GetHealth()->Update();
}

void PlayerController::Render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, dc);
	Component_Render(dc);
}

void PlayerController::Move()
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	if (KEY_PRESS(KEY_TYPE::A))
	{
		//pos.x -= _moveSpeed * DeltaTime;
		pos.x = std::clamp(pos.x - _moveSpeed * DeltaTime, GetClampMin().x + scale.x / 2, GetClampMax().x - scale.x / 2);
	}
	if (KEY_PRESS(KEY_TYPE::D))
	{
		pos.x = std::clamp(pos.x + _moveSpeed * DeltaTime, GetClampMin().x + scale.x / 2, GetClampMax().x - scale.x / 2);
	}
	if (KEY_PRESS(KEY_TYPE::W))
	{
		pos.y = std::clamp(pos.y - _moveSpeed * DeltaTime, GetClampMin().y + scale.y / 2, GetClampMax().y - scale.y / 2);
	}
	if (KEY_PRESS(KEY_TYPE::S))
	{
		pos.y = std::clamp(pos.y + _moveSpeed * DeltaTime, GetClampMin().y + scale.y / 2, GetClampMax().y - scale.y / 2);
	}
	
	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		ShootBullet();
	}

	if (KEY_PRESS(KEY_TYPE::Q))
	{
		_angle -= _rotateSpeed * DeltaTime;
	}
	if (KEY_PRESS(KEY_TYPE::E))
	{
		_angle += _rotateSpeed * DeltaTime;
	}
	//pos.x = std::clamp(pos.y, _clampMin.y, _clampMax.y);
	SetPos(pos);
}

void PlayerController::ShootBullet()
{
	Vector2 mousePos = KeyManager::GetInstance()->GetMousePos();
	Vector2 pos = GetPos();
	Vector2 dir = Vector2(mousePos.x - pos.x, mousePos.y - pos.y);
	Vector2 shootPos = Vector2(pos.x + dir.x * 3, pos.y + dir.y * 3);
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"Bullet");
	newBullet->SetObj(this);
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}

void PlayerController::EnterCollision(Collider* other)
{
	const Object* otherObj = other->GetObj();
	if (otherObj->GetName() == L"Bullet")
	{
		GetHealth()->Damage(1);
	}
}

void PlayerController::ExitCollision(Collider* other)
{
}

void PlayerController::StayCollision(Collider* other)
{
}