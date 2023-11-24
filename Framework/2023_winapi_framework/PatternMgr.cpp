#include "pch.h"
#include "PatternMgr.h"
#include "define.h"
void PatternMgr::Init()
{
    HeartPattern();
}
void PatternMgr::Update()
{
}
void PatternMgr::HeartPattern()
{
    for (int i = 0; i < 360; i += 10)
    {
        float angle = Deg2Rad(i);
        float x = sin(angle) * sin(angle) * sin(angle);
        float y = cos(angle) * cos(angle) * cos(angle);
        Vector2 dir = { x,y };
        int a = 0;
    }
}
