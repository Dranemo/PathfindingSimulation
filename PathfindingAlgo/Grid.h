#pragma once
#include "Node.h"
#include "WindowManager.h"
#include <vector>

class Grid
{
private:
	int rowsNum = WindowManager::windowSize.x / Node::sizeNode.x;
	int ColNums = WindowManager::windowSize.y / Node::sizeNode.y;

	Node* startNode = nullptr;
	Node* finishNode = nullptr;

	WindowManager* wm = nullptr; 

	bool mousePressed = false;
	Node* lastNodeStateChange = nullptr;
	bool movingStart = false;
	bool movingFinish = false;
	bool creatingWalls = false;


public:
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
};

