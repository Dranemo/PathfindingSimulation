#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include <queue>
#include <vector>
#include <thread> 
#include <chrono>
class AStar {
private:
    Grid* grid;
    std::vector<Node> walls;
    sf::Vector2i startPosition;
    sf::Vector2i finishPosition;
    Node* currentNode;
    Node* bestNode;
    Node* neighborNode;
    std::vector<int> fCosts;
    std::vector<Node*> neighbors;
    std::vector<Node*> path;
    int startX;
    int startY;
    struct CompareNode {
        bool operator()(Node* a, Node* b) {
            return a->fCost > b->fCost;
        }
    };
    struct CompareNodeGreedy {
        bool operator()(Node* a, Node* b) {
            return a->hCost > b->hCost;
        }
    };
public:
    AStar(Grid* grid) : grid(grid), bestNode(nullptr) {
        startX = startPosition.x;
        startY = startPosition.y;
    }


    //void FindPath(int startX, int startY) {
    //    bestNode = grid->GetNode(startX, startY);
    //    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openSet;
    //    Node* startNode = grid->GetNode(startX, startY);
    //    Node* finishNode = grid->GetNode(finishPosition.x, finishPosition.y);
    //
    //    startNode->gCost = 0;
    //    startNode->hCost = Heuristic(startNode, finishNode);
    //    startNode->fCost = startNode->gCost + startNode->hCost;
    //    openSet.push(startNode);
    //
    //    std::cout << "Starting A* algorithm" << std::endl;
    //    std::cout << "Start Node: (" << startX << ", " << startY << ")" << std::endl;
    //    std::cout << "Finish Node: (" << finishPosition.x << ", " << finishPosition.y << ")" << std::endl;
    //
    //    while (!openSet.empty()) {
    //        bestNode = openSet.top();
    //        openSet.pop();
    //
    //        std::cout << "Current Best Node: (" << bestNode->positionInMatrice.x << ", " << bestNode->positionInMatrice.y << ")" << std::endl;
    //
    //        if (bestNode == finishNode) {
    //            std::cout << "Finish node reached" << std::endl;
    //            RetracePath(startNode, finishNode);
    //            return;
    //        }
    //
    //        bestNode->SetState(Node::State::visited);
    //
    //        neighbors = GetNeighbors(bestNode->positionInMatrice.x, bestNode->positionInMatrice.y);
    //        for (Node* neighbor : neighbors) {
    //            if (neighbor == nullptr || neighbor->state == Node::State::visited || neighbor->state == Node::State::wall) {
    //                continue;
    //            }
    //
    //            int tentativeGCost = bestNode->gCost + 1;
    //            if (tentativeGCost < neighbor->gCost || neighbor->state == Node::State::defaultState || neighbor->state == Node::State::finish) {
    //                neighbor->gCost = tentativeGCost;
    //                neighbor->hCost = Heuristic(neighbor, finishNode);
    //                neighbor->fCost = neighbor->gCost + neighbor->hCost;
    //                neighbor->SetParent(bestNode);
    //
    //                std::cout << "Neighbor: (" << neighbor->positionInMatrice.x << ", " << neighbor->positionInMatrice.y << ") - gCost: " << neighbor->gCost << ", hCost: " << neighbor->hCost << ", fCost: " << neighbor->fCost << std::endl;
    //
    //                if (neighbor->state != Node::State::path) {
    //                    neighbor->SetState(Node::State::path);
    //                    openSet.push(neighbor);
    //                }
    //            }
    //        }
    //        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    //    }
    //
    //    std::cout << "No path found" << std::endl;
    //}
    //void FindPathGreedy(int startX, int startY) {
    //    bestNode = grid->GetNode(startX, startY);
    //    std::priority_queue<Node*, std::vector<Node*>, CompareNodeGreedy> openSet;
    //    Node* startNode = grid->GetNode(startX, startY);
    //    Node* finishNode = grid->GetNode(finishPosition.x, finishPosition.y);
    //
    //    startNode->hCost = Heuristic(startNode, finishNode);
    //    openSet.push(startNode);
    //
    //    std::cout << "Starting Greedy Best-First Search algorithm" << std::endl;
    //    std::cout << "Start Node: (" << startX << ", " << startY << ")" << std::endl;
    //    std::cout << "Finish Node: (" << finishPosition.x << ", " << finishPosition.y << ")" << std::endl;
    //
    //    while (!openSet.empty()) {
    //        bestNode = openSet.top();
    //        openSet.pop();
    //
    //        std::cout << "Current Best Node: (" << bestNode->positionInMatrice.x << ", " << bestNode->positionInMatrice.y << ")" << std::endl;
    //
    //        if (bestNode == finishNode) {
    //            std::cout << "Finish node reached" << std::endl;
    //            RetracePath(startNode, finishNode);
    //            return;
    //        }
    //
    //        bestNode->SetState(Node::State::visited);
    //
    //        std::vector<Node*> neighbors = GetNeighbors(bestNode->positionInMatrice.x, bestNode->positionInMatrice.y);
    //        for (Node* neighbor : neighbors) {
    //            if (neighbor == nullptr || neighbor->state == Node::State::visited || neighbor->state == Node::State::wall) {
    //                continue;
    //            }
    //
    //            if (neighbor->state == Node::State::defaultState || neighbor->state == Node::State::finish) {
    //                neighbor->hCost = Heuristic(neighbor, finishNode);
    //                neighbor->SetParent(bestNode);
    //
    //                std::cout << "Neighbor: (" << neighbor->positionInMatrice.x << ", " << neighbor->positionInMatrice.y << ") - hCost: " << neighbor->hCost << std::endl;
    //
    //                if (neighbor->state != Node::State::path) {
    //                    neighbor->SetState(Node::State::path);
    //                    openSet.push(neighbor);
    //                }
    //            }
    //        }
    //        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    //    }
    //
    //    std::cout << "No path found" << std::endl;
    //}



    void StartAlgorithm(int startX, int startY) {
    }

    int Heuristic(Node* a, Node* b) {
        return abs(a->positionInMatrice.x - b->positionInMatrice.x) + abs(a->positionInMatrice.y - b->positionInMatrice.y);
    }


    void RetracePath(Node* startNode, Node* finishNode) {
        Node* currentNode = finishNode;
        while (currentNode != startNode) {
            path.push_back(currentNode);
            currentNode->SetState(Node::State::start);
            currentNode = currentNode->GetParent();
        }
        path.push_back(startNode);
        startNode->SetState(Node::State::path);
    }



};
