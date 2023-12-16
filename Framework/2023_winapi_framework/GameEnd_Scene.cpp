#include "pch.h"
#include "GameEnd_Scene.h"
#include "SceneMgr.h"
#include "KeyMgr.h"
#include "ResMgr.h"
#include "ResultManager.h"

void GameEnd_Scene::Init()
{
	backTex = ResourceManager::GetInstance()->TexLoad(L"EBG", L"Texture\\EndBack.bmp");
	selectTex = ResourceManager::GetInstance()->TexLoad(L"Select", L"Texture\\Select.bmp");
	ResourceManager::GetInstance()->Pause(SOUND_CHANNEL::BGM, true);
}

void GameEnd_Scene::Update()
{
	Scene::Update();

	if (KEY_DOWN(KEY_TYPE::UP))
	{
		num--;
	}
	if (KEY_DOWN(KEY_TYPE::DOWN))
	{
		num++;
	}

	num = std::clamp(num, 0, 1);

	switch (num)
	{
	case 0: // 게임 다시 시작
	{
		y = 555;
	}
	break;
	case 1: // 게임 종료
	{
		y = 640;
	}
	break;
	default:
		break;
	}

	if (KEY_DOWN(KEY_TYPE::ENTER))
	{
		switch (num)
		{
		case 0: // 게임 다시 시작
		{
			SceneManager::GetInstance()->LoadScene(L"Start_Scene");
		}
		break;
		case 1: // 게임 종료
		{
			PostQuitMessage(0);
		}
		break;
		default:
			break;
		}
	}
}

void GameEnd_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
	BitBlt(_dc, (int)(0), (int)(-50), 1280, 780, backTex->GetDC(), 0, 0, SRCCOPY);
	TransparentBlt(_dc, 400, y, 64, 64, selectTex->GetDC(), 0, 0, 64, 64, RGB(255, 255, 255));

	int fontSize = 70; // 원하는 폰트 크기 선택
	HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"고령딸기체");

	// 폰트를 디바이스 컨텍스트에 선택
	HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);

	// 시간 텍스트 렌더링
	int timeI = ResultManager::GetInstance()->GetTime();
	wstring time = L"생존시간 : " + Text(timeI);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, 300, 300, time.c_str(), time.length());

	// 점수 텍스트 렌더링
	int scoreI = ResultManager::GetInstance()->GetMonster();
	wstring score = L"처치한 적 : " + Text(scoreI);
	TextOut(_dc, 300, 400, score.c_str(), score.length());

	// 이전 폰트로 복원
	SelectObject(_dc, hOldFont);
	DeleteObject(hFont);
}

void GameEnd_Scene::Release()
{

}
