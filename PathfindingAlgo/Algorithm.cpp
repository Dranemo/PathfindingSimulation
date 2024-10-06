#include "Algorithm.h"
#include "Grid.h"
#include "Node.h"


#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

#include "Stack.h"
#include <queue>
#include <set>


Node* Algorithm::visitingNode = nullptr;
bool Algorithm::isFinished = false;
bool Algorithm::threadOn = false;
std::vector<Node*> Algorithm::path;
int Algorithm::speed = 50;





struct DijkstraCompare {
	bool operator()(Node* a, Node* b) {
		return a->weight > b->weight;
	}
};
struct AStarCompare {
	bool operator()(Node* a, Node* b) {
		if (a->fCost == b->fCost) {
			return a->hCost > b->hCost; 
		}
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
	isFinished = false;
	grid->ClearGridVisited();

	Stack<Node*> stack;
	std::set<Node*> enTraitement;

	stack.push(grid->GetStartNode());
	//enTraitement.insert(grid->GetStartNode());  // Marque comme en traitement


	// Calcul du path (affichage vert)
	while (!isFinished && !stack.empty()) {



		visitingNode = stack.top();												// Prend le dernier élément
		grid->SetNeighbourNodes(visitingNode);									// Met les childs
		visitingNode->visited = true;											// Met en visited

		// Suppression des listes
		stack.pop();															// Supprime de la stack
		if (enTraitement.find(visitingNode) != enTraitement.end())				
			enTraitement.erase(visitingNode);									// Supprime de la liste en cours




		bool allVisited = true;
		// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
		for (Node* n : *visitingNode->GetChilds()) {
			if (!n->visited) {

				if (enTraitement.find(n) != enTraitement.end()) {
					enTraitement.erase(n);
					stack.pop_inside(n);
				}

				stack.push(n);

				// Set parent
				if (visitingNode != nullptr)
					n->SetParent(visitingNode);

				enTraitement.insert(n);

				allVisited = false;
			}
		}

		// S'ils sont tous visités, ne pas attendre pour revenir a la cellule d'avant
		if (!allVisited) {
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}


		if (visitingNode->GetState() == Node::finish) {
			isFinished = true;
			break;
		}
	}


	CalculatePath(grid);
	ShowPath();

	enTraitement.clear();
	stack.clear();
	Reset();

	std::cout << "DFS Finished \n";
}


void Algorithm::BFS(Grid* grid) {
	threadOn = true;
	isFinished = false;
	grid->ClearGridVisited();


	std::queue<Node*> queue;
	std::set<Node*> enTraitement;

	queue.push(grid->GetStartNode());



	while (!isFinished && !queue.empty()) {

		visitingNode = queue.front();											// Prend le dernier élément
		grid->SetNeighbourNodes(visitingNode);									// Met les childs
		visitingNode->visited = true;											// Met en visited

		// Suppression des listes
		queue.pop();															// Supprime de la queue

		bool suppressing = true;
		while (suppressing) {

			if (enTraitement.find(visitingNode) != enTraitement.end())
				enTraitement.erase(visitingNode);
			else {
				suppressing = false;
			}
		}




		// Vérifier qu'il n'est pas déjà présent dans la queue et que c'est un noeud non visité
		for (Node* n : *visitingNode->GetChilds()) {

			if (!n->visited) {

				if (enTraitement.find(n) == enTraitement.end()) {
					queue.push(n);
					enTraitement.insert(n);


					// Set parent
					if (visitingNode != nullptr)
						n->SetParent(visitingNode);
				}
			}
		}

		if (!queue.empty()) {
			if (!queue.front()->visited) {
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			}
		}

		if (visitingNode->GetState() == Node::finish) {
			isFinished = true;
			break;
		}
	}

	CalculatePath(grid);

	enTraitement.clear();
	while (!queue.empty())
		queue.pop();
	ShowPath();
	Reset();

	std::cout << "BFS Finished \n";

}


void Algorithm::Dijkstra(Grid* grid) 
{
	threadOn = true;
	grid->ClearGridVisited();
	isFinished = false;
	std::priority_queue<Node*, std::vector<Node*>, DijkstraCompare> pq;


	// Point de départ
	visitingNode = grid->GetStartNode();
	visitingNode->weight = 0;
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinished) {
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
					isFinished = true;
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

	if (isFinished) {
		for (int i = path.size() - 1; i >= 0; i--) {
			if (path[i]->GetState() != Node::start && path[i]->GetState() != Node::finish)
				path[i]->SetState(Node::path);

			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
		}
	}
}

void Algorithm::Reset() {
	path.clear();

	threadOn = false;
}

void Algorithm::AStar(Grid* grid) {
	
	threadOn = true;
	grid->ClearGridVisited();
	isFinished = false;
	std::priority_queue<Node*, std::vector<Node*>, AStarCompare> pq;

	visitingNode = grid->GetStartNode();
	visitingNode->fCost = 0;
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinished) {
		visitingNode = pq.top();
		pq.pop();

		// Obtenir les voisins
		grid->SetNeighbourNodes(visitingNode);

		for (Node* neighbor : *visitingNode->GetChilds()) {
			if (!neighbor->visited) {
				neighbor->gCost = manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetStartNode()->positionInMatrice.x,
					grid->GetStartNode()->positionInMatrice.y
				);
				float newGCost = visitingNode->gCost + manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					visitingNode->positionInMatrice.x,
					visitingNode->positionInMatrice.y
				);
				neighbor->hCost = manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetFinishNode()->positionInMatrice.x,
					grid->GetFinishNode()->positionInMatrice.y
				);
				neighbor->gCost = newGCost;
				neighbor->fCost = neighbor->gCost + neighbor->hCost;
				neighbor->SetParent(visitingNode);
				if (neighbor->GetState() == Node::finish) {
					isFinished = true;
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

	std::cout << "A Star Finished \n";
}
void Algorithm::GreedyBFS(Grid* grid) {

	threadOn = true;
	grid->ClearGridVisited();
	isFinished = false;
	std::priority_queue<Node*, std::vector<Node*>, GreedyCompare> pq;

	visitingNode = grid->GetStartNode();
	visitingNode->visited = true;
	pq.push(visitingNode);

	WindowManager* windowManager = WindowManager::GetInstance();


	while (!pq.empty() && !isFinished) {
		visitingNode = pq.top();
		pq.pop();

		// Obtenir les voisins
		grid->SetNeighbourNodes(visitingNode);

		for (Node* neighbor : *visitingNode->GetChilds()) {
			if (!neighbor->visited) {
				neighbor->hCost = manhattan_distance(
					neighbor->positionInMatrice.x,
					neighbor->positionInMatrice.y,
					grid->GetFinishNode()->positionInMatrice.x,
					grid->GetFinishNode()->positionInMatrice.y
				);
				neighbor->SetParent(visitingNode);
				if (neighbor->GetState() == Node::finish) {
					isFinished = true;
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

	std::cout << "Greedy BFS Finished \n";
}





void Algorithm::AStar2(Grid* grid) {
	threadOn = true;
	isFinished = false;
	grid->ClearGridVisited();

	auto compare = [](Node* a, Node* b) {
		if (a->fCost == b->fCost)
			return a->hCost > b->hCost;
		return a->fCost > b->fCost;
		};

	Priority_Queue<Node*, std::vector<Node*>, decltype(compare)> queue(compare);
	std::set<Node*> enTraitement;

	Node* startNode = grid->GetStartNode();
	Node* finishNode = grid->GetFinishNode();

	// Set les costs du départ
	startNode->gCost = 0;
	startNode->hCost = manhattan_distance(startNode->positionInMatrice.x, startNode->positionInMatrice.y, finishNode->positionInMatrice.x, finishNode->positionInMatrice.y);
	startNode->fCost = startNode->gCost + startNode->hCost;
	queue.push(startNode);

	// Tant que c'est pas fini
	while (!isFinished && !queue.empty()) {
		visitingNode = queue.top();
		queue.pop();

		// Savoir si c'est fini
		if (visitingNode->GetState() == Node::finish) {
			isFinished = true;
			break;
		}

		// Mettre les voisins
		grid->SetNeighbourNodes(visitingNode);
		visitingNode->visited = true;


		// Check pour chaque voisins
		for (Node* neighbor : *visitingNode->GetChilds()) {

			// Vérifier qu'il soit pas visité
			if (!neighbor->visited) {
				int tentativeGCost = visitingNode->gCost + 1; // 1 = distance entre 2 nodes
				if (tentativeGCost < neighbor->gCost || !enTraitement.count(neighbor)) { // Si le nouveau gCost est plus petit que l'ancien ou que le noeud n'est pas en traitement (= pas encore voisin d'un autre / ave cun chemin plus court)
					
					// Màj des costs et parent
					neighbor->SetParent(visitingNode);
					neighbor->gCost = tentativeGCost;
					neighbor->hCost = manhattan_distance(neighbor->positionInMatrice.x, neighbor->positionInMatrice.y, finishNode->positionInMatrice.x, finishNode->positionInMatrice.y);
					neighbor->fCost = neighbor->gCost + neighbor->hCost;

					// S'il est déjà dans la lsite, pas besoin de le rajouter
					if (!enTraitement.count(neighbor)) {
						queue.push(neighbor);
						enTraitement.insert(neighbor);
					}
					//queue.sort();
				}
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(speed));
	}

	CalculatePath(grid);
	ShowPath();
	Reset();

	std::cout << "A* test Finished \n";
}



