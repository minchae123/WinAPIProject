#pragma once
#include "Scene.h"
class Menu_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC dc) override;
};

