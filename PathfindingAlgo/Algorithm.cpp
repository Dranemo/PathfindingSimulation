#include "Algorithm.h"
#include "Grid.h"
#include "Node.h"

Node* Algorithm::visitingNode = nullptr;
bool Algorithm::threadOn = false;
std::vector<Node*> Algorithm::serchingQueue;
std::vector<Node*> Algorithm::path;
std::vector<Node*> Algorithm::walls;

struct DijkstraCompare {
	bool operator()(Node* a, Node* b) {
		return a->weight > b->weight;
	}
};
struct AStarCompare {
	bool operator()(Node* a, Node* b) {
		return a->fCost > b->fCost;
	}
};
struct GreedyCompare {
	bool operator()(Node* a, Node* b) {
		return a->hCost > b->hCost;
	}
};

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

			// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
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

			// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
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


void Algorithm::Dijkstra(Grid* grid) 
{
	threadOn = true;
	bool isFinish = false;
	std::priority_queue<Node*, std::vector<Node*>, DijkstraCompare> pq;


	// Point de départ
	visitingNode = grid->GetStartNode();
	visitingNode->weight = 0;
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinish) {
		visitingNode = pq.top();
		pq.pop();

		// Obtenir les voisins
		grid->SetNeighbourNodes(visitingNode);

		for (Node* neighbor : visitingNode->GetChilds()) {
			if (!neighbor->visited) {
				int newCost = visitingNode->weight + neighbor->weight;
				neighbor->weight = newCost;
				neighbor->SetParent(visitingNode);
				if (neighbor->GetState() == Node::finish) {
					isFinish = true;
					break;
				}
				else {
					neighbor->visited = true;
				}
				pq.push(neighbor);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "Dijkstra Finished \n";
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
	// Retour au début et vector path
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

void Algorithm::AStar(Grid* grid) {
	
	threadOn = true;
	bool isFinish = false;
	std::priority_queue<Node*, std::vector<Node*>, AStarCompare> pq;

	visitingNode = grid->GetStartNode();
	visitingNode->fCost = 0;
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinish) {
		visitingNode = pq.top();
		pq.pop();

		// Obtenir les voisins
		grid->SetNeighbourNodes(visitingNode);

		for (Node* neighbor : visitingNode->GetChilds()) {
			if (!neighbor->visited) {
				neighbor->gCost = neighbor->manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetStartNode()->positionInMatrice.x,
					grid->GetStartNode()->positionInMatrice.y
				);
				float newGCost = visitingNode->gCost + neighbor->manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					visitingNode->positionInMatrice.x,
					visitingNode->positionInMatrice.y
				);
				neighbor->hCost = neighbor->manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetFinishNode()->positionInMatrice.x,
					grid->GetFinishNode()->positionInMatrice.y
				);
				neighbor->gCost = newGCost;
				neighbor->fCost = neighbor->gCost + neighbor->hCost;
				neighbor->SetParent(visitingNode);
				if (neighbor->GetState() == Node::finish) {
					isFinish = true;
					break;
				}
				else {
					neighbor->visited = true;
				}
				pq.push(neighbor);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "A Star Finished \n";
}
void Algorithm::GreedyBFS(Grid* grid) {

	threadOn = true;
	bool isFinish = false;
	std::priority_queue<Node*, std::vector<Node*>, GreedyCompare> pq;

	visitingNode = grid->GetStartNode();
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinish) {
		visitingNode = pq.top();
		pq.pop();

		// Obtenir les voisins
		grid->SetNeighbourNodes(visitingNode);

		for (Node* neighbor : visitingNode->GetChilds()) {
			if (!neighbor->visited) {
				neighbor->hCost = neighbor->manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetFinishNode()->positionInMatrice.x,
					grid->GetFinishNode()->positionInMatrice.y
				);
				neighbor->SetParent(visitingNode);
				if (neighbor->GetState() == Node::finish) {
					isFinish = true;
					break;
				}
				else {
					neighbor->visited = true;
				}
				pq.push(neighbor);
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "Greedy BFS Finished \n";
}