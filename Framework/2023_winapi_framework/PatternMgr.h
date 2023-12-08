#pragma once
class PatternMgr 
{
public: 
	SINGLE(PatternMgr);

public:
	void Init();
	void Update();

public: 
	void CreateBullet(float angle, Vector2 pos);    
	void CreateBullet(Vector2 dir, Vector2 pos);

public: // ���� ����
	void HeartPattern();
	void SpreadPattern(int count);
	void SquarePattern();

};