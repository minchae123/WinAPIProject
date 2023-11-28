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

        for (int i = 0; i < 10; i++)
        {
            float angle = i;
            float radians = Deg2Rad(angle);
        
            float x = radius * cos(radians);
            float y = radius * sin(radians);
        
             // 계산된 방향으로 발사
            Vector2 direction = {cos(radians), sin(radians)};
        }


    }
}
