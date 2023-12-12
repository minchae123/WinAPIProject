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
	void SetIdx(int idx) { _idx = idx; }
	bool GetOn() const { return _onTimer; }
private:
	float _curTime; // �귯�� �Ǵ� �ð�
	float _time;	// �帣�� �ִ� �ð�
	bool _onTimer;
	Object* _ownerObject;
	int _idx;
};

