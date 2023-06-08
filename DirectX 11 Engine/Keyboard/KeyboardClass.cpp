#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++) {
		this->keyStates[i] = false; //--������ ���ÿ� Ű��Ȱ��ȭ 
	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();//--keyBuffer�� ��������� true �ƴϸ� false ��ȯ
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();//--charBuffer�� ��������� true �ƴϸ� false ��ȯ
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if(this->keyBuffer.empty())	{
		return KeyboardEvent();//-- �о�� keyBuffer�� ������ Event�� �����Ѵ�.
	}
	else {
		KeyboardEvent e = this->keyBuffer.front();
		this->keyBuffer.pop();
		return e;
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (this->charBuffer.empty()) {
		return 0u; // return 0(NULL char)
	}
	else {
		unsigned char e = this->charBuffer.front();
		this->charBuffer.pop();
		return e;
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return this->autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return this->autoRepeatChars;
}
