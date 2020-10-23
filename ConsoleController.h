#pragma once

#include <Windows.h>

class ConsoleController
{
public:
	enum { BLACK = 0, BLUE = 1, GREEN = 2, AQUA = 3, RED = 4, PURPLE = 5, YELLOW = 6, WHITE = 7, GRAY = 8 }; // 콘솔 텍스트 색상 enum값

	// ConsoleController.cpp
	void SetCursorPosition(SHORT x, SHORT y); // x,y 좌표 이동시키는 함수
	void ConsoleSize(); // 콘솔창 크기 조절
	void RemoveScrollbar(); // 콘솔창 스크롤바 삭제
	void RemoveCursor(); // 콘솔창 커서 제거
	void SetConsoleTextColor(int color); // 콘솔 텍스트 색상 변경
	void SetConsole(); // 콘솔창 세팅 함수 모음 (초기 세팅용)
};
