#pragma once
#include "Object.h"
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
    void SetDir(float _f) { m_fTheta = _f; }
    void SetDir(Vector2 _vDir) 
    { 
        m_vDir = _vDir; 
        m_vDir.Normalize();
    }
private:
    float m_fTheta; // 삼각함수 방향.
    Vector2 m_vDir;
    Texture* m_pTex;
};

