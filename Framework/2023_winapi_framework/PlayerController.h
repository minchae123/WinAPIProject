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
    void Damage();
private:
    Texture* _texture;
    Texture* _hitTexture;
    float _moveSpeed;
    float _time;
    bool _hit;
};

