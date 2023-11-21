#pragma once
class Texture; class Animator;
struct AnimationFrame
{
	Vector2 vLT;
	Vector2 vSlice;
	float fDuration;
	Vector2 vOffset;
};

class Animation
{
public:
	Animation();
	~Animation();
public:
	void Update();
	void Render(HDC dc);
public:
	void Create(Texture* texture, Vector2 leftTop, Vector2 sliceSize,
		Vector2 step, int framecount, float duration);
public:
	const wstring& GetName() const { return _name; }
	void SetName(wstring name) { _name = name; }
	void SetFrameOffset(int index, Vector2 offset) { _vecAnimationFrame[index].vOffset = offset; }
	const size_t& GetMaxFrame() { return _vecAnimationFrame.size(); }
	friend class Animator;
private:
	UINT   _curFrame; // 현재 프레임
	float  _accTime; // 누적 시간
	int	   _repeatCount; // 반복 횟수
	Texture* _texture; // 애니메이션 텍스처
	vector<AnimationFrame> _vecAnimationFrame;
	wstring _name;
	Animator* _animator;

};

