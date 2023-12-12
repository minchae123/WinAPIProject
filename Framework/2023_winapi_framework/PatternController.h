#pragma once
#include "Object.h"
class PatternController :
    public Object
{
	SINGLE(PatternController);

public:
	void Init();
	void Update();

public:
	void CreateBullet(float angle, Vector2 pos);
	void CreateBullet(Vector2 dir, Vector2 pos);
	Vector2 SpanwRandomPos();

public: // 패턴 종류
	void HeartPattern();
	void SpreadPattern(int count);
	void SquarePattern(Vector2 pos);
};

