#pragma once
class Collider;
class Animator;
class Timer;
class Health;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Update();
	virtual void FinalUpdate() final;
	virtual void Render(HDC dc);
	virtual void EnterCollision(Collider* other);
	virtual void ExitCollision(Collider* other);
	virtual void StayCollision(Collider* other);
	virtual void EndTimer(Timer* timer);
	void Component_Render(HDC dc);
public:
	void SetPos(Vector2 pos) { _pos = pos; }
	void SetScale(Vector2 scale) { _scale = scale; }
	const Vector2& GetPos() const { return _pos; }
	const Vector2& GetScale() const { return _scale; }
	const Vector2& GetClampMin() const { return _clampMin; }
	const Vector2& GetClampMax() const { return _clampMax; }
	Collider* GetCollider() const { return _pCollider; }
	Animator* GetAnimator() { return _pAnimator; }
	Health* GetHealth() { return _health; }
	const wstring& GetName() const { return _name; }
	void SetName(wstring name) { _name = name; }
	bool GetIsDead() const { return !_isAlive; }
	const float& GetAngle() const { return _angle; }
private:
	void SetDead() { _isAlive = false; }
	friend class EventManager;
public:
	void CreateCollider();
	void CreateAnimator();
	void CreateHealth();
private:
	Vector2 _pos; // 위치
	Vector2 _scale; // 크기
	Vector2 _clampMin;
	Vector2 _clampMax;
	wstring _name; // 이름.
	bool _isAlive;
private:
	Collider* _pCollider;
	Animator* _pAnimator;
	Health* _health;
protected:
	float _angle;
	float _rotateSpeed;
};

