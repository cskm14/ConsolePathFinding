#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include "Player.h"
#include "ConsoleController.h"

#define SIZE 27  // Ȧ��

using namespace std;

class Player;
class Maze
{
public:
	int board[SIZE][SIZE]; // ��(�̷�)�� ��Ÿ���� �迭
	bool visited[SIZE][SIZE]; // BFS�� �湮�� ��ǥ ������ ���� �迭
	
	enum { EMPTY = 0, WALL = 1, ROUTE = 2 }; // board �迭�� ������ ���� enum��

	const string BLANK = "  ";
	const string SQUARE = "��";
	const string MARKED = "��";
	const string CIRCLE = "��";
	const string HEART = "��";
	const string STAR = "��";

	void GenerateMazeByBinaryTree(); // BinaryTree �̷� ���� �˰���
	void MapInitialize(); // �� �ʱ�ȭ
	string GetTile(int y, int x); // Ư�� ��ǥ Ÿ�� ����(enum��) ���ϱ�
	void Render(Player &player); // �� ������
	void RouteRender(Player &player, vector<pair<int, int>> &route); // ���� ��� + �� ������
	void MapClean();
};
