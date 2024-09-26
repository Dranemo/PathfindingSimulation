#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class WindowManager
{
private:
	std::vector<sf::Drawable*> drawables;
public:
	sf::RenderWindow window;


	void CreateWindow();
	void Update();

	void AddDrawable(sf::Drawable* drawable);
	sf::Drawable* GetDrawable(int i);
};

