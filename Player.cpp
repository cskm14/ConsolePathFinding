#include "Player.h"

void Player::PlayerInitialize(int posY, int posX, int destY, int destX)
{
	this->posY = posY;
	this->posX = posX;
	this->destY = destY;
	this->destX = destX;
}

vector<pair<int, int>> Player::DFS(Maze& maze)
{
	stack<pair<int, int>> st;
	st.push({ this->posY, this->posX });
	maze.visited[this->posY][this->posX] = true;

	pair<int, int> prev[SIZE][SIZE];
	prev[posY][posX] = { posY, posX };

	while (!st.empty())
	{
		auto cur = st.top(); st.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = cur.first + dy[dir];
			int newX = cur.second + dx[dir];
			if (newY < 0 || newY >= SIZE || newX < 0 || newX >= SIZE) continue;
			if (maze.board[newY][newX] == maze.WALL) continue;
			if (maze.visited[newY][newX]) continue;

			st.push({ newY, newX });
			maze.visited[newY][newX] = true;
			prev[newY][newX] = { cur.first, cur.second };
		}

		maze.Render(*this);

		if (isFinish) break;
	}

	int y = destY;
	int x = destX;
	vector<pair<int, int>> route;
	while (prev[y][x].first != y || prev[y][x].second != x)
	{
		route.push_back({ y, x });
		auto pos = prev[y][x];
		y = pos.first;
		x = pos.second;
	}
	route.push_back({ y,x });
	reverse(route.begin(), route.end());

	return route;
}

vector<pair<int, int>> Player::BFS(Maze &maze)
{
	queue<pair<int, int>> q;
	q.push({this->posY, this->posX});
	maze.visited[this->posY][this->posX] = true;

	pair<int, int> prev[SIZE][SIZE];
	prev[posY][posX] = { posY, posX };

	while (!q.empty())
	{
		auto cur = q.front(); q.pop();
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = cur.first + dy[dir];
			int newX = cur.second + dx[dir];
			if (newY < 0 || newY >= SIZE || newX < 0 || newX >= SIZE) continue;
			if (maze.board[newY][newX] == maze.WALL) continue;
			if (maze.visited[newY][newX]) continue;

			q.push({ newY, newX });
			maze.visited[newY][newX] = true;
			prev[newY][newX] = { cur.first, cur.second };
		}

		maze.Render(*this);

		if (isFinish) break;
	}

	int y = destY;
	int x = destX;
	vector<pair<int, int>> route;
	while (prev[y][x].first != y || prev[y][x].second != x)
	{
		route.push_back({ y, x });
		auto pos = prev[y][x];
		y = pos.first;
		x = pos.second;
	}
	route.push_back({ y,x });
	reverse(route.begin(), route.end());

	return route;
}

vector<pair<int, int>> Player::AStar(Maze& maze)
{
	int cost[4] = { 1,1,1,1 };

	// ���� �ű��
	// F = G + H
	// F = ���� ���� (���� ���� ����, ��ο� ���� �޶���)
	// G = ���������� �ش� ��ǥ���� �̵��ϴµ� ��� ��� (���� ���� ����, ��ο� ���� �޶���)
	// H = ���������� �󸶳� ������� (���� ���� ����, ������)

	// (y, x) �̹� �湮�ߴ��� ���� (�湮 = closed ����)
	bool closed[SIZE][SIZE]; // CloseList
	for (int i = 0; i < SIZE; i++)
		fill(closed[i], closed[i] + SIZE, false);

	// (y, x) ���� ���� �� ���̶� �߰��ߴ���
	// �߰�X => MaxValue
	// �߰�O => F = G + H
	int open[SIZE][SIZE]; // OpenList
	for (int i = 0; i < SIZE; i++)
		fill(open[i], open[i] + SIZE, INT_MAX);

	// ���¸���Ʈ�� �ִ� ������ �߿���, ���� ���� �ĺ��� ������ �̾ƿ��� ���� �켱���� ť
	priority_queue<PQNode, vector<PQNode>, compare> pq;

	// ������ �߰� (���� ����)
	open[posY][posX] = abs(destY - posY) + abs(destX + posX);
	pq.push({ abs(destY - posY) + abs(destX + posX), 0, posY, posX });

	pair<int, int> prev[SIZE][SIZE];
	prev[posY][posX] = { posY, posX };
	
	while (pq.size() > 0)
	{
		// ���� ���� �ĺ�(F���� ���� ����)�� ã�´�
		PQNode node = pq.top(); pq.pop();
		// ������ ��ǥ�� ���� ��η� ã�Ƽ�, �� ���� ��η� ���ؼ� �̹� �湮(closed)�� ��� ��ŵ
		if (closed[node.Y][node.X])
			continue;

		// �湮�Ѵ�
		closed[node.Y][node.X] = true;
		// ������ ���������� �ٷ� ����
		if (node.Y == destY && node.X == destX)
			break;

		// �����¿� �� �̵��� �� �ִ� ��ǥ���� Ȯ���ؼ� ����(open)�Ѵ�
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = node.Y + dy[dir];
			int newX = node.X + dx[dir];

			// ��ȿ ������ ������� ��ŵ
			if (newY < 0 || newY >= SIZE || newX < 0 || newX >= SIZE) continue;
			// ������ ������ �� �� ������ ��ŵ
			if (maze.board[newY][newX] == maze.WALL) continue;
			// �̹� �湮�� ���̸� ��ŵ
			if (closed[newY][newX]) continue;

			// ��� ���
			int g = node.G + cost[dir];
			int h = abs(destY - newY) + abs(destX + newX);
			// �ٸ� ��ο��� �� ���� �� �̹� ã������ ��ŵ
			if (open[newY][newX] < g + h) continue;

			// ���� ����
			open[newY][newX] = g + h;
			pq.push({ g + h, g, newY, newX });
			prev[newY][newX] = { node.Y, node.X };
			

			maze.visited[newY][newX] = true;
		}

		maze.Render(*this);

		if (isFinish) break;
	}

	int y = destY;
	int x = destX;
	vector<pair<int, int>> route;
	while (prev[y][x].first != y || prev[y][x].second != x)
	{
		route.push_back({ y, x });
		auto pos = prev[y][x];
		y = pos.first;
		x = pos.second;
	}
	route.push_back({ y,x });
	reverse(route.begin(), route.end());

	return route;
}