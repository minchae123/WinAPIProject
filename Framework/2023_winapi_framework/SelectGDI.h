#pragma once
class SelectGDI
{
public:
	SelectGDI(HDC dc, PEN_TYPE pen);
	SelectGDI(HDC dc, BRUSH_TYPE brush);
	SelectGDI(HDC dc, HFONT _font);
	~SelectGDI();
private:
	HDC		_hDC;
	HPEN	_hDefaultPen;
	HBRUSH	_hDefaultBrush;
	HFONT   _hDefaultFont;
	HFONT	_hFont;
};
