#pragma once
#include <SFML/Graphics.hpp>

class Node
{
public:
	enum State {
		finish,
		start,
		visited,
		wall,
		defaultState,
	};

private:

	State state = State::defaultState;


public:

	static sf::Vector2f sizeNode;

	Node(int i, int ii) {
		square = new sf::RectangleShape(sizeNode);
		square->setFillColor(sf::Color::White);

		weight = 1;
		positionInMatrice = sf::Vector2i(i, ii);
		square->setPosition((i) * sizeNode.x, (ii) * sizeNode.y);
	}

	void Update() {
		switch (state)
		{
		case State::defaultState:
			square->setFillColor(sf::Color::White);
			break;

		case State::finish:
			square->setFillColor(sf::Color::Red);
			break;

		case State::start:
			square->setFillColor(sf::Color::Blue);
			break;

		case State::wall:
			square->setFillColor(sf::Color::Black);
			break;

		case State::visited:
			square->setFillColor(sf::Color::Green);
			break;
		}
	}


	

	void SetState(State state) {
		this->state = state;
	}
	State GetState() { return state; }

	float weight;
	sf::RectangleShape* square;
	sf::Vector2i positionInMatrice;

};

