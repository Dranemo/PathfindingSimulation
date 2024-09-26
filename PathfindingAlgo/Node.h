#pragma once
#include <SFML/Graphics.hpp>

class Node
{
private:
	bool isFinish = false;
	bool isStart = false;

	bool visited = false;


public:
	Node(int i, int ii) {
		square = new sf::RectangleShape(sf::Vector2f(50, 50));
		square->setFillColor(sf::Color::White);


		weight = 1;
		positionInMatrice = sf::Vector2i(i, ii);
		square->setPosition((i) * 50, (ii) * 50);
	}

	float weight;
	sf::RectangleShape* square;
	sf::Vector2i positionInMatrice;

};

