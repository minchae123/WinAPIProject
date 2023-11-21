#include "pch.h"
#include "EventMgr.h"
#include "Object.h"
void EventMgr::Update()
{
	for (size_t i = 0; i < _vecDead.size(); ++i)
	{
		delete _vecDead[i];
	}
	_vecDead.clear();

	for (size_t i = 0; i < _vecEvent.size(); ++i)
	{
		Excute(_vecEvent[i]);
	}
	_vecEvent.clear();
}

void EventMgr::DeleteObject(Object* pObj)
{
	Event eve = {};
	eve.eEve = EVENT_TYPE::DELETE_OBJECT;
	eve.Object = pObj;
	_vecEvent.push_back(eve);
}

void EventMgr::Excute(const Event& eve)
{
	switch (eve.eEve)
	{
	case EVENT_TYPE::DELETE_OBJECT:
	{
		Object* pDeadObj = eve.Object;
		pDeadObj->SetDead();
		_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::CREATE_OBJECT:
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		break;
	}
}
