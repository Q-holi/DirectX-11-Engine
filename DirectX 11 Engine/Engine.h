#pragma once
#include "WindowContainer.h"

using namespace std;

class Engine : WindowContainer
{
public:
	bool Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height);
	bool ProcessMessages();
	void Update();
};

