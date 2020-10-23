#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include "Player.h"
#include "ConsoleController.h"

#define SIZE 27  // 홀수

using namespace std;

class Player;
class Maze
{
public:
	int board[SIZE][SIZE]; // 맵(미로)을 나타내는 배열
	bool visited[SIZE][SIZE]; // BFS시 방문한 좌표 정보를 담은 배열
	
	enum { EMPTY = 0, WALL = 1, ROUTE = 2 }; // board 배열의 값으로 쓰일 enum값

	const string BLANK = "  ";
	const string SQUARE = "■";
	const string MARKED = "▦";
	const string CIRCLE = "●";
	const string HEART = "♥";
	const string STAR = "★";

	void GenerateMazeByBinaryTree(); // BinaryTree 미로 생성 알고리즘
	void MapInitialize(); // 맵 초기화
	string GetTile(int y, int x); // 특정 좌표 타일 색상(enum값) 구하기
	void Render(Player &player); // 맵 렌더링
	void RouteRender(Player &player, vector<pair<int, int>> &route); // 최종 경로 + 맵 렌더링
	void MapClean();
};
