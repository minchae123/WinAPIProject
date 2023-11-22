#include "pch.h"
#include "PlayerController.h"
#include "TimeMgr.h"
#include "KeyMgr.h"

PlayerController::PlayerController()
	: _texture(nullptr)
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
}

void PlayerController::Move()
{
	Vector2 vPos = GetPos();

	if (KEY_PRESS(KEY_TYPE::LEFT))
	{
		vPos.x -= 100.f * DeltaTime;
	}
	if (KEY_PRESS(KEY_TYPE::RIGHT))
	{
		vPos.x += 100.f * DeltaTime;
	}
	SetPos(vPos);
}

void PlayerController::CreateBullet()
{
}
