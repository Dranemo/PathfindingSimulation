#include "Grid.h"
#include "Algorithm.h"
#include "InputManager.h"

#include <thread>

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
		if (InputManager::GetEvent(sf::Keyboard::P)) {

			mousePressed = false;

			movingStart = false;
			movingFinish = false;
			creatingWalls = false;

			lastNodeStateChange = nullptr;


			ClearGridVisited();


			// Lancer DFS dans un nouveau thread, en passant `this` (instance de Grid) comme argument
			std::thread t(&Algorithm::DFS, this);
			t.detach();  // Détacher le thread si vous ne voulez pas attendre qu'il se termine
		}

		else if (InputManager::GetEvent(sf::Keyboard::B)) {

			mousePressed = false;

			movingStart = false;
			movingFinish = false;
			creatingWalls = false;

			lastNodeStateChange = nullptr;

			ClearGridVisited();


			// Lancer DFS dans un nouveau thread, en passant `this` (instance de Grid) comme argument
			std::thread t(&Algorithm::BFS, this);
			t.detach();  // Détacher le thread si vous ne voulez pas attendre qu'il se termine
		}

		else if (InputManager::GetEvent(sf::Keyboard::D)) {

			mousePressed = false;

			movingStart = false;
			movingFinish = false;
			creatingWalls = false;

			lastNodeStateChange = nullptr;

			ClearGridVisited();


			// Lancer DFS dans un nouveau thread, en passant `this` (instance de Grid) comme argument
			std::thread t(&Algorithm::Dijkstra, this);
			t.detach();  // Détacher le thread si vous ne voulez pas attendre qu'il se termine
		}
	}


	if (mousePressed) {
		SetNodeStateMouse(sf::Mouse::getPosition(wm->window));
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
		if(!movingFinish && !movingStart)
			lastNodeStateChange = nullptr;
	}
}


void Grid::SetNeighbourNodes(Node* node) {
	std::vector<Node*> returnVector = {};

	sf::Vector2i nodePos = node->positionInMatrice;

	if (nodePos.x == 0 && nodePos.y == 5) {
		std::cout << "stop" << std::endl;
	}

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