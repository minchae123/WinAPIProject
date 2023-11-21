#pragma once
class Collider;
union COLLIDER_ID
{
	struct
	{
		UINT left_ID;
		UINT right_ID;
	};
	ULONGLONG ID;
};
class CollisionManager
{
	SINGLE(CollisionManager);
public:
	void Update();
	void CheckGroup(OBJECT_GROUP eLeft, OBJECT_GROUP eRight);
	void CheckReset();
private:
	void CollisionGroupUpdate(OBJECT_GROUP eLeft, OBJECT_GROUP eRight);
	bool IsCollision(Collider* pLeft, Collider* pRight);
private:
	// �׷찣�� �浹üũ�� �迭
	UINT _arrCheck[(UINT)OBJECT_GROUP::END];
	map<ULONGLONG, bool> _mapColInfo;
};

