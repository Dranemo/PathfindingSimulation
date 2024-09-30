#pragma once
#include <vector>
#include "WindowManager.h"
#include "Button.h"

class Menu
{
public: 

	Menu();
	
	void CreateButton(sf::Vector2f _size, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize);


	void Update();

private:

	std::vector<Button*> buttons;

	WindowManager* wm;
};

