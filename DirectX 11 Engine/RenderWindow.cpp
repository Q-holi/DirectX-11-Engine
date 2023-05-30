#include "RenderWindow.h"

bool RenderWindow::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class);

	this->RegisterWindowClass();

	this->handle = CreateWindowEx(0,
		this->window_class_wide.c_str(),
		this->window_title_wide.c_str(),
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0,//--x좌표
		0,//--y좌표
		this->width,
		this->height,
		NULL,
		NULL,
		this->hInstance,
		nullptr);

	if (this->handle == NULL) 
	{
		ErrorLogger::Log(GetLastError(), "CreateWindowEX Failed For Window : " + this->window_title);
		return false;
	}

	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);


	return false;
}

bool RenderWindow::ProcessMessages()
{
	//-- 윈도우 메세지 
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	if (PeekMessage(&msg, this->handle, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//-- 윈도우 핸들러가 닫혔을 경우 
	if (msg.message == WM_NULL) {
		if (!IsWindow(this->handle)) {
			this->handle = NULL;
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}
	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL) {
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

void RenderWindow::RegisterWindowClass()
{
	WNDCLASSEX wc;
	// 윈도우 클래스를 기본 설정으로
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = DefWindowProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = this->hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = this->window_class_wide.c_str();
	wc.cbSize = sizeof(WNDCLASSEX);
	RegisterClassEx(&wc);
}
