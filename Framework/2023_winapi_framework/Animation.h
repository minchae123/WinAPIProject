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
	UINT   _curFrame; // ���� ������
	float  _accTime; // ���� �ð�
	int	   _repeatCount; // �ݺ� Ƚ��
	Texture* _texture; // �ִϸ��̼� �ؽ�ó
	vector<AnimationFrame> _vecAnimationFrame;
	wstring _name;
	Animator* _animator;

};

