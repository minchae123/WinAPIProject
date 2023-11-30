#pragma once
#include "Object.h"
class Texture;
class Enemy :
    public Object
{
public:
    Enemy();
    ~Enemy();
public:
    void Update() override;
    void Render(HDC dc) override;
private:
    void Move();
    void ShootBullet();
private:
    Texture* _texture;
    float _moveSpeed;
};

