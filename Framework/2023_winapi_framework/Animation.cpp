#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "Core.h"

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
	/*if (_animator->GetRepeatcnt() <= 0)
		return;*/
	_accTime += DeltaTime;
	// 누적한 시간이 내가 이 프레임에 진행한 시간을 넘어섰냐?
	if (_accTime >= _vecAnimationFrame[_curFrame].fDuration)
	{
		// 일단 모은 시간에서 현재 진행한 시간을 빼고
		_accTime -= _vecAnimationFrame[_curFrame].fDuration;
		++_curFrame; // 다음프레임으로 옮기기
		if (_curFrame >= _vecAnimationFrame.size()) // 한바퀴 돌게하고싶어
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
	// 기본 애니메이션
	/*Object* pObj = _animator->GetObj();
	Vector2 vPos = pObj->GetPos();

	// 오프셋 적용
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
		,RGB(255,0,255));*/
	// 회전 애니메이션
	Object* pObj = _animator->GetObj();
	Vector2 pos = pObj->GetPos();
	Vector2 scale = pObj->GetScale();
	Vector2 center = pos;
	float angle = pObj->GetAngle();
	// 오프셋 적용
	//pos = pos + m_vecAnimFrame[m_CurFrame].vOffset;
	POINT point[3] = { 0 }; // LT, RT, LB
	float x, y, fxDest, fyDest; // P(fx, fy), P'(fxDest,fyDest)
	float radian = angle * M_PI / 180.f;
	float cosTheta = cosf(radian);
	float sinTheta = sinf(radian);

	for (int i = 0; i < 3; ++i)
	{
		if (i == 0)
		{
			x = -scale.x / 2.f;
			y = -scale.y / 2.f;
		}
		else if (i == 1)
		{
			x = scale.x / 2.f;
			y = -scale.y / 2.f;
		}
		else if (i == 2)
		{
			x = -scale.x / 2.f;
			y = scale.y / 2.f;
		}
		fxDest = x * cosTheta - y * sinTheta;
		fyDest = x * sinTheta + y * cosTheta;
		point[i].x = fxDest + center.x;
		point[i].y = fyDest + center.y;
	}


	HBITMAP alphaBit = CreateCompatibleBitmap(dc
		, Core::GetInstance()->GetResolution().x
		, Core::GetInstance()->GetResolution().y);
	HDC alphaDC = CreateCompatibleDC(dc);
	SelectObject(alphaDC, alphaBit);

	PatBlt(alphaDC, 0, 0
		, Core::GetInstance()->GetResolution().x
		, Core::GetInstance()->GetResolution().y, WHITENESS);

	TransparentBlt(alphaDC
		, (int)(pos.x - _vecAnimationFrame[_curFrame].vSlice.x / 2.f)
		, (int)(pos.y - _vecAnimationFrame[_curFrame].vSlice.y / 2.f)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.x)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.y)
		, _texture->GetDC()
		, (int)(_vecAnimationFrame[_curFrame].vLT.x)
		, (int)(_vecAnimationFrame[_curFrame].vLT.y)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.x)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.y)
		, RGB(255, 0, 255));

	PlgBlt(dc, point, alphaDC
		, (int)(pos.x - _vecAnimationFrame[_curFrame].vSlice.x / 2.f)
		, (int)(pos.y - _vecAnimationFrame[_curFrame].vSlice.y / 2.f)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.x)
		, (int)(_vecAnimationFrame[_curFrame].vSlice.y)
		, nullptr, 0, 0);

	DeleteDC(alphaDC);
	DeleteObject(alphaBit);
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
