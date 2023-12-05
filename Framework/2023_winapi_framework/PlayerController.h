#pragma once
#include "Object.h"
class Texture;
class PlayerController :
    public Object
{
public:
    PlayerController();
    ~PlayerController();
public:
    void Update() override;
    void Render(HDC dc) override;
    void EndTimer(Timer* timer) override;
private:
    void Move();
    void ShootBullet();
private:
    Texture* _texture;
    float _moveSpeed;
};

