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
		path
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

		case State::path:
			square->setFillColor(sf::Color::Magenta);
			break;
		}
		
	}


	

	void SetState(State state) {
		this->state = state;
	}

	State GetState() const { return state; };

	std::vector<Node*> GetNeighbors(const std::vector<std::vector<Node*>>& grid);

	float weight;
	sf::RectangleShape* square;
	sf::Vector2i positionInMatrice;

	Node* parent;
};

