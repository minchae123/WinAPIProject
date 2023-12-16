#include "pch.h"
#include "Button.h"
#include "KeyMgr.h"
#include "DebugManager.h"

Button::Button()
	: _texture(nullptr)
{
}

Button::~Button()
{
}

void Button::Update()
{
	if (KEY_PRESS(KEY_TYPE::RBUTTON) && CheckClick())
	{
		OnClick();
	}
}

void Button::OnClick()
{
	DebugLog(L"¹öÆ° Å¬¸¯ µÊ");
}

void Button::Render(HDC dc)
{
	Vector2 pos = GetPos();
	Vector2 scale = GetScale();
	wstring text = GetText();

	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, dc);
	TextOut(dc, pos.x, pos.y, text.c_str(), text.size());
}

bool Button::CheckClick()
{
	Vector2 mousePos = KeyManager::GetInstance()->GetMousePos();

	Vector2 pos = GetPos();
	Vector2 scale = GetScale();
	Vector2 minPos = { pos.x - scale.x, pos.y - scale.y };
	Vector2 maxPos = { pos.x + scale.x, pos.y + scale.y };

	if (mousePos.x >= minPos.x &&
		mousePos.x <= maxPos.x &&
		mousePos.y >= minPos.y &&
		mousePos.y <= maxPos.y)
	{
		return true;
	}
	return false;
}
