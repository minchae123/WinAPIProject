#include "pch.h"
#include "Texture.h"
#include "Core.h"
#include<assert.h>
Texture::Texture()
	: _hBitMap(0)
	, _hDC(0)
	, _bitMapInfo{}
{
}

Texture::~Texture()
{
	DeleteDC(_hDC);
	DeleteObject(_hBitMap);
}

void Texture::Load(const wstring& filePath)
{
	_hBitMap = (HBITMAP)LoadImage(nullptr, filePath.c_str(), IMAGE_BITMAP
		, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	assert(_hBitMap);
	_hDC = CreateCompatibleDC(Core::GetInstance()->GetMainDC());
	SelectObject(_hDC, _hBitMap);
	GetObject(_hBitMap, sizeof(BITMAP),&_bitMapInfo);
}
