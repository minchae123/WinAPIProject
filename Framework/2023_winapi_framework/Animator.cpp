#include "pch.h"
#include "Animator.h"
#include "Animation.h"
Animator::Animator()
	: _ownerObject(nullptr)
	, _curAnim(nullptr)
	, _isRepeat(false)
{
}

Animator::~Animator()
{
	map<wstring, Animation*>::iterator iter;
	for (iter = _mapAnim.begin(); iter != _mapAnim.end(); ++iter)
	{
		if (iter->second != nullptr)
			delete iter->second;
	}
	_mapAnim.clear();
}

void Animator::Update()
{
	if (nullptr != _curAnim)
	{
		_curAnim->Update();
	}
}

void Animator::Render(HDC _dc)
{
	if (nullptr != _curAnim)
	{
		_curAnim->Render(_dc);
	}
}

void Animator::CreateAnim(const wstring& name, Texture* texture,
	Vector2 leftTop, Vector2 sliceSize, Vector2 step,
	UINT frameCount, float duration)
{
	Animation* pAnim = FindAnim(name);
	if (pAnim != nullptr)
		return;
	
	pAnim = new Animation;
	pAnim->SetName(name);
	pAnim->_animator = this;
	pAnim->Create(texture, leftTop, sliceSize, step, frameCount, duration);
	_mapAnim.insert({ name,pAnim });
}

Animation* Animator::FindAnim(const wstring& name)
{
	map<wstring, Animation*>::iterator iter = _mapAnim.find(name);
	if (iter == _mapAnim.end())
		return nullptr;
	return iter->second;
}

void Animator::PlayAnim(const wstring& name, bool repeat, int repeatCount)
{
	_curAnim = FindAnim(name);
	_isRepeat = repeat;
	_repeatCount = repeatCount;
}
