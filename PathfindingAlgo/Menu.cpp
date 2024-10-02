#include "Menu.h"
#include "InputManager.h"
#include "Algorithm.h"

Menu::Menu(Grid* _grid) 
{
	wm = WindowManager::GetInstance();
	grid = _grid;

	// Algo Button
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 25), sf::Color::Blue, "DFS", sf::Color::White, 40, std::bind(&Algorithm::DFS, grid));
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 100), sf::Color::Red, "BFS", sf::Color::White, 40, std::bind(&Algorithm::BFS, grid));
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 175), sf::Color::Green, "Dijkstra", sf::Color::White, 40, std::bind(&Algorithm::Dijkstra, grid));

	// Clear Button




	// Speed Button
	Button* slow = CreateSpeedButton(sf::Vector2f(65, 30), sf::Vector2f(920, 825), sf::Color::Color(100, 100, 100), "Slow", sf::Color::White, 20, nullptr);
	slow->SetCallback(std::bind(&Menu::SetSpeed, this, 100, slow));
	Button* average = CreateSpeedButton(sf::Vector2f(96, 30), sf::Vector2f(1002, 825), sf::Color::Magenta, "Average", sf::Color::White, 20, nullptr);
	average->SetCallback(std::bind(&Menu::SetSpeed, this, 50, average));
	Button* fast = CreateSpeedButton(sf::Vector2f(65, 30), sf::Vector2f(1115, 825), sf::Color::Color(100, 100, 100), "Fast", sf::Color::White, 20, nullptr);
	fast->SetCallback(std::bind(&Menu::SetSpeed, this, 10, fast));
}


void Menu::CreateButton(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback)
{
	Button* button = new Button(_size, _position, _color, _text, _textColor, _characterSize, _callback);
	buttons.push_back(button);
	wm->AddDrawable(button->square);
	wm->AddText(button->text);
}

Button* Menu::CreateSpeedButton(sf::Vector2f _size, sf::Vector2f _position, sf::Color _color, std::string _text, sf::Color _textColor, int _characterSize, std::function<void()> _callback) 
{
	Button* button = new Button(_size, _position, _color, _text, _textColor, _characterSize, _callback);
	speedButtons.push_back(button);
	buttons.push_back(button);
	wm->AddDrawable(button->square);
	wm->AddText(button->text);

	return button;
}

void Menu::SetSpeed(int _speed, Button* _button)
{
	Algorithm::speed = _speed;

	for (Button* btn : speedButtons) {
		if (btn == _button) {
			btn->SetSquareColor(sf::Color::Magenta);
		}
		else {
			btn->SetSquareColor(sf::Color::Color(100, 100, 100));
		}
	}
}




void Menu::Update()
{
	if (InputManager::GetMousePressed() && !Algorithm::threadOn) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(wm->window);
		if (mousePos.x > 900 && mousePos.x < wm->window.getSize().x && mousePos.y > 0 && mousePos.y < wm->window.getSize().y) {
			for (Button* button : buttons)
			{
				if (button->Update(mousePos)) {
					break;
				}
			}
		}
	}
}