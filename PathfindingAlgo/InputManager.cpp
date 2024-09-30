#include "InputManager.h"
#include "WindowManager.h"

std::map<sf::Keyboard::Key, bool> InputManager::eventMap;
WindowManager* InputManager::wm = nullptr;
bool InputManager::mousePressed = false;
bool InputManager::windowClosed = false;


void InputManager::Awake()
{
	wm = WindowManager::GetInstance();

	eventMap[sf::Keyboard::P] = false;
	eventMap[sf::Keyboard::B] = false;

	mousePressed = false;
	windowClosed = false;


}


void InputManager::Update()
{
	sf::Event event;
	while (wm->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			windowClosed = true;


		if (event.type == sf::Event::MouseButtonPressed) {
			mousePressed = true;


		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			mousePressed = false;
		}

		if (event.type == sf::Event::KeyPressed)
		{
			// Vérifier si la touche 'P' est pressée
			if (event.key.code == sf::Keyboard::P)
			{
				eventMap[sf::Keyboard::P] = true;
			}

			if (event.key.code == sf::Keyboard::B)
			{
				eventMap[sf::Keyboard::B] = true;
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			// Vérifier si la touche 'P' est pressée
			if (event.key.code == sf::Keyboard::P)
			{
				eventMap[sf::Keyboard::P] = false;
			}

			if (event.key.code == sf::Keyboard::B)
			{
				eventMap[sf::Keyboard::B] = false;
			}
		}
	}
}