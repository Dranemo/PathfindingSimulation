#include "Grid.h"
#include "Algorithm.h"
#include "InputManager.h"

#include <thread>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

Grid::Grid() {
	wm = WindowManager::GetInstance();

	grid.resize(rowsNum, std::vector<Node*>(ColNums, nullptr));

	for (int i = 0; i < rowsNum; i++) {
		for (int ii = 0; ii < ColNums; ii++) {
			grid[i][ii] = new Node(i, ii);
			wm->AddDrawable(grid[i][ii]->square);

			if (i == 1 && ii == 1) {
				startNode = grid[i][ii];
				startNode->SetState(Node::start);
			}
			if (i == rowsNum - 2 && ii == ColNums - 2) {
				finishNode = grid[i][ii];
				finishNode->SetState(Node::finish);
			}

		}
	}


	for (int i = 1; i < rowsNum; i++) {
		wm->AddLine(sf::Vector2f(i * Node::sizeNode.x, 0), sf::Vector2f(i * Node::sizeNode.x, ColNums * Node::sizeNode.x));  // Lignes verticales
	}
	for (int i = 1; i < ColNums; i++) {
		wm->AddLine(sf::Vector2f(0, i * Node::sizeNode.y), sf::Vector2f(rowsNum * Node::sizeNode.y, i * Node::sizeNode.y));  // Lignes horizontales
	}
}


void Grid::SetStartNode(int x, int y) {
	startNode->SetState(Node::defaultState);
	startNode = grid[x][y];
	startNode->SetState(Node::start);
}

void Grid::SetFinishNode(int x, int y) {
	finishNode->SetState(Node::defaultState);
	finishNode = grid[x][y];
	finishNode->SetState(Node::finish);
}



void Grid::ClearGrid() {
	for (std::vector<Node*> v : grid) {
		for (Node* n : v) {
			n->visited = false;
			n->SetState(Node::defaultState);

			n->GetChilds()->clear();
			n->SetParent(nullptr);
		}
	}

	startNode->SetState(Node::start);
	SetStartNode(1, 1);
	finishNode->SetState(Node::finish);
	SetFinishNode(rowsNum - 2, ColNums - 2);
}

void Grid::ClearWall() {
	for (std::vector<Node*> v : grid) {
		for (Node* n : v) {
			if (n->GetState() == Node::wall) {
				n->SetState(Node::defaultState);
			}
			n->visited = false;
			n->GetChilds()->clear();
			n->SetParent(nullptr);
		}
	}
}

void Grid::ClearGridVisited() {
	for (std::vector<Node*> v : grid) {
		for (Node* n : v) {
			n->visited = false;
			if(n->GetState() == Node::path)
				n->SetState(Node::defaultState);

			n->GetChilds()->clear();
			n->SetParent(nullptr);
		}
	}
}


void Grid::Update() {
	if(InputManager::GetMousePressed())
		mousePressed = true;
	else{
		mousePressed = false;

		movingStart = false;
		movingFinish = false;
		creatingWalls = false;

		lastNodeStateChange = nullptr;
	}

	if (Algorithm::threadOn == false) {
		if (mousePressed) {
			SetNodeStateMouse(sf::Mouse::getPosition(wm->window));
		}

		else if (InputManager::GetEvent(sf::Keyboard::A)) {

			mousePressed = false;

			movingStart = false;
			movingFinish = false;
			creatingWalls = false;

			lastNodeStateChange = nullptr;

			ClearGridVisited();

			std::thread t(&Algorithm::AStar, this);
			t.detach(); 
		}

	else if (InputManager::GetEvent(sf::Keyboard::G)) {

		mousePressed = false;

		movingStart = false;
		movingFinish = false;
		creatingWalls = false;

		lastNodeStateChange = nullptr;

		ClearGridVisited();

		std::thread t(&Algorithm::GreedyBFS, this);
		t.detach();
	}
}


	


	for (int i = 0; i < WindowManager::windowSize.y / Node::sizeNode.y; i++) {
		for (int j = 0; j < WindowManager::windowSize.x / Node::sizeNode.x; j++) {
			grid[i][j]->Update();
		}
	}
}


