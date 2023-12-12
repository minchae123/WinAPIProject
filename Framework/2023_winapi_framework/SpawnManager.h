#pragma once
class SpawnManager
{
	SINGLE(SpawnManager);
public:
	void Init();
	void Update();
	void Spawn();
	Vector2 SpawnPos();
private:
	float _time;
	float _spawnTime;
};

