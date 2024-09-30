#include "Button.h"

#include <iostream>


Button::Button(sf::Vector2f _size, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize) 
{
	square = new sf::RectangleShape(_size);
	SetSquareColor(_color);

	if (!font.loadFromFile("arial.ttf")) 
	{
		std::cout << "Erreur lors du chargement du font" << std::endl;
	}
		
	text.setFont(font);
	SetText(_text);
	SetCharacterSize(_characterSize);
}



void Button::Update() 
{

}

void Button::SetSquareColor(sf::Color _color) 
{
	square->setFillColor(_color);
}

void Button::SetText(std::string _text) 
{
	text.setString(_text);
}

void Button::SetTextColor(sf::Color _color)
{
	text.setFillColor(_color);
}

void Button::SetCharacterSize(int _characterSize)
{
	text.setCharacterSize(_characterSize);
}
