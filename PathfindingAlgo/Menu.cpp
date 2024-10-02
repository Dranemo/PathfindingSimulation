#include "Menu.h"
#include "InputManager.h"
#include "Algorithm.h"

Menu::Menu(Grid* _grid) 
{
	wm = WindowManager::GetInstance();
	grid = _grid;

	// Algo Button
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 25), sf::Color::Color(0,0, 255), "DFS", sf::Color::White, 40, std::bind(&Algorithm::DFS, grid));
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 100), sf::Color::Color(43, 255, 255), "BFS", sf::Color::White, 40, std::bind(&Algorithm::BFS, grid));
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 175), sf::Color::Color(0, 128, 0), "Dijkstra", sf::Color::White, 40, std::bind(&Algorithm::Dijkstra, grid));
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 250), sf::Color::Color(0, 100, 200), "A*", sf::Color::White, 40, nullptr);
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 325), sf::Color::Color(0, 100, 250), "Greedy", sf::Color::White, 40, nullptr);
	CreateButton(sf::Vector2f(200, 50), sf::Vector2f(950, 400), sf::Color::Color(0, 200, 250), "Swarm", sf::Color::White, 40, nullptr);

	// Clear Button
	CreateButton(sf::Vector2f(170, 50), sf::Vector2f(965, 600), sf::Color::Yellow, "Clear Grid", sf::Color::Black, 30, std::bind(&Grid::ClearGrid, grid));
	CreateButton(sf::Vector2f(170, 50), sf::Vector2f(965, 675), sf::Color::Yellow, "Clear Wall", sf::Color::Black, 30, std::bind(&Grid::ClearWall, grid));
	CreateButton(sf::Vector2f(170, 50), sf::Vector2f(965, 750), sf::Color::Yellow, "Clear Path", sf::Color::Black, 30, std::bind(&Grid::ClearGridVisited, grid));


	// Speed Button
	Button* slow = CreateSpeedButton(sf::Vector2f(65, 30), sf::Vector2f(920, 825), sf::Color::Color(100, 100, 100), "Slow", sf::Color::White, 20, nullptr);
	slow->SetCallback(std::bind(&Menu::SetSpeed, this, 100, slow));
	Button* average = CreateSpeedButton(sf::Vector2f(96, 30), sf::Vector2f(1002, 825), sf::Color::Red, "Average", sf::Color::White, 20, nullptr);
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
			btn->SetSquareColor(sf::Color::Red);
		}
		else {
			btn->SetSquareColor(sf::Color::Color(100, 100, 100));
		}
	}
}

void Menu::Update()
{
	if (InputManager::GetMousePressed()) {
		if (!Algorithm::threadOn) {
			CheckIfButtonPressed(buttons);
		}
		else {
			CheckIfButtonPressed(speedButtons);
		}
	}
}

void Menu::CheckIfButtonPressed(std::vector<Button*> _buttons)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(wm->window);
	if (mousePos.x > 900 && mousePos.x < wm->window.getSize().x && mousePos.y > 0 && mousePos.y < wm->window.getSize().y) {
		for (Button* button : _buttons)
		{
			if (button->Update(mousePos)) {
				break;
			}
		}
	}
}