#pragma once
class Object;
class Timer;
class TimeManager
{
	SINGLE(TimeManager);
public:
	void Init();
	void Update();
public:
	const float& GetDeltaTime() const { return _deltaTime; }
	const float& GetTime() const { return _accFrameTime; }
private:
	// DT(1�����Ӵ� �ð�: Delta time)
	LARGE_INTEGER _llPrevCount; // �����ð�
	LARGE_INTEGER _llCurCount; // ����ð�
	LARGE_INTEGER _llFrequency; // ���ļ�
	float _deltaTime; // �����Ӱ��� �ð� ��

	// FPS
	UINT  _fps; // FPS
	UINT  _frameCount; // ������ ȣ�� üũ
	float _accFrameTime; // �ð� ����

	vector<Timer*> _vecTimer;
	int _currentIdx;

public:
	void TimePass(float duration, Object* obj);
	void PopTime(int idx);
};

