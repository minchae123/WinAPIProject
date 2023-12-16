#include "pch.h"
#include "InfoManager.h"
#include "ResultManager.h"
#include "KeyMgr.h"
#include "ResMgr.h"

void InfoManager::Init()
{
	fHeart = ResourceManager::GetInstance()->TexLoad(L"FHeart", L"Texture\\Fheart.bmp");
	eHeart = ResourceManager::GetInstance()->TexLoad(L"EHeart", L"Texture\\Eheart.bmp");
	_surviveTime = 0;
}

void InfoManager::Update()
{
	_surviveTime = ResultManager::GetInstance()->GetTime();
}

void InfoManager::Render(HDC dc)
{
	RECT_RENDER(1100, 300, 300, 400, dc);
	int fontSize = 40; // ���ϴ� ��Ʈ ũ�� ����
	HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("��ɵ���ü"));

	// ��Ʈ�� ����̽� ���ؽ�Ʈ�� ����
	HFONT hOldFont = (HFONT)SelectObject(dc, hFont);

	wstring time = L"�����ð� : " + Text((int)_surviveTime);
	SetBkMode(dc, TRANSPARENT);
	SetTextColor(dc, RGB(0, 0, 0));
	TextOut(dc, 960, 300, time.c_str(), time.length());

	// ���� �ؽ�Ʈ ������
	int scoreI = ResultManager::GetInstance()->GetMonster();
	wstring score = L"���� : " + Text(scoreI);
	TextOut(dc, 960, 350, score.c_str(), score.length());

	hp = ResultManager::GetInstance()->GetHeart();
	for (int i = 0; i < hp; i++)
	{
		if (i < 3)
			TransparentBlt(dc, 937 + (i * 100), 110, 128, 128, fHeart->GetDC(), 0, 0, 128, 128, RGB(255, 0, 255));
		else
			TransparentBlt(dc, 937 + ((i - 3) * 100), 190, 128, 128, fHeart->GetDC(), 0, 0, 128, 128, RGB(255, 0, 255));
	}

	// ���� ��Ʈ�� ����
	SelectObject(dc, hOldFont);
	DeleteObject(hFont);
}
