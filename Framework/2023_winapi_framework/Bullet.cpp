#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "DebugManager.h"
#include "EventMgr.h"
#include <string>

Bullet::Bullet()
//	: m_fDir(-1.f)
	: _theta(0.f)
	, _dir(Vector2(0.f,0.f))
	, _texture(nullptr)
	, _moveSpeed(500.f)
{
	_texture = ResourceManager::GetInstance()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vector2 pos = GetPos();
	pos.x += _moveSpeed * DeltaTime * _dir.x;
	pos.y += _moveSpeed * DeltaTime * _dir.y;
	/*
	pos.x += _moveSpeed * DeltaTime * cosf(m_fTheta);
	pos.y += _moveSpeed * DeltaTime * sinf(m_fTheta);
	*/

	if (pos.x < GetClampMin().x || pos.x > GetClampMax().x ||
		pos.y < GetClampMin().y || pos.y > GetClampMax().y )
	{
		Reflect();
		DebugLog(Text(pos.x) + L" " + Text(pos.y));
	}
	SetPos(pos);
}

void Bullet::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int Width = _texture->GetWidth();
	int Height = _texture->GetHeight();
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, _texture->GetDC()
		, 0, 0, Width,Height, RGB(255,0,255));
	Component_Render(_dc);
}

void Bullet::Reflect()
{
	Vector2 normal = GetPos();
	Vector2 clampMin = GetClampMin();
	Vector2 clampMax = GetClampMax();
 	normal = Vector2(std::clamp(normal.x, clampMin.x, clampMax.x)
				, std::clamp(normal.y, clampMin.y, clampMax.y));

	if (normal.x == clampMin.x || normal.x == clampMax.x)
	{
		_dir.x *= -1;
	}
	else if (normal.y == clampMin.y || normal.y == clampMax.y)
	{
		_dir.y *= -1;
	}
}
