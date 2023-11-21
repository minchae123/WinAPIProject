#pragma once
//#include "Object.h"
class Object;
class Scene
{
public:
	Scene();
	virtual ~Scene();
	// Init(), Update(), Render(), Release();
	virtual void Init() abstract;
	virtual void Update();
	virtual void FinalUpdate();
	virtual void Render(HDC _dc);
	virtual void Release();
public:
	const vector<Object*>& GetGroupObject(OBJECT_GROUP type) const
	{
		return _vecObject[(UINT)type];
	}
public:
	void AddObject(Object* pObject, OBJECT_GROUP type)
	{
		_vecObject[(UINT)type].push_back(pObject);
	}
private:
//	Object*  m_obj;
	vector<Object*> _vecObject[(UINT)OBJECT_GROUP::END];
};

