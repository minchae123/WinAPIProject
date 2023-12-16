#include "pch.h"
#include "Menu_Scene.h"
#include "Button.h"
#include "DebugManager.h"

Button* newButton = new Button;
void Menu_Scene::Init()
{
	newButton->SetPos({ 300, 300 });
	newButton->SetScale({ 100, 100 });
	newButton->SetText(L"dddd");
}

void Menu_Scene::Update()
{
}

void Menu_Scene::Render(HDC dc)
{
	DebugManager::GetInstance()->Render(dc);
	newButton->Render(dc);
}
