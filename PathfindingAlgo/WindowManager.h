#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class WindowManager
{
private:

	std::vector<sf::Drawable*> drawables;
	std::vector<sf::Vertex> lines;

	static WindowManager* instance;

public:
	static sf::Vector2f windowSize;
	sf::RenderWindow window;

	static WindowManager* GetInstance() {
		if (instance == nullptr)
			instance = new WindowManager;
		
		return instance;
	}

	void CreateWindow();
	void Update();

	void AddDrawable(sf::Drawable* drawable);
	sf::Drawable* GetDrawable(int i);
	void AddLine(sf::Vector2f pA, sf::Vector2f pB);
};

