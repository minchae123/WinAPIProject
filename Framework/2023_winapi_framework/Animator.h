#pragma once
class Object;
class Texture;
class Animation;
class Animator
{
public:
	Animator();
	~Animator();
public:
	void Update();
	void Render(HDC _dc);
public:
	// 애니메이션 생성함수
	void CreateAnim(const wstring& name, Texture* texture,
					Vector2 leftTop, Vector2 sliceSize, Vector2 step,
					UINT frameCount, float duration);
	// 애니메이션 찾기함수
	Animation* FindAnim(const wstring& name);

	// 애니메이션 플레이 함수
	void PlayAnim(const wstring& name, bool repeat, int repeatCount = 1);
public:
	Object* GetObj() const { return _ownerObject; }
	const bool& GetRepeat() const { return _isRepeat; }
	const int& GetRepeatcnt() const { return _repeatCount; }
	void SetRepeatcnt() { --_repeatCount; }
private:
	map<wstring, Animation*> _mapAnim;
	Animation* _curAnim;
	Object* _ownerObject;
	friend class Object;
	bool	_isRepeat;
	int		_repeatCount;
};

