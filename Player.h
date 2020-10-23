#pragma once

#include <stack>
#include <queue>
#include <utility>
#include <vector>
#include <time.h>
#include "Maze.h"

using namespace std;

class Maze;

class Player
{
public:
	bool isFinish = false;
	int posY;
	int posX;
	int destY;
	int destX;

	int dy[4] = { -1,0,1,0 };
	int dx[4] = { 0,-1,0,1 };
	
	typedef struct PQNode
	{
		int F;
		int G;
		int Y;
		int X;
	}PQNode;

	struct compare
	{
		bool operator()(const PQNode& node1, const PQNode& node2)
		{
			return node1.F > node2.F;
		}
	};

	// Player.cpp
	void PlayerInitialize(int posY, int posX, int destY, int destX); // 플레이어의 출발지 좌표와 목적지 좌표 초기화
	vector<pair<int, int>> DFS(Maze& maze);
	vector<pair<int, int>> BFS(Maze &maze);
	vector<pair<int, int>> AStar(Maze& maze);
};