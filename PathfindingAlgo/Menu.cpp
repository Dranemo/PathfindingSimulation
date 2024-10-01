#include "Menu.h"
#include "InputManager.h"
#include "Algorithm.h"

Menu::Menu(Grid* _grid) 
{
	wm = WindowManager::GetInstance();
	grid = _grid;

	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 25), sf::Color::Blue, "DFS", sf::Color::White, 40, std::bind(&Algorithm::DFS, grid));
}


void Menu::CreateButton(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback)
{
	Button* button = new Button(_size, _position, _color, _text, _textColor, _characterSize, _callback);
	buttons.push_back(button);
	wm->AddDrawable(button->square);
	wm->AddText(button->text);
}


void Menu::Update()
{
	if (InputManager::GetMousePressed() && !Algorithm::threadOn) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(wm->window);
		if (mousePos.x > 900 && mousePos.x < wm->window.getSize().x && mousePos.y > 0 && mousePos.y < wm->window.getSize().y) {
			for (Button* button : buttons)
			{
				if (button->Update(mousePos)) {
					grid->ClearGridVisited();
					break;
				}
			}
		}
	}
}