#pragma once
class LevelManager
{
	SINGLE(LevelManager);
public:
	void Init(int enemyHP, float bulletSpeed, int bulletHP);
public:
	int		GetEnemyHP() { return _enemyHP; }
	float	GetBulletSpeed() { return _bulletSpeed; }
	int		GetBulletHP() { return _bulletHP; }
private:
	int _enemyHP;
	float _bulletSpeed;
	int _bulletHP;
};

