#include "Menu.h"

Menu::Menu() 
{
	wm = WindowManager::GetInstance();
}


void Menu::CreateButton(sf::Vector2f _size, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize)
{
	Button* button = new Button(_size, _color, _text, _textColor, _characterSize);
	buttons.push_back(button);
	wm->AddDrawable(button->square);
}


void Menu::Update()
{
	for (Button* button : buttons) 
	{
		button->Update();
	}
}