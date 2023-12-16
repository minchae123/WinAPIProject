#pragma once
#include "UI.h"
class Texture;
class Button :
    public UI
{
public:
    Button();
    ~Button();
public:
    virtual void Update() override;
    virtual void OnClick() override;
    virtual void Render(HDC dc) override;
private:
    bool CheckClick();
private:
    Texture* _texture;
};

