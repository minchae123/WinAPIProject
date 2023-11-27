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
#include <string>

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

	Rectangle(dc, GetClampMin().x, GetClampMin().y, GetClampMax().x, GetClampMax().y);
	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, dc);
}

void PlayerController::Move()
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		//pos.x -= _moveSpeed * DeltaTime;
		pos.x = std::clamp(pos.x - _moveSpeed * DeltaTime, GetClampMin().x + scale.x / 2, GetClampMax().x - scale.x / 2);
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		pos.x = std::clamp(pos.x + _moveSpeed * DeltaTime, GetClampMin().x + scale.x / 2, GetClampMax().x - scale.x / 2);
	}
	if (KEY_PRESS(KEY_TYPE::UP))
	{
		pos.y = std::clamp(pos.y - _moveSpeed * DeltaTime, GetClampMin().y + scale.y / 2, GetClampMax().y - scale.y / 2);
	}
	if (KEY_PRESS(KEY_TYPE::DOWN))
	{
		pos.y = std::clamp(pos.y + _moveSpeed * DeltaTime, GetClampMin().y + scale.y / 2, GetClampMax().y - scale.y / 2);
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
	wstring dirX = std::to_wstring((int)point.x - pos.x);
	wstring dirY = std::to_wstring((int)point.y - pos.y);
	DebugLog(dirX + L" " + dirY);
	Vector2 dir = Vector2(point.x - pos.x, point.y - pos.y);
	//DebugManager::GetInstance()->SetLog();
	Bullet* newBullet = new Bullet;
	newBullet->SetPos(pos);
	newBullet->SetScale(Vector2(25.f, 25.f));
	newBullet->SetDir(dir);
	newBullet->SetName(L"PlayerBullet");
	SceneManager::GetInstance()->GetCurScene()->AddObject(newBullet, OBJECT_GROUP::BULLET);
}
