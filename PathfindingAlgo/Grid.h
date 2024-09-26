#pragma once
#include "Node.h"
#include "WindowManager.h"
#include <vector>

class Grid
{
private:
	int rowsNum = 18;
	int ColNums = 18;

public:
	std::vector<std::vector<Node*>> grid;

	Grid() {
		WindowManager* wm = WindowManager::GetInstance();

		grid.resize(rowsNum, std::vector<Node*>(ColNums, nullptr));

		for (int i = 0; i < rowsNum; i++) {
			for (int ii = 0; ii < ColNums; ii++) {
				grid[i][ii] = new Node(i, ii);
				wm->AddDrawable(grid[i][ii]->square);
			}
		}


		for (int i = 1; i < rowsNum; i++) {
			wm->AddLine(sf::Vector2f(i * 50, 0), sf::Vector2f(i * 50, ColNums * 50));  // Lignes verticales
		}
		for (int i = 1; i < ColNums; i++) {
			wm->AddLine(sf::Vector2f(0, i * 50), sf::Vector2f(rowsNum * 50, i * 50));  // Lignes horizontales
		}
	}
};

