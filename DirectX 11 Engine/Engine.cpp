#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{
	return this->render_Window.Initialize(this,hInstance, window_title, window_class, width, height);
}

bool Engine::ProcessMessages()
{
	return this->render_Window.ProcessMessages();
}
