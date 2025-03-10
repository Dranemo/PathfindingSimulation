#include "Node.h"


sf::Vector2f Node::sizeNode = sf::Vector2f(30, 30);

Node::Node(int i, int ii) {
	square = new sf::RectangleShape(sizeNode);
	square->setFillColor(sf::Color::White);

	weight = 1;
	gCost = 0;
	hCost = 0;
	fCost = 0;
	positionInMatrice = sf::Vector2i(i, ii);
	square->setPosition((i)*sizeNode.x, (ii)*sizeNode.y);
}

void Node::Update() {
	if(state == State::defaultState)
		square->setFillColor(sf::Color::White);


	if (visited)
		square->setFillColor(sf::Color::Green);


	switch (state)
	{
	case State::finish:
		square->setFillColor(sf::Color::Red);
		break;

	case State::start:
		square->setFillColor(sf::Color::Blue);
		break;

	case State::wall:
		square->setFillColor(sf::Color::Black);
		break;

	case State::path:
		square->setFillColor(sf::Color::Magenta);
		break;
	}

}
