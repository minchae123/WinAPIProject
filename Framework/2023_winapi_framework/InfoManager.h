#pragma once
#include "Texture.h"
class InfoManager
{
	SINGLE(InfoManager);
public:
	void Init();
	void Update();
	void Render(HDC dc);
private:
	Texture* fHeart;
	Texture* eHeart;
	int hp;
	float _surviveTime;
};

