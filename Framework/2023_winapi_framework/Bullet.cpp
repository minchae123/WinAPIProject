#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
Bullet::Bullet()
	: m_fTheta(0.f)
	, m_vDir(Vector2(0.f,0.f))
	, m_pTex(nullptr)
{
	m_pTex = ResourceManager::GetInstance()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vector2 vPos = GetPos();
	vPos.x += 500.f * DeltaTime * m_vDir.x;
	vPos.y += 500.f * DeltaTime * m_vDir.y;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vector2 vPos = GetPos();
	Vector2 vScale = GetScale();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();
	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width,Height, RGB(255,0,255));
	Component_Render(_dc);
}
