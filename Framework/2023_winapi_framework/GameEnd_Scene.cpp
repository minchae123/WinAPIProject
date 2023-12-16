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
	case 0: // ���� �ٽ� ����
	{
		y = 555;
	}
	break;
	case 1: // ���� ����
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
		case 0: // ���� �ٽ� ����
		{
			SceneManager::GetInstance()->LoadScene(L"Start_Scene");
		}
		break;
		case 1: // ���� ����
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

	int fontSize = 70; // ���ϴ� ��Ʈ ũ�� ����
	HFONT hFont = CreateFont(fontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, L"��ɵ���ü");

	// ��Ʈ�� ����̽� ���ؽ�Ʈ�� ����
	HFONT hOldFont = (HFONT)SelectObject(_dc, hFont);

	// �ð� �ؽ�Ʈ ������
	int timeI = ResultManager::GetInstance()->GetTime();
	wstring time = L"�����ð� : " + Text(timeI);
	SetBkMode(_dc, TRANSPARENT);
	SetTextColor(_dc, RGB(255, 255, 255));
	TextOut(_dc, 300, 300, time.c_str(), time.length());

	// ���� �ؽ�Ʈ ������
	int scoreI = ResultManager::GetInstance()->GetMonster();
	wstring score = L"óġ�� �� : " + Text(scoreI);
	TextOut(_dc, 300, 400, score.c_str(), score.length());

	// ���� ��Ʈ�� ����
	SelectObject(_dc, hOldFont);
	DeleteObject(hFont);
}

void GameEnd_Scene::Release()
{

}
