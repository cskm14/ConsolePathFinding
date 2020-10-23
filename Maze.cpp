#include "Maze.h"

void Maze::GenerateMazeByBinaryTree()
{
	// 일단 길을 다 막아버리는 작업
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				board[y][x] = WALL;
			else
				board[y][x] = EMPTY;
		}
	}

	// 랜덤으로 오른쪽 또는 아래로 길을 뚫는 작업
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
				continue;

			if (y == SIZE - 2 && x == SIZE - 2)
				continue;

			if (y == SIZE - 2)
			{
				board[y][x + 1] = EMPTY;
				continue;
			}

			if (x == SIZE - 2)
			{
				board[y + 1][x] = EMPTY;
				continue;
			}

			if (rand() % 2 == 0)
				board[y][x + 1] = EMPTY;
			else
				board[y + 1][x] = EMPTY;

		}
	}
}

void Maze::MapInitialize()
{
	//srand((unsigned)time(NULL));
	GenerateMazeByBinaryTree();

	for (int i = 0; i < SIZE; i++)
		fill(visited[i], visited[i] + SIZE, false);
}

string Maze::GetTile(int y, int x)
{
	switch (board[y][x])
	{
	case EMPTY:
		return BLANK;
	case WALL:
		return SQUARE;
	default:
		return to_string(board[y][x]);
	}
}

void Maze::Render(Player& player) // 맵 렌더링하기
{
	ConsoleController consoleController;
	consoleController.SetCursorPosition(0, 0);

	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (player.posY == y && player.posX == x)
			{
				consoleController.SetConsoleTextColor(consoleController.GREEN);
				cout << CIRCLE;
				continue;
			}

			if (visited[y][x])
			{
				if (player.destY == y && player.destX == x)
				{
					consoleController.SetConsoleTextColor(consoleController.YELLOW);
					cout << STAR;
					player.isFinish = true;
					continue;
				}
				else
				{
					consoleController.SetConsoleTextColor(consoleController.AQUA);
					cout << MARKED;
					continue;
				}
			}

			if (player.destY == y && player.destX == x)
			{
				consoleController.SetConsoleTextColor(consoleController.RED);
				cout << HEART;
			}
			else
			{
				consoleController.SetConsoleTextColor(consoleController.WHITE);
				cout << GetTile(y, x);
			}
		}
		cout << endl;
	}
}

void Maze::RouteRender(Player& player, vector<pair<int, int>> &route)
{
	ConsoleController consoleController;
	consoleController.SetCursorPosition(0, 0);

	for (auto& pos : route)
	{
		board[pos.first][pos.second] = ROUTE;
	}

	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (board[y][x] == ROUTE)
			{
				if (player.destY == y && player.destX == x)
				{
					consoleController.SetConsoleTextColor(consoleController.YELLOW);
					cout << STAR;
					continue;
				}
				else if (player.posY == y && player.posX == x)
				{
					consoleController.SetConsoleTextColor(consoleController.GREEN);
					cout << CIRCLE;
					continue;
				}
				else
				{
					consoleController.SetConsoleTextColor(consoleController.RED);
					cout << MARKED;
					continue;
				}
			}

			if (visited[y][x])
			{
				consoleController.SetConsoleTextColor(consoleController.AQUA);
				cout << MARKED;
			}
			else
			{
				consoleController.SetConsoleTextColor(consoleController.WHITE);
				cout << GetTile(y, x);
			}
		}
		cout << endl;
	}
}

void Maze::MapClean()
{
	for (int i = 0; i < SIZE; i++)
		fill(visited[i], visited[i] + SIZE, false);

	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			if (board[y][x] == ROUTE)
				board[y][x] = EMPTY;
		}
	}
}