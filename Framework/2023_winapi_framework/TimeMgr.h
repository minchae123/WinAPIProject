#pragma once
class TimeManager
{
	SINGLE(TimeManager);
public:
	void Init();
	void Update();
public:
	const float& GetDeltaTime() const { return _deltaTime; }
private:
	// DT(1프레임당 시간: Delta time)
	LARGE_INTEGER _llPrevCount; // 이전시간
	LARGE_INTEGER _llCurCount; // 현재시간
	LARGE_INTEGER _llFrequency; // 주파수
	float _deltaTime; // 프레임간의 시간 값

	// FPS
	UINT  _fps; // FPS
	UINT  _frameCount; // 프레임 호출 체크
	float _accFrameTime; // 시간 누적
};

