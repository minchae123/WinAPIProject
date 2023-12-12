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
	void CreateBullet(Vector2 dir, Vector2 pos, float speed);
	void CreateBullet(float angle, Vector2 pos);
	void CreateBullet(Vector2 dir, Vector2 pos);
	Vector2 SpawnRandomPos();

public: // 패턴 종류
	void SpreadPattern(int count, Vector2 pos); // 퍼지는 모양 갯수 설정
	void SquarePattern(Vector2 pos); // 상하좌우로 퍼짐
	void RhombPattern(Vector2 pos); // 사각형 모양으로
	void TrianglePattern(Vector2 pos); // 삼각형
	void HexagonPattern(Vector2 pos); // 육각형
	void RandomPattern(int count, Vector2 pos); // 랜덤 방향
	void HeartPattern(Vector2 pos); // 하트

	void RandomSelectPattern();
	
private:
	float time = 0;
};

