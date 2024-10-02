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
	Button* CreateSpeedButton(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback);

	void SetSpeed(int _speed, Button* _button);

	void Update();

private:

	std::vector<Button*> buttons;
	std::vector<Button*> speedButtons;

	WindowManager* wm;
	Grid* grid;

	int speed = 50;
};

