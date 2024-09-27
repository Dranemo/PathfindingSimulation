#pragma once
#include "Node.h"
#include "WindowManager.h"
#include <vector>

class Grid
{
private:
	int rowsNum = WindowManager::windowSize.x / Node::sizeNode.x;
	int ColNums = WindowManager::windowSize.y / Node::sizeNode.y;

public:
	std::vector<std::vector<Node*>> grid;

	Grid() {
		WindowManager* wm = WindowManager::GetInstance();

		grid.resize(rowsNum, std::vector<Node*>(ColNums, nullptr));

		for (int i = 0; i < rowsNum; i++) {
			for (int ii = 0; ii < ColNums; ii++) {
				grid[i][ii] = new Node(i, ii);
				wm->AddDrawable(grid[i][ii]->square);

				if (i == 1 && ii == 1)
					grid[i][ii]->SetState(Node::start);
				if (i == rowsNum - 2 && ii == ColNums - 2)
					grid[i][ii]->SetState(Node::finish);

			}
		}


		for (int i = 1; i < rowsNum; i++) {
			wm->AddLine(sf::Vector2f(i * Node::sizeNode.x, 0), sf::Vector2f(i * Node::sizeNode.x, ColNums * Node::sizeNode.x));  // Lignes verticales
		}
		for (int i = 1; i < ColNums; i++) {
			wm->AddLine(sf::Vector2f(0, i * Node::sizeNode.y), sf::Vector2f(rowsNum * Node::sizeNode.y, i * Node::sizeNode.y));  // Lignes horizontales
		}
	}

	int GetRows() const { return rowsNum; };

	int GetCols() const { return ColNums; };
};

