#pragma once
#include "Res.h"
class Texture :
    public Res
{
private:
    Texture();
    ~Texture();
    friend class ResourceManager;
public:
    void Load(const wstring& filePath);
    const LONG& GetWidth() const { return (_bitMapInfo.bmWidth); }
    const LONG& GetHeight() const { return (_bitMapInfo.bmHeight); }
    const HDC& GetDC() const { return _hDC; }
private:
    HBITMAP _hBitMap;
    HDC     _hDC;
    BITMAP  _bitMapInfo;
};

