#pragma once
class Object;
struct Event
{
	EVENT_TYPE eEve; // �̺�Ʈ Ÿ��
	Object* Object;
	OBJECT_GROUP ObjectType;
};
class EventMgr
{
	SINGLE(EventMgr);
public:
	void Update();
	void DeleteObject(Object* pObj);
private:
	void Excute(const Event& eve);
private:
	vector<Event> _vecEvent;
	vector<Object*> _vecDead;
};

