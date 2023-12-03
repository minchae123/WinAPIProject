#pragma once
class Object;

class Collider
{
public:
	Collider();
	Collider(const Collider& origin);
	~Collider();
	Collider& operator = (Collider& origin) = delete;
public:
	void FinalUpdate();
	void Render(HDC dc); // 이건 제출 할때 지우기
public:
	void EnterCollision(Collider* other);
	void ExitCollision(Collider* other);
	void StayCollision(Collider* other);
public:
	void SetScale(Vector2 scale) { _scale = scale; }
	void SetOffSetPos(Vector2 offsetPos)
	{ _offsetPos = offsetPos; }
	const Vector2& GetScale() const { return _scale; }
	const Vector2& GetOffSetPos() const { return _offsetPos; }
	const Vector2& GetFinalPos() const
	{ return _finalPos; }
	const UINT& GetID() const { return _ID; }
	const Object* GetObj() const { return _ownerObject; }
	Vector2 GetHeightVector();
	Vector2 GetWidthVector();
private:
	UINT _check;
	Object* _ownerObject;
	Vector2 _offsetPos; // 오프셋
	Vector2 _finalPos; // 파이널 위치
	Vector2 _scale; // 크기
	friend class Object;
	UINT _ID; // 충돌체 ID값
	static UINT _nextID;
};

