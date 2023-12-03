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
	void Render(HDC dc); // �̰� ���� �Ҷ� �����
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
	Vector2 _offsetPos; // ������
	Vector2 _finalPos; // ���̳� ��ġ
	Vector2 _scale; // ũ��
	friend class Object;
	UINT _ID; // �浹ü ID��
	static UINT _nextID;
};

