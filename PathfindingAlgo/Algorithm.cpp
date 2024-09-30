#include "Algorithm.h"
#include <thread>
#include <chrono>
#include <algorithm>
#include <iostream>

#include "Grid.h"
#include "Node.h"

Node* Algorithm::visitingNode = nullptr;
bool Algorithm::threadOn = false;
std::vector<Node*> Algorithm::serchingQueue;
std::vector<Node*> Algorithm::path;
std::vector<Node*> Algorithm::walls;


void Algorithm::DFS(Grid* grid) {
	threadOn = true;
	GetWalls(grid);
	
	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);

	// Calcul du path (affichage vert)
	while (visitingNode != grid->GetFinishNode()) {
		visitingNode->visited = true;


		if (!visitingNode->GetChilds().empty()) {
			bool allVisited = true;

			// V�rifier qu'il n'est pas d�j� pr�sent dans la queue et que c'est un noeud non visit�
			for (Node* n : visitingNode->GetChilds()) {
				if (!n->visited) {

					serchingQueue.push_back(n);
					allVisited = false;
				}
			}

			if (!allVisited) {
				Node* newNode = serchingQueue[serchingQueue.size() - 1];

				newNode->SetParent(visitingNode);
				grid->SetNeighbourNodes(newNode);

				visitingNode = newNode;

				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			else {
				visitingNode = visitingNode->GetParent();
				serchingQueue.pop_back();
			}


		}

	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "DFS Finished \n";
}




void Algorithm::BFS(Grid* grid) {
	threadOn = true;
	GetWalls(grid);

	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);
	visitingNode->visited = true;

	int i = 0;

	while (visitingNode != grid->GetFinishNode()) {

		if (!visitingNode->GetChilds().empty()) {

			// V�rifier qu'il n'est pas d�j� pr�sent dans la queue et que c'est un noeud non visit�
			for (Node* n : visitingNode->GetChilds()) {

				if (!n->visited) {

					auto it = std::find(serchingQueue.begin(), serchingQueue.end(), n);

					if (it == serchingQueue.end()) {
						serchingQueue.push_back(n);
						n->SetParent(visitingNode);
					}					
				}
			}

			





			Node* newNode = serchingQueue[i];

			//newNode->SetParent(visitingNode);
			grid->SetNeighbourNodes(newNode);

			visitingNode = newNode;
			if (visitingNode != grid->GetFinishNode() && visitingNode != grid->GetStartNode())
				visitingNode->visited = true;

			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		}

		i++;
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "BFS Finished \n";

}

void Algorithm::GetWalls(Grid* grid) {


	for (int i = 0; i < WindowManager::windowSize.y / Node::sizeNode.y; i++) {
		for (int j = 0; j < WindowManager::windowSize.x / Node::sizeNode.x; j++) {
			if (grid->grid[i][j]->GetState() == Node::wall) {
				walls.push_back(grid->grid[i][j]);
			}
		}
	}

}

void Algorithm::CalculatePath(Grid* grid) {
	// Retour au d�but et vector path
	while (visitingNode != grid->GetStartNode()) {
		path.push_back(visitingNode);
		visitingNode = visitingNode->GetParent();
	}
}

void Algorithm::ShowPath() {
	// Affichage du path
	for (int i = path.size() - 1; i >= 0; i--) {
		if (path[i]->GetState() != Node::start && path[i]->GetState() != Node::finish)
			path[i]->SetState(Node::path);

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void Algorithm::Reset() {
	serchingQueue.clear();
	path.clear();
	walls.clear();

	threadOn = false;
}