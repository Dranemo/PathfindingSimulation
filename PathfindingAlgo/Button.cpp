#include "Button.h"

#include <iostream>
#include <thread>


Button::Button(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback)
{
	square = new sf::RectangleShape(_size);
	SetSquareColor(_color);
	square->setPosition(_position);
	bounds = square->getGlobalBounds();

	if (!font.loadFromFile("arial.ttf")) 
	{
		std::cout << "Erreur lors du chargement du font" << std::endl;
	}
		
	text = new sf::Text(_text, font, _characterSize);
	text->setFillColor(_textColor);
	text->setPosition(sf::Vector2f(_position.x + (_size.x / 2) - (text->getLocalBounds().width / 2), _position.y + (_size.y / 2) - (_characterSize / 2)));
	text->setStyle(sf::Text::Bold);

	callback = _callback;
}


bool Button::Update(sf::Vector2i _mousePos)
{
	if (_mousePos.x >= bounds.left && _mousePos.x <= bounds.left + bounds.width && _mousePos.y >= bounds.top && _mousePos.y <= bounds.top + bounds.height)
	{
		Execute();
		return true;
	}
	return false;
}

void Button::Execute() 
{
	std::thread t(callback);
	t.detach();
}

void Button::SetSquareColor(sf::Color _color) 
{
	square->setFillColor(_color);
}

void Button::SetText(std::string _text) 
{
	text->setString(_text);
}

void Button::SetTextColor(sf::Color _color)
{
	text->setFillColor(_color);
}

void Button::SetCharacterSize(int _characterSize)
{
	text->setCharacterSize(_characterSize);
}

void Button::SetCallback(std::function<void()> _callback) 
{
	callback = _callback;
}