void Grid::SetNodeStateMouse(sf::Vector2i mousePos) {
	if (mousePos.x > 0 && mousePos.x < WindowManager::windowSize.x && mousePos.y > 0 && mousePos.y < WindowManager::windowSize.y) {
		sf::Vector2i NodePos = sf::Vector2i(mousePos.x / Node::sizeNode.x, mousePos.y / Node::sizeNode.y);


		Node* nodeConcerned = grid[NodePos.x][NodePos.y];


		if (nodeConcerned->GetState() == Node::start && !movingFinish && !creatingWalls) {
			movingStart = true;
		}
		else if (nodeConcerned->GetState() == Node::finish && !movingStart && !creatingWalls) {
			movingFinish = true;
		}
		else
			creatingWalls = true;




		if (lastNodeStateChange != nodeConcerned) {

			if (movingStart && nodeConcerned->GetState() != Node::start) {
				SetStartNode(nodeConcerned->positionInMatrice.x, nodeConcerned->positionInMatrice.y);

				if (lastNodeStateChange == finishNode)
					lastNodeStateChange->SetState(Node::finish);
			}
			else if (movingFinish && nodeConcerned->GetState() != Node::finish) {
				SetFinishNode(nodeConcerned->positionInMatrice.x, nodeConcerned->positionInMatrice.y);

				if (lastNodeStateChange == startNode)
					lastNodeStateChange->SetState(Node::start);
			}


			else if (nodeConcerned->GetState() != Node::wall && nodeConcerned->GetState() != Node::start && nodeConcerned->GetState() != Node::finish)
				nodeConcerned->SetState(Node::wall);
			else if (nodeConcerned->GetState() == Node::wall)
				nodeConcerned->SetState(Node::defaultState);

			lastNodeStateChange = nodeConcerned;
		}
	}


	else {
		if (!movingFinish && !movingStart) {
			lastNodeStateChange = nullptr;
		}
	}
}


void Grid::SetNeighbourNodes(Node* node) {
	std::vector<Node*> returnVector = {};

	sf::Vector2i nodePos = node->positionInMatrice;

	if (nodePos.x > 0) {
		if (grid[nodePos.x - 1][nodePos.y]->GetState() != Node::wall && grid[nodePos.x - 1][nodePos.y]->GetState() != Node::start)
			returnVector.push_back(grid[nodePos.x - 1][nodePos.y]);
	}

	if (nodePos.x < rowsNum -1) {
		if (grid[nodePos.x + 1][nodePos.y]->GetState() != Node::wall && grid[nodePos.x + 1][nodePos.y]->GetState() != Node::start)
			returnVector.push_back(grid[nodePos.x + 1][nodePos.y]);
	}

	if (nodePos.y > 0) {
		if (grid[nodePos.x][nodePos.y - 1]->GetState() != Node::wall && grid[nodePos.x][nodePos.y - 1]->GetState() != Node::start)
			returnVector.push_back(grid[nodePos.x][nodePos.y - 1]);
	}

	if (nodePos.y < ColNums -1) {
		if (grid[nodePos.x][nodePos.y + 1]->GetState() != Node::wall && grid[nodePos.x][nodePos.y + 1]->GetState() != Node::start)
			returnVector.push_back(grid[nodePos.x][nodePos.y + 1]);
	}



	for (Node * n : returnVector) {
		node->AddChild(n);
	}
}

void Grid::SpawnRandomWall() 
{
	Algorithm::threadOn = true;
	ClearWall();

	std::vector<Node*> random_path;
	random_path.push_back(startNode);
	startNode->visited = true;
	Node* actualNode = random_path[random_path.size() - 1];
	SetNeighbourNodes(actualNode);

	while (actualNode->GetState() != Node::finish)
	{
		Node* next = GetRandomNeighborNode(actualNode);

		if (next != nullptr)
		{
			random_path.push_back(next);
			actualNode = next;
			SetNeighbourNodes(actualNode);
		}
		else {
			random_path.pop_back();
			actualNode = random_path[random_path.size() - 1];
		}
	}

	for (int i = 0; i < rowsNum; ++i) {
		for (int j = 0; j < ColNums; ++j) {
			if (std::find(random_path.begin(), random_path.end(), grid[i][j]) == random_path.end()) {
				if (i > 0 && j > 0) {
					if (!(grid[i - 1][j]->GetState() == Node::wall && grid[i][j - 1]->GetState() == Node::wall && grid[i - 1][j - 1]->GetState() == Node::wall)) {
						if (grid[i - 1][j]->GetState() == Node::defaultState && grid[i][j - 1]->GetState() == Node::defaultState && grid[i - 1][j - 1]->GetState() == Node::defaultState) {
							grid[i][j]->SetState(Node::wall);
						}
						else {
							std::mt19937 gen(rd());
							std::uniform_int_distribution<> distrib(0, 1);
							int random_number = distrib(gen);

							if (random_number == 0) {
								grid[i][j]->SetState(Node::wall);
							}
						}
					}
				}
				else {
					std::mt19937 gen(rd());
					std::uniform_int_distribution<> distrib(0, 1);
					int random_number = distrib(gen);

					if (random_number == 0) {
						grid[i][j]->SetState(Node::wall);
					}
				}
			}
		}
	}
	ClearGridVisited();

	Algorithm::threadOn = false;
}

Node* Grid::GetRandomNeighborNode(Node* _node) 
{
	std::vector<Node*> possibly_neighbor;
	for (Node* neighbor : *_node->GetChilds()) {
		if (neighbor->GetState() == Node::finish) {
			return neighbor;
		}
		if (!neighbor->visited) {
			possibly_neighbor.push_back(neighbor);
		}
	}

	if (possibly_neighbor.size() != 0) {
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<> distrib(0, possibly_neighbor.size() - 1);

		int random_number = distrib(gen);
		
		possibly_neighbor[random_number]->visited = true;
		return possibly_neighbor[random_number];
	}

	return nullptr;
}