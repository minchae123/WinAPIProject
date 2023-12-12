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
	void CreateBullet(float angle, Vector2 pos, float speed = 0);
	void CreateBullet(Vector2 dir, Vector2 pos);
	Vector2 SpawnRandomPos();

public: // 패턴 종류
	void SpreadPattern(int count, Vector2 pos);
	void SquarePattern(Vector2 pos);
	void RhombPattern(Vector2 pos);
	void TrianglePattern(Vector2 pos);
	void HexagonPattern(Vector2 pos);
	void RandomPattern(int count, Vector2 pos);
	void SinPattern(Vector2 pos);
};

