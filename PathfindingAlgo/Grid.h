#pragma once
#include "Node.h"
#include "WindowManager.h"
#include <vector>
#include <random>

class Grid
{
private:

	Node* startNode = nullptr;
	Node* finishNode = nullptr;

	WindowManager* wm = nullptr; 

	bool mousePressed = false;
	Node* lastNodeStateChange = nullptr;
	bool movingStart = false;
	bool movingFinish = false;
	bool creatingWalls = false;

	std::random_device rd;


public:
	int rowsNum = WindowManager::windowSize.x / Node::sizeNode.x;
	int ColNums = WindowManager::windowSize.y / Node::sizeNode.y;
	std::vector<std::vector<Node*>> grid;
	int speed = 50;

	Node* GetStartNode() { return startNode; }
	Node* GetFinishNode() { return finishNode; }

	void SetStartNode(int x, int y);
	void SetFinishNode(int x, int y);

	void ClearGrid();
	void ClearWall();
	void ClearGridVisited();

	void SetNeighbourNodes(Node* node);

	void SetNodeStateMouse(sf::Vector2i mousePos);
	void Update();

	Grid();

	void SpawnRandomWall();
	Node* GetRandomNeighborNode(Node* _node);

	void WilsonAlgorithm();
	Node* GetRandomNeighbor(Node* node);
};

