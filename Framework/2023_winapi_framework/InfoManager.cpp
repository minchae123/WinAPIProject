#include "pch.h"
#include "InfoManager.h"
#include "ResultManager.h"
#include "ResMgr.h"

void InfoManager::Init()
{
	fHeart = ResourceManager::GetInstance()->TexLoad(L"FHeart", L"Texture\\Fheart.bmp");
	eHeart = ResourceManager::GetInstance()->TexLoad(L"EHeart", L"Texture\\Eheart.bmp");
}

void InfoManager::Render(HDC dc)
{
	RECT_RENDER(1100, 300, 300, 400, dc);
	int fontSize = 40; // 원하는 폰트 크기 선택
	HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Arial");

	// 폰트를 디바이스 컨텍스트에 선택
	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	// 시간 텍스트 렌더링
	int timeI = ResultManager::GetInstance()->GetTime();
	wstring time = L"생존시간 : " + Text(timeI);
	SetBkMode(dc, TRANSPARENT);
	SetTextColor(dc, RGB(0, 0, 0));
	TextOut(dc, 1000, 200, time.c_str(), time.length());

	// 점수 텍스트 렌더링
	int scoreI = ResultManager::GetInstance()->GetMonster();
	wstring score = L"처치한 적 : " + Text(scoreI);
	TextOut(dc, 1000, 250, score.c_str(), score.length());

	hp = ResultManager::GetInstance()->GetHeart();
	for (int i = 0; i < hp; i++)
	{
		TransparentBlt(dc, 800 + (i * 100), 150, 128, 128, fHeart->GetDC(), 0, 0, 128, 128, RGB(255, 0, 255));
	}

	// 이전 폰트로 복원
	SelectObject(dc, hOldFont);
	DeleteObject(hFont);
}
