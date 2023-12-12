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
	float _curTime; // 흘러야 되는 시간
	float _time;	// 흐르고 있는 시간
	bool _onTimer;
	Object* _ownerObject;
	int _idx;
};

