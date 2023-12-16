#include "pch.h"
#include "ResultManager.h"
#include "TimeMgr.h"

void ResultManager::Init()
{
	_maxTimeScore		= 0;
	_maxMonsterScore	= 0;
	_monsterScore		= 0;
	_timeScore			= 0;
	heart = 6;
	_playTime			= true;
}

void ResultManager::Update()
{
	if (_monsterScore > _maxMonsterScore)
	{
 		_maxMonsterScore = _monsterScore;
	}

	if (_timeScore > _maxTimeScore)
	{
		_maxTimeScore = _timeScore;
	}

	if (_playTime)
	{
		_timeScore += DeltaTime;
	}

}
