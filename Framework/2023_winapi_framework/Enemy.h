#pragma once
#include "Object.h"
class Texture;
class Timer;
class Enemy :
    public Object
{
public:
    Enemy();
    ~Enemy();
public:
    void Update() override;
    void Render(HDC dc) override;
    void EndTimer(Timer* timer) override;
private:
    void ShootBullet();
private:
    Texture* _texture;
    float _moveSpeed;
};

