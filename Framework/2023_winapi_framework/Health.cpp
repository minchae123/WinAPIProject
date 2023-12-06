#include "pch.h"
#include "Health.h"
#include "EventMgr.h"

Health::Health()
	: _hp(0)
	, _ownerObject(nullptr)
{
}

Health::~Health()
{
}

void Health::Update()
{
	if (_hp <= 0)
	{
		EventManager::GetInstance()->DeleteObject(_ownerObject);
	}
}

void Health::Render(HDC dc)
{

}

void Health::Damage(int damage)
{
	_hp -= damage;
}
