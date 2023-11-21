#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeMgr.h"
Animation::Animation()
	: _animator(nullptr)
	, _curFrame(0)
	, _texture(nullptr)
	, _accTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (_animator->GetRepeatcnt() <= 0)
		return;
	_accTime += DeltaTime;
	// ������ �ð��� ���� �� �����ӿ� ������ �ð��� �Ѿ��?
	if (_accTime >= _vecAnimationFrame[_curFrame].fDuration)
	{
		// �ϴ� ���� �ð����� ���� ������ �ð��� ����
		_accTime -= _vecAnimationFrame[_curFrame].fDuration;
		++_curFrame; // �������������� �ű��
		if (_curFrame >= _vecAnimationFrame.size()) // �ѹ��� �����ϰ�;�
		{
			if (!_animator->GetRepeat())
				_animator->SetRepeatcnt();
			_curFrame = 0;
			_accTime = 0.f;
		}

	}
}

void Animation::Render(HDC dc)
{
	Object* pObj = _animator->GetObj();
	Vector2 vPos = pObj->GetPos();

	// ������ ����
	vPos = vPos + _vecAnimationFrame[_curFrame].vOffset;
	TransparentBlt(dc
		,(int)(vPos.x - _vecAnimationFrame[_curFrame].vSlice.x /2.f)
		,(int)(vPos.y - _vecAnimationFrame[_curFrame].vSlice.y / 2.f)
		,(int)(_vecAnimationFrame[_curFrame].vSlice.x)
		,(int)(_vecAnimationFrame[_curFrame].vSlice.y)
		,_texture->GetDC()
		,(int)(_vecAnimationFrame[_curFrame].vLT.x)
		,(int)(_vecAnimationFrame[_curFrame].vLT.y)
		,(int)(_vecAnimationFrame[_curFrame].vSlice.x)
		,(int)(_vecAnimationFrame[_curFrame].vSlice.y)
		,RGB(255,0,255));
}

void Animation::Create(Texture* texture, Vector2 leftTop, Vector2 sliceSize, Vector2 step, int framecount, float duration)
{
	_texture = texture;
	for (int i = 0; i < framecount; ++i)
	{
		_vecAnimationFrame.push_back(AnimationFrame({ leftTop + step * i,
			sliceSize, duration,{0.f,0.f} }));
	}

}
