#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{

	if (!this->render_Window.Initialize(this, hInstance, window_title, window_class, width, height))
		return false;

	if (!gfx.Initialize(this->render_Window.GetHWND(), width, height))
		return false;

	return true;
}

bool Engine::ProcessMessages()
{
	return this->render_Window.ProcessMessages();
}

void Engine::Update()
{
	while (!keyboard.CharBufferIsEmpty()) 
	{
		unsigned char ch = keyboard.ReadChar();
	}

	while (!keyboard.KeyBufferIsEmpty()) 
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}
	/*
	while (!mouse.EventBufferIsEmpty()) 
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::WheelUp)
		{
			OutputDebugStringA("MouseWheelUp \n");
		}
		if (me.GetType() == MouseEvent::EventType::WheelDown)
		{
			OutputDebugStringA("MouseWheelDown \n");
		}
	}*/
}
