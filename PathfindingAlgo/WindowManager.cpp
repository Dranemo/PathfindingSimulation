#include "WindowManager.h"

void WindowManager::CreateWindow() {
	window.create(sf::VideoMode(200, 200), "SFML works!");
}

void WindowManager::Update() {
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();

    for (sf::Drawable* dr : drawables) {
        window.draw(*dr);
    }

    window.display();
}

void WindowManager::AddDrawable(sf::Drawable* drawable) {
    drawables.push_back(drawable);
}

sf::Drawable* WindowManager::GetDrawable(int i) {
    return drawables[i];
}