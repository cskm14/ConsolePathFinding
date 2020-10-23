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

	// 점수 매기기
	// F = G + H
	// F = 최종 점수 (작을 수록 좋음, 경로에 따라 달라짐)
	// G = 시작점에서 해당 좌표까지 이동하는데 드는 비용 (작을 수록 좋음, 경로에 따라 달라짐)
	// H = 목적지에서 얼마나 가까운지 (작을 수록 좋음, 고정값)

	// (y, x) 이미 방문했는지 여부 (방문 = closed 상태)
	bool closed[SIZE][SIZE]; // CloseList
	for (int i = 0; i < SIZE; i++)
		fill(closed[i], closed[i] + SIZE, false);

	// (y, x) 가는 길을 한 번이라도 발견했는지
	// 발견X => MaxValue
	// 발견O => F = G + H
	int open[SIZE][SIZE]; // OpenList
	for (int i = 0; i < SIZE; i++)
		fill(open[i], open[i] + SIZE, INT_MAX);

	// 오픈리스트에 있는 정보들 중에서, 가장 좋은 후보를 빠르게 뽑아오기 위한 우선순위 큐
	priority_queue<PQNode, vector<PQNode>, compare> pq;

	// 시작점 발견 (예약 진행)
	open[posY][posX] = abs(destY - posY) + abs(destX + posX);
	pq.push({ abs(destY - posY) + abs(destX + posX), 0, posY, posX });

	pair<int, int> prev[SIZE][SIZE];
	prev[posY][posX] = { posY, posX };
	
	while (pq.size() > 0)
	{
		// 제일 좋은 후보(F값이 가장 작은)를 찾는다
		PQNode node = pq.top(); pq.pop();
		// 동일한 좌표를 여러 경로로 찾아서, 더 빠른 경로로 인해서 이미 방문(closed)된 경우 스킵
		if (closed[node.Y][node.X])
			continue;

		// 방문한다
		closed[node.Y][node.X] = true;
		// 목적지 도착했으면 바로 종료
		if (node.Y == destY && node.X == destX)
			break;

		// 상하좌우 등 이동할 수 있는 좌표인지 확인해서 예약(open)한다
		for (int dir = 0; dir < 4; dir++)
		{
			int newY = node.Y + dy[dir];
			int newX = node.X + dx[dir];

			// 유효 범위를 벗어났으면 스킵
			if (newY < 0 || newY >= SIZE || newX < 0 || newX >= SIZE) continue;
			// 벽으로 막혀서 갈 수 없으면 스킵
			if (maze.board[newY][newX] == maze.WALL) continue;
			// 이미 방문한 곳이면 스킵
			if (closed[newY][newX]) continue;

			// 비용 계산
			int g = node.G + cost[dir];
			int h = abs(destY - newY) + abs(destX + newX);
			// 다른 경로에서 더 빠른 길 이미 찾았으면 스킵
			if (open[newY][newX] < g + h) continue;

			// 예약 진행
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