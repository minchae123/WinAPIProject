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
	int GetTime() const { return _timeScore; }
	int GetMonster() const { return _monsterScore; }
	int GetMaxMonster() const { return _maxMonsterScore; }
	int GetHeart() const { return heart; }
private:
	int _maxTimeScore;
	int _maxMonsterScore;
	int _monsterScore;
	int _timeScore;
	bool _playTime;
	int heart;
};
