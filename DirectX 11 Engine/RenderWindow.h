#pragma once
#include "ErrorLogger.h"

using namespace std;

class WindowContainer;

class RenderWindow
{
public:
	bool Initialize(WindowContainer * pWindowContainer, HINSTANCE hInstance, string window_title, string window_class, int width, int height);
	bool ProcessMessages();
	~RenderWindow();

private:
	void RegisterWindowClass();
	HWND handle = NULL; // ������ �ڵ鷯 
	HINSTANCE hInstance = NULL;
	string window_title = "";
	wstring window_title_wide = L"";
	string window_class = "";
	wstring window_class_wide = L"";
	int width = 0;
	int height = 0;
};

