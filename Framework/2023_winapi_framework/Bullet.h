#pragma once
#include "Object.h"
#include "DebugManager.h"
class Texture;
class Bullet :
    public Object
{
public:
    Bullet();
    ~Bullet();
public:
    void Update() override;
    void Render(HDC _dc) override;
    void Reflect();
public:
    void SetDir(float _f) { _theta = _f; }
    void SetDir(Vector2 _vDir) 
    { 
        _dir = _vDir; 
        _dir.Normalize();
    }
    void SetSpeed(float speed) { _moveSpeed = speed; }
private:
//    float m_fDir; // 총알 방향(-1 위, 1 아래);
    float _theta; // 삼각함수 방향.
    float _moveSpeed;
    Vector2 _dir;
    Texture* _texture;
};

