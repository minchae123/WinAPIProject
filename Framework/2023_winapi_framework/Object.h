#pragma once
class Collider;
class Animator;
class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC dc);
	virtual void EnterCollision(Collider* other);
	virtual void ExitCollision(Collider* other);
	virtual void StayCollision(Collider* other);
	void Component_Render(HDC dc);
public:
	void SetPos(Vector2 pos) { _pos = pos; }
	void SetScale(Vector2 scale) { _scale = scale; }
	const Vector2& GetPos() const { return _pos; }
	const Vector2& GetScale() const { return _scale; }
	const Vector2& GetClampMin() const { return _clampMin; }
	const Vector2& GetClampMax() const { return _clampMax; }
	Collider* GetCollider() const 
	{ return _pCollider; }
	Animator* GetAnimator()
	{
		return _pAnimator;
	}
	const wstring& GetName() const { return _name; }
	void SetName(wstring name) { _name = name; }
	bool GetIsDead() const { return !_isAlive; }
private:
	void SetDead() { _isAlive = false; }
	friend class EventManager;
public:
	void CreateCollider();
	void CreateAnimator();
private:
	Vector2 _pos; // 위치
	Vector2 _scale; // 크기
	Vector2 _clampMin;
	Vector2 _clampMax;
	Collider* _pCollider;
	wstring _name; // 이름.
	bool _isAlive;
	Animator* _pAnimator;
};

