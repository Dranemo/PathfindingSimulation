#pragma once
#include <vector>


class Grid;
class Node;


class Algorithm
{
private:
	static Node* visitingNode;
	static bool isFinished;
	

	static std::vector<Node*> path;

	static void CalculatePath(Grid* grid);
	static void ShowPath();
	static void Reset();

	static int manhattan_distance(int x1, int y1, int x2, int y2) {
		return abs(x1 - x2) + abs(y1 - y2);
	}

public:
	static bool threadOn;
	static int speed;

	static void DFS(Grid* grid);

	static void BFS(Grid* grid);

	static void Dijkstra(Grid* grid);

	static void AStar(Grid* grid);

	static void GreedyBFS(Grid* grid);
};

