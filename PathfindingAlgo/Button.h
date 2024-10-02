#pragma once
#include "SFML/Graphics.hpp"
#include <functional>


class Button
{

public:

	Button(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback);

	void SetSquareColor(sf::Color _color);
	void SetText(std::string _text);
	void SetTextColor(sf::Color _color);
	void SetCharacterSize(int _characterSize);
	void SetCallback(std::function<void()> _callback);


	bool Update(sf::Vector2i _mousePos);
	void Execute();

	sf::RectangleShape* square;
	sf::Text* text;

private:

	std::string string = "Text";
	sf::Font font;
	sf::FloatRect bounds;

	std::function<void()> callback;



};

