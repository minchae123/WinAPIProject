#include "pch.h"
#include "PathMgr.h"
#include "Core.h"
void PathManager::Init()
{
	GetCurrentDirectory(255,_strResPath);
	wcscat_s(_strResPath, 255, L"\\Res\\");
	SetWindowText(Core::GetInstance()->GetHwnd(),_strResPath);
}
