#pragma once
class ResultManager
{
	SINGLE(ResultManager);
public:
	void Init();
	void Update();
	void SetMonster() { ++_monsterScore; }
	void StopTime() { _playTime = false; }
	void HeartSet(int h) { heart = h; }
	float GetTime() const { return _timeScore; }
	int GetMonster() const { return _monsterScore; }
	int GetMaxMonster() const { return _maxMonsterScore; }
	int GetHeart() const { return heart; }
private:
	float _maxTimeScore;
	int _maxMonsterScore;
	int _monsterScore;
	float _timeScore;
	bool _playTime;
	int heart;
};
