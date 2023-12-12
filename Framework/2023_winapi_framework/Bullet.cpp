#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "DebugManager.h"
#include "EventMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "Core.h"

Bullet::Bullet()
//	: m_fDir(-1.f)
	: _theta(0.f)
	, _dir(Vector2(0.f, 0.f))
	, _texture(nullptr)
	, _moveSpeed(500.f)
	, _vecMove(true)
	, _shootObj(nullptr)
	, _cnt(0)
{
	_texture = ResourceManager::GetInstance()->TexLoad(L"Bullet", L"Texture\\EBullet.bmp");
	CreateCollider();

	CreateAnimator();
	//GetAnimator()->CreateAnim
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_cnt >= 10)
	{
		EventManager::GetInstance()->DeleteObject(this);
	}

	//if (_shootObj != nullptr)
	Vector2 pos = GetPos();
	if (_vecMove)
	{
		pos.x += _moveSpeed * DeltaTime * _dir.x;
		pos.y += _moveSpeed * DeltaTime * _dir.y;
	}
	else
	{
		pos.y += _moveSpeed * DeltaTime * sinf(_theta);
		pos.x += _moveSpeed * DeltaTime * cosf(_theta);
	}

	pos = Vector2(std::clamp(pos.x, GetClampMin().x, GetClampMax().x)
		, std::clamp(pos.y, GetClampMin().y, GetClampMax().y));
	
	if (pos.x <= GetClampMin().x || pos.x >= GetClampMax().x ||
		pos.y <= GetClampMin().y || pos.y >= GetClampMax().y )
	{
		Reflect();
	}
	SetPos(pos);
}

void Bullet::Render(HDC _dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();
	int Width = _texture->GetWidth();
	int Height = _texture->GetHeight();
	/*TransparentBlt(_dc
		, (int)(pos.x - scale.x / 2)
		, (int)(pos.y - scale.y / 2)
		, Width, Height, _texture->GetDC()
		, 100, 100, Width / 5, Height / 5, RGB(255, 0, 255));
	Component_Render(_dc);*/

	/*HBITMAP stretchBit = CreateCompatibleBitmap(_dc
		, Core::GetInstance()->GetResolution().x
		, Core::GetInstance()->GetResolution().y);
	HDC stretchDC = CreateCompatibleDC(_dc);
	SelectObject(stretchDC, stretchBit);

	PatBlt(stretchDC, 0, 0
		, Core::GetInstance()->GetResolution().x
		, Core::GetInstance()->GetResolution().y, WHITENESS);

	StretchBlt(stretchDC
		, (int)(pos.x - scale.x / 2)
		, (int)(pos.y - scale.y / 2)
		, Width / 5, Height / 5, _texture->GetDC()
		, 0, 0, Width, Height, SRCCOPY);

	TransparentBlt(_dc
		, (int)(pos.x - scale.x / 2)
		, (int)(pos.y - scale.y / 2)
		, Width, Height, _texture->GetDC()
		, 0, 0, Width, Height, RGB(255, 0, 255));
	Component_Render(_dc);

	DeleteObject(stretchBit);*/
	Component_Render(_dc);
}

void Bullet::Reflect()
{
	Vector2 normal = GetPos();
	Vector2 clampMin = GetClampMin();
	Vector2 clampMax = GetClampMax();
	_cnt++;
	if (normal.x == clampMin.x || normal.x == clampMax.x)
	{
		_dir.x *= -1;
	}
	else if (normal.y == clampMin.y || normal.y == clampMax.y)
	{
		_dir.y *= -1;
	}
}
