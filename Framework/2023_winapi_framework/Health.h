#pragma once
class Object;
class Health
{
public:
	Health();
	~Health();
public:
	void Update();
	void Render(HDC dc);
public: 
	Object* GetObj() const { return _ownerObject; }
	void Damage(int damage = 1);
	void SetHP(int hp) { _hp = hp; }
	int GetHealth() const { return _hp; }
private:
	int _hp;
	Object* _ownerObject;
	friend class Object;
};

