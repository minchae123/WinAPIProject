#include "pch.h"
#include "SelectGDI.h"
#include "Core.h"
SelectGDI::SelectGDI(HDC dc, PEN_TYPE pen)
	: _hDC(dc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HPEN hColorPen = Core::GetInstance()->GetPen(pen);
	_hDefaultPen = (HPEN)SelectObject(dc, hColorPen);
}

SelectGDI::SelectGDI(HDC dc, BRUSH_TYPE brush)
	: _hDC(dc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	HBRUSH hColorBrush = Core::GetInstance()->GetBrush(brush);
	_hDefaultBrush = (HBRUSH)SelectObject(dc, hColorBrush);
}

SelectGDI::SelectGDI(HDC _dc, HFONT _font)
	: _hDC(_dc)
	, _hDefaultBrush(nullptr)
	, _hDefaultPen(nullptr)
	, _hDefaultFont(nullptr)
	, _hFont(nullptr)
{
	_hFont = _font;
	_hDefaultFont = (HFONT)SelectObject(_dc, _hFont);
}

SelectGDI::~SelectGDI()
{
	SelectObject(_hDC, _hDefaultPen);
	SelectObject(_hDC, _hDefaultBrush);
	SelectObject(_hDC, _hDefaultFont);
	if (nullptr != _hFont)
		DeleteObject(_hFont);
}
