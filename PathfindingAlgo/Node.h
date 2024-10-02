#pragma once
#include <SFML/Graphics.hpp>

class Node
{
public:
	enum State {
		finish,
		start,
		path,
		wall,
		defaultState,
	};
	bool visited = false;

private:

	State state = State::defaultState;

	Node* parent = nullptr;
	std::vector<Node*> childs;


public:

	static sf::Vector2f sizeNode;

	Node(int i, int ii);

	void Update();


	int manhattan_distance(int x1, int y1, int x2, int y2) {
		return abs(x1 - x2) + abs(y1 - y2);
	}

	void SetState(State state) {
		this->state = state;
	}
	State GetState() const { return state; };

	void SetParent(Node* parent) { this->parent = parent; }
	void AddChild(Node* child) { childs.push_back(child); }
	Node* GetParent() { return parent; }
	std::vector<Node*> GetChilds() { return childs; }

	float weight;
	int gCost;
	int hCost;
	int fCost;
	sf::RectangleShape* square;
	sf::Vector2i positionInMatrice;
};

