#include "pch.h"
#include "BaseWindow.h"
#include "Resource.h"
#include "Core.h"
BaseWindow::BaseWindow(POINT ptResolution)
	: _hWnd(0)
	, _instance(0)
    , _resolution(ptResolution)
{
}

BaseWindow::~BaseWindow()
{
}

int BaseWindow::Run(HINSTANCE hInst, LPWSTR lpCmdline, int nCmdShow)
{
    //this->m_hWnd;
    _instance = hInst;
    this->MyRegisterClass();
    this->WindowCreate();
    this->WindowShow(nCmdShow);
    this->WindowUpdate();
    // Init();
    if (!Core::GetInstance()->Init(_hWnd, _resolution))
    {
        MessageBox(_hWnd, L"Core 초기화 실패", L"FAIL", MB_OK);
    }
    return this->MessageLoop();
}

ATOM BaseWindow::MyRegisterClass()
{
    WNDCLASSEXW wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = BaseWindow::WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _instance;
    wcex.hIcon = LoadIcon(_instance, MAKEINTRESOURCE(IDI_MY2023WINAPIFRAMEWORK22));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = WINDOW_CLASS_NAME;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

void BaseWindow::WindowCreate()
{
    int iWinposx = GetSystemMetrics(SM_CXSCREEN) / 2 - _resolution.x / 2;
    int iWinposy = GetSystemMetrics(SM_CYSCREEN) / 2 - _resolution.y / 2;
    
    _hWnd = CreateWindowW(WINDOW_CLASS_NAME, L"Jun's Framework", WS_OVERLAPPEDWINDOW,
        iWinposx, iWinposy, _resolution.x, _resolution.y, nullptr, nullptr, _instance, nullptr);
    
    RECT rt = { iWinposx, iWinposy, iWinposx + _resolution.x, iWinposy + _resolution.y };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
    MoveWindow(_hWnd, iWinposx, iWinposy, rt.right - rt.left, rt.bottom - rt.top, true);
}

void BaseWindow::WindowShow(int nCmdShow)
{
    ShowWindow(_hWnd, nCmdShow);
}

void BaseWindow::WindowUpdate()
{
    UpdateWindow(_hWnd);
}

LRESULT BaseWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int BaseWindow::MessageLoop()
{
    MSG msg;
    // 기본 메시지 루프입니다:
    while (true)
    {
        // 어? 메시지 있네? 그럼 여기 ㅇㅋ
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // 어? 메시지 없음? ㅇㅋ 나 따로놈 게임함
            Core::GetInstance()->GameLoop();
        }
    }
    Core::GetInstance()->Release();
    return (int)msg.wParam;
}
