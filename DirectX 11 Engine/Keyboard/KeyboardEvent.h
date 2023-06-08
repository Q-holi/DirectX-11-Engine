#pragma once
class KeyboardEvent
{
public:
	enum EventType {
		Press,//-- 플레이어가 키를 누루는 경우
		Release,//-- 플레이어가 키를 때는 경우
		Invalid//--키 이벤트가유효하지 않을 경우
	};
	KeyboardEvent();
	KeyboardEvent(const EventType type, const unsigned char key);
	bool IsPress() const;
	bool IsRelease() const;
	bool IsValid() const;
	unsigned char GetKeyCode() const;

private:
	EventType type;
	unsigned char key;
};

