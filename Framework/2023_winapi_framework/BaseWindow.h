#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT ptResolution);
	~BaseWindow();
	// 내가 이거는 꼭 멤버변수로 들고가야한다!
	// 1. 인스턴스, 윈도우 핸들
	int					Run(HINSTANCE hInst, LPWSTR lpCmdline, int nCmdShow);
	ATOM                MyRegisterClass();
//	BOOL                InitInstance(HINSTANCE, int);
	void				WindowCreate();
	void				WindowShow(int nCmdShow);
	void				WindowUpdate();
	static LRESULT CALLBACK    WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	int				    MessageLoop();
private:
	HWND		_hWnd;
	HINSTANCE	_instance;
	POINT		_resolution;
};

