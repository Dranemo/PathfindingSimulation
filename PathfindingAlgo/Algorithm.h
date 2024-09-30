#pragma once
#include <vector>

class Grid;
class Node;


class Algorithm
{
private:
	static std::vector<Node*> serchingQueue;
	static Node* visitingNode;

	static std::vector<Node*> path;

	static std::vector<Node*> walls;
	static void GetWalls(Grid* grid);

	static void CalculatePath(Grid* grid);
	static void ShowPath();
	static void Reset();

public:
	static bool threadOn;

	static void DFS(Grid* grid);

	static void BFS(Grid* grid);
};

