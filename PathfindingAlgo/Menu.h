#pragma once
#include <vector>
#include "WindowManager.h"
#include "Button.h"
#include "Grid.h"

class Menu
{
public: 

	Menu(Grid* _grid);
	
	void CreateButton(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback);


	void Update();

private:

	std::vector<Button*> buttons;

	WindowManager* wm;
	Grid* grid;
};

