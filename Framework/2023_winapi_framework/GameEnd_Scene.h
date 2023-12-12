#pragma once
#include "Scene.h"
#include "Texture.h"
class GameEnd_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

private:
    Texture* backTex;
    Texture* selectTex;
    int num = 0;
    float x;
    float y = 395;
};

