#include "pch.h"
#include "Scene.h"
#include "Object.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < _vecObject[i].size(); ++j)
		{
			if(!_vecObject[i][j]->GetIsDead())
				_vecObject[i][j]->Update();
		}
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < _vecObject[i].size(); ++j)
		{
			_vecObject[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < _vecObject[i].size();)
		{
			if (!_vecObject[i][j]->GetIsDead())
			{
				_vecObject[i][j]->Render(_dc);
				++j;
			}
			else
				_vecObject[i].erase(_vecObject[i].begin() + j);
		}
	}
}

void Scene::Release()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < _vecObject[i].size(); ++j)
		{
			delete _vecObject[i][j];
		}
		_vecObject[i].clear();
	}
}
