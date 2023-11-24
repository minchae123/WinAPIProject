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

PlayerController::PlayerController()
	: _texture(nullptr)
	, _moveSpeed(200.f)
	, _rightVec(Vector2(1, 0))
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::Update()
{
	Move();
}

void PlayerController::Render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, dc);
}

void PlayerController::Move()
{
	Vector2 pos = GetPos();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		//pos.x -= _moveSpeed * DeltaTime;
		pos.x = std::clamp(pos.x - _moveSpeed * DeltaTime, GetClampMin().x, GetClampMax().x);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		pos.x = std::clamp(pos.x + _moveSpeed * DeltaTime, GetClampMin().x, GetClampMax().x);
	}
	if (KEY_PRESS(KEY_TYPE::UP))
	{
		pos.y = std::clamp(pos.y - _moveSpeed * DeltaTime, GetClampMin().y, GetClampMax().y);
	}
	if (KEY_PRESS(KEY_TYPE::DOWN))
	{
		pos.y = std::clamp(pos.y + _moveSpeed * DeltaTime, GetClampMin().y, GetClampMax().y);
	}
	if (KEY_DOWN(KEY_TYPE::SPACE))
	{
		CreateBullet();
	}
	//pos.x = std::clamp(pos.y, _clampMin.y, _clampMax.y);
	SetPos(pos);
}

void PlayerController::CreateBullet()
{
	POINT point;
	GetCursorPos(&point);
	Vector2 pos = GetPos();
	Vector2 dir = Vector2(point.x - pos.x, point.y - pos.y);
	Bullet* newBullet = new Bullet;
	Vector2 bulletPos = GetPos();
	newBullet->SetPos(bulletPos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"PlayerBullet");
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}
