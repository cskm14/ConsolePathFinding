#pragma once

#include <Windows.h>

class ConsoleController
{
public:
	enum { BLACK = 0, BLUE = 1, GREEN = 2, AQUA = 3, RED = 4, PURPLE = 5, YELLOW = 6, WHITE = 7, GRAY = 8 }; // �ܼ� �ؽ�Ʈ ���� enum��

	// ConsoleController.cpp
	void SetCursorPosition(SHORT x, SHORT y); // x,y ��ǥ �̵���Ű�� �Լ�
	void ConsoleSize(); // �ܼ�â ũ�� ����
	void RemoveScrollbar(); // �ܼ�â ��ũ�ѹ� ����
	void RemoveCursor(); // �ܼ�â Ŀ�� ����
	void SetConsoleTextColor(int color); // �ܼ� �ؽ�Ʈ ���� ����
	void SetConsole(); // �ܼ�â ���� �Լ� ���� (�ʱ� ���ÿ�)
};
