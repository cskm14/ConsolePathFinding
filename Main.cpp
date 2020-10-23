#include "pathFinding.h"

int main()
{
    ConsoleController consoleController;
    Maze maze;

    maze.MapInitialize();
    while (true)
    {
        Player player;
        vector<pair<int, int>> route;

        player.PlayerInitialize(1, 1, 1, SIZE - 2);
        consoleController.SetConsole();

        cout << "Select algorithm" << endl;
        cout << "1. DFS" << endl << "2. BFS" << endl << "3. AStar" << endl << "☞  ";
        int mode; cin >> mode;

        clock_t start = clock();
        switch (mode)
        {
        case 1:
            route = player.DFS(maze);
            break;
        case 2:
            route = player.BFS(maze);
            break;
        case 3:
            route = player.AStar(maze);
            break;
        default:
            return 0;
        }
        clock_t end = clock();
        cout << "Time : " << (double)(end - start) / CLOCKS_PER_SEC << endl;

        Sleep(1000);
        maze.RouteRender(player, route);
        
        Sleep(2000);
        maze.MapClean();
    }
    
}
