#pragma once
#include "Scene.h"
#include "Texture.h"
class Intro_Scene :
    public Scene
{
public:
    Intro_Scene();
    ~Intro_Scene();
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

public:
    Texture* backTex;
    Texture* selectTex;
    Texture* infoTex;
    int num = 0;
    float x;
    float y = 395;
    bool info;
};

