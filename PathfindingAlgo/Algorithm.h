#pragma once
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>
#include <queue>

class Grid;
class Node;


class Algorithm
{
private:
	static std::vector<Node*> serchingQueue;
	static Node* visitingNode;

	static std::vector<Node*> path;

	static void CalculatePath(Grid* grid);
	static void ShowPath();
	static void Reset();

public:
	static bool threadOn;
	static int speed;

	static void DFS(Grid* grid);

	static void BFS(Grid* grid);

	static void Dijkstra(Grid* grid);
};

