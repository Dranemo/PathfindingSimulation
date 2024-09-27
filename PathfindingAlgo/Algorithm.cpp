#include "Algorithm.h"
#include <thread>
#include <chrono>

#include "Grid.h"
#include "Node.h"

Node* Algorithm::visitingNode = nullptr;


void Algorithm::DFS(Grid* grid) {
	GetWalls(grid);
	
	visitingNode = grid->GetStartNode();

	while (visitingNode != grid->GetFinishNode()) {
		grid->SetNeighbourNodes(visitingNode);

		for (Node* n : visitingNode->GetChilds())
			serchingQueue.push_back(n);

		for (int i = serchingQueue.size() - 1; i >= 0; i--) {
			if (serchingQueue[i]->GetChilds().empty()) {
				serchingQueue.pop_back();
			}
			else {
				serchingQueue[i]->SetParent(visitingNode);
				visitingNode = serchingQueue[i];
				visitingNode->SetState(Node::visited);
				break;
			}

		}
	}

	while (visitingNode != grid->GetStartNode()) {
		path.push_back(visitingNode);
		visitingNode = visitingNode->GetParent();
	}

	for (int i = path.size() - 1; i >= 0; i--) {
		path[i]->SetState(Node::path);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}




void Algorithm::BFS(Grid* grid) {
	GetWalls(grid);

	visitingNode = grid->GetStartNode();

	while (visitingNode != grid->GetFinishNode()) {
		grid->SetNeighbourNodes(visitingNode);


	}
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