#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++) {
		this->keyStates[i] = false; //--생성과 동시에 키비활성화 
	}
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();//--keyBuffer가 비어있으면 true 아니면 false 반환
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();//--charBuffer가 비어있으면 true 아니면 false 반환
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if(this->keyBuffer.empty())	{
		return KeyboardEvent();//-- 읽어올 keyBuffer가 없으면 Event를 생성한다.
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
