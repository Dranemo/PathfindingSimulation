#pragma once
#include <vector>


class Grid;
class Node;


class Algorithm
{
private:
	static Node* visitingNode;

	static std::vector<Node*> path;

	static void CalculatePath(Grid* grid);
	static void ShowPath();
	static void Reset();

public:
	static bool threadOn;

	static void DFS(Grid* grid);

	static void BFS(Grid* grid);

	static void Dijkstra(Grid* grid);
};

