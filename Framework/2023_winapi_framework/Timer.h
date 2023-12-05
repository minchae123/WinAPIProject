#pragma once
class Object;
class Timer
{
public:
	Timer();
	~Timer();
public:
	void Update();
public:
	void SetTimer(float time, Object* obj);
private:
	float _curTime; // �귯�� �Ǵ� �ð�
	float _time;	// �帣�� �ִ� �ð�
	bool _onTimer;
	Object* _ownerObject;
};

