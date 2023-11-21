#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
Object::Object()
	: _pCollider(nullptr)
	, _pos{}
	, _scale{}
	, _isAlive(true)
	, _pAnimator(nullptr)
{
}

Object::~Object()
{
	if (nullptr != _pCollider)
		delete _pCollider;
	if (nullptr != _pAnimator)
		delete _pAnimator;

}

void Object::CreateCollider()
{
	_pCollider = new Collider;
	_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	_pAnimator = new Animator;
	_pAnimator->m_pOwner = this;
}

void Object::Update()
{
	//Vec2 vPos = m_obj.GetPos();

//	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
//	if(KeyMgr::GetInst()->GetKey(KEY_TYPE::LEFT) == KEY_STATE::UP)

	//m_obj.SetPos(vPos);
}

void Object::FinalUpdate()
{
	if (_pCollider)
		_pCollider->FinalUpdate();
}

void Object::Render(HDC dc)
{
	/*Vec2 vPos = m_obj.GetPos();
	Vec2 vScale = m_obj.GetScale();*/
	RECT_RENDER(_pos.x, _pos.y, _scale.x, _scale.y, _dc);
	Component_Render(dc);
}

void Object::EnterCollision(Collider* other)
{
}

void Object::ExitCollision(Collider* other)
{
}

void Object::StayCollision(Collider* other)
{

}

void Object::Component_Render(HDC dc)
{
	if (nullptr != _pCollider)
		_pCollider->Render(dc);
	if (nullptr != _pAnimator)
		_pAnimator->Render(dc);

}

