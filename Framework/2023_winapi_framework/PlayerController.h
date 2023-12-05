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
    virtual void EnterCollision(Collider* other) override;
    virtual void ExitCollision(Collider* other) override;
    virtual void StayCollision(Collider* other) override;
private:
    void Move();
    void ShootBullet();
private:
    Texture* _texture;
    float _moveSpeed;
};

