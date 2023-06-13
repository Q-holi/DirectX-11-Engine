#pragma once
#include "MouseEvent.h"
#include <queue>
//-- Ű���� Ŭ������ ���������� �̺�Ʈ ��⿭�� �����ϰ� �ֱ� ������ 

using namespace std;

class MouseClass
{
public:
	void OnLeftPressed(int x, int y);
	void OnLeftReleased(int x, int y);
	void OnRightPressed(int x, int y);
	void OnRightReleased(int x, int y);
	void OnMiddlePressed(int x, int y);
	void OnMiddleReleased(int x, int y);
	void OnWheelUp(int x, int y);
	void OnWheelDown(int x, int y);
	void OnMouseMove(int x, int y);

	bool IsLeftDown();
	bool IsMiddleDown();
	bool IsRightDown();

	int GetPosX();
	int GetPosY();
	MousePoint GetPos();

	bool EventBufferIsEmpty();
	MouseEvent ReadEvent();

private:
	queue<MouseEvent> eventBuffer;
	bool leftIsDown = false;
	bool rightIsDonw = false;
	bool mbuttonDown = false;
	int x = 0;
	int y = 0;

};
