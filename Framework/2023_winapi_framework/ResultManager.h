#pragma once
class ResultManager
{
	SINGLE(ResultManager);
public:
	void Init();
	void Update();
	void SetMonster() { ++_monsterScore; }
	void StopTime() { _playTime = false; }
private:
	int _maxTimeScore;
	int _maxMonsterScore;
	int _monsterScore;
	int _timeScore;
	bool _playTime;
};
