#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
UINT Collider::_nextID = 0;
Collider::Collider()
	: _ownerObject(nullptr)
	, _scale(Vector2(40.f,40.f))
	, _ID(_nextID++)
	, _check(0)
	, _finalPos{}
{
}

Collider::Collider(const Collider& origin)
	: _ownerObject(nullptr)
	, _scale(origin._scale)
	, _offsetPos(origin._offsetPos)
	, _ID(_nextID++)
	, _check(0)
	, _finalPos{}
{
}

Collider::~Collider()
{}

void Collider::Render(HDC dc)
{
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (_check)
		ePen = PEN_TYPE::RED;
	SelectGDI pen(dc, ePen);
	SelectGDI brush(dc, BRUSH_TYPE::HOLLOW);
	RECT_RENDER(_finalPos.x, _finalPos.y, _scale.x, _scale.y, dc);
}

void Collider::EnterCollision(Collider* other)
{
 	++_check;
	_ownerObject->EnterCollision(other);
}

void Collider::ExitCollision(Collider* other)
{
	--_check;
	_ownerObject->ExitCollision(other);
}

void Collider::StayCollision(Collider* other)
{
	_ownerObject->StayCollision(other);
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	Vector2 vObjPos = _ownerObject->GetPos();
	_finalPos = vObjPos + _offsetPos;
}

