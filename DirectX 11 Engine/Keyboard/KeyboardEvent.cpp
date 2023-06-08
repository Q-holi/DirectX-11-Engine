#include "KeyboardEvent.h"

KeyboardEvent::KeyboardEvent()
	:
	type(EventType::Invalid),
	key(0u)
{
 }

KeyboardEvent::KeyboardEvent(const EventType type, const unsigned char key)
	:
	type(type),
	key(key)
{
}

//--return this->type == EventType::Press; 이런 형태의 return은 ture 또는 false를 반활할때 효과적임
bool KeyboardEvent::IsPress() const
{
	return this->type == EventType::Press;
}

bool KeyboardEvent::IsRelease() const
{
	return this->type == EventType::Release;
}

bool KeyboardEvent::IsValid() const
{
	return this->type == EventType::Invalid;
}

unsigned char KeyboardEvent::GetKeyCode() const
{
	return this->key;
}
