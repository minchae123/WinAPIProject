#include "pch.h"
#include "LevelManager.h"

void LevelManager::Init(int enemyHP, float bulletSpeed, int bulletHP)
{
	_enemyHP = enemyHP;
	_bulletHP = bulletHP;
	_bulletSpeed = bulletSpeed;
}
