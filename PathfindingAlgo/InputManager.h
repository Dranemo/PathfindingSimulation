#pragma once
#include <map>
#include <SFML/Graphics.hpp>
class WindowManager;

class InputManager
{
private:
	static std::map<sf::Keyboard::Key, bool> eventMap;
	static bool mousePressed;
	static bool windowClosed;

	static WindowManager* wm;

public:
	static void Awake();
	static void Update();

	static void SetMousePressed(bool _pressed) { mousePressed = _pressed; }

	static bool GetMousePressed() { return mousePressed; }
	static bool GetWindowClosed() { return windowClosed; }
	static bool GetEvent(sf::Keyboard::Key key) { return eventMap[key]; }
};

