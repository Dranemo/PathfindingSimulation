#pragma once
#include "SFML/Graphics.hpp"

class Button
{

public:

	Button(sf::Vector2f _size, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize);

	void SetSquareColor(sf::Color _color);
	void SetText(std::string _text);
	void SetTextColor(sf::Color _color);
	void SetCharacterSize(int _characterSize);


	void Update();

	sf::RectangleShape* square;

private:

	std::string string = "Text";
	sf::Font font;
	sf::Text text;


};

