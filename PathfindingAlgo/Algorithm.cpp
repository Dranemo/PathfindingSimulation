#include "Algorithm.h"
#include "Grid.h"
#include "Node.h"

Node* Algorithm::visitingNode = nullptr;
bool Algorithm::threadOn = false;
std::vector<Node*> Algorithm::serchingQueue;
std::vector<Node*> Algorithm::path;
int Algorithm::speed = 50;

struct DijkstraCompare {
	bool operator()(Node* a, Node* b) {
		return a->weight > b->weight;
	}
};


void Algorithm::DFS(Grid* grid) {
	threadOn = true;
	grid->ClearGridVisited();

	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);

	// Calcul du path (affichage vert)
	while (visitingNode != grid->GetFinishNode()) {
		visitingNode->visited = true;


		if (!visitingNode->GetChilds()->empty()) {
			bool allVisited = true;

			// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
			for (Node* n : *visitingNode->GetChilds()) {
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

				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
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
	grid->ClearGridVisited();

	visitingNode = grid->GetStartNode();
	grid->SetNeighbourNodes(visitingNode);
	visitingNode->visited = true;

	int i = 0;

	while (visitingNode != grid->GetFinishNode()) {

		if (!visitingNode->GetChilds()->empty()) {

			// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
			for (Node* n : *visitingNode->GetChilds()) {

				if (n->GetState() == Node::wall) {
					std::cout << "euh" << std::endl;
				}

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

			std::this_thread::sleep_for(std::chrono::milliseconds(speed));

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
	grid->ClearGridVisited();
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

		for (Node* neighbor : *visitingNode->GetChilds()) {
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

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "Dijkstra Finished \n";
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

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}
}

void Algorithm::Reset() {
	serchingQueue.clear();
	path.clear();

	threadOn = false;
}