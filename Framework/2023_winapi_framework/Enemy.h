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
    virtual void EnterCollision(Collider* other) override;
public:
    void ShootBullet();
protected:
    Texture* _texture;
    Texture* _hitTexture;
    float _time;
    float _spawnTime;
    float _hitTime;
    bool _hit;
};

