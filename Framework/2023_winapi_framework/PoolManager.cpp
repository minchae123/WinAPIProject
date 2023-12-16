#include "pch.h"
#include "PoolManager.h"
#include "Object.h"
#include "Enemy.h"
#include "Bullet.h"
#include "LevelManager.h"

void PoolManager::Init(OBJECT_GROUP _eType, int _poolSize)
{
	for (int i = 0; i < _poolSize; ++i)
	{
		Object* obj = nullptr;
		switch (_eType)
		{
		case OBJECT_GROUP::BULLET:
		{
			obj = new Bullet;
		}
		break;
		case OBJECT_GROUP::ENEMY:
		{
			obj = new Enemy(LevelManager::GetInstance()->GetEnemyHP());
		}
		break;
		}

		auto& objList = m_mapObjPool[_eType];
		objList.push_back(obj);
	}

}

void PoolManager::Release()
{
	for (auto& pool : m_mapObjPool)
	{
		for (Object* obj : pool.second)
		{
			if (nullptr != obj)
				delete obj;
		}
	}
}

Object* PoolManager::GetObj(OBJECT_GROUP _eType)
{
	auto& objList = m_mapObjPool[_eType];
	if (!objList.empty()) // 이미 할당된게 있는거.
	{
		Object* obj = objList.front();
		objList.pop_front();
		return obj;
	}
	else
	{
		Object* obj = nullptr;
		switch (_eType)
		{
		case OBJECT_GROUP::BULLET:
		{
			obj = new Bullet;
		}
		break;
		case OBJECT_GROUP::ENEMY:
		{
			obj = new Enemy(LevelManager::GetInstance()->GetEnemyHP());
			break;
		}
		return obj;
		}
	}
	return nullptr;
}

void PoolManager::ReturnObj(OBJECT_GROUP _eType, Object* _pObj)
{
	m_mapObjPool[_eType].push_back(_pObj);
}

