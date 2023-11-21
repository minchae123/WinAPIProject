#pragma once
class BaseWindow
{
public:
	BaseWindow(POINT ptResolution);
	~BaseWindow();
	// ���� �̰Ŵ� �� ��������� ������Ѵ�!
	// 1. �ν��Ͻ�, ������ �ڵ�
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

