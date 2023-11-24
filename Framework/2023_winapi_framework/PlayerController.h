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
private:
    void Move();
    void CreateBullet();
private:
    Texture* _texture;
    float _moveSpeed;
    Vector2 _rightVec;
};

