#pragma once
class SpawnManager
{
	SINGLE(SpawnManager);
public:
	void Update();
	void Spawn();
	Vector2 SpawnPos();
};

