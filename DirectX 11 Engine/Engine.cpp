#include "Engine.h"

bool Engine::Initialize(HINSTANCE hInstance, string window_title, string window_class, int width, int height)
{
	return this->render_Window.Initialize(this,hInstance, window_title, window_class, width, height);
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
		string outmsg = "Char : ";
		outmsg += ch;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}

	while (!keyboard.KeyBufferIsEmpty()) 
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		string outmsg = "";
		if (kbe.IsPress())
		{
			outmsg = "Key Press : ";
		}
		if (kbe.IsRelease()) 
		{
			outmsg = "Key Release : ";
		}
		
		outmsg += keycode;
		outmsg += "\n";
		OutputDebugStringA(outmsg.c_str());
	}
}
