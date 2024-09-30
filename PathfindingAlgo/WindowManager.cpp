#include "WindowManager.h"
#include "InputManager.h"
#include <iostream>

WindowManager* WindowManager::instance = nullptr;
sf::Vector2f WindowManager::windowSize = sf::Vector2f(900, 900);

void WindowManager::CreateWindow() {
	window.create(sf::VideoMode(1200, 900), "SFML works!");
}

void WindowManager::Update() {
    if(InputManager::GetWindowClosed()) {
		window.close();
	}

    window.clear();

    for (sf::Drawable* dr : drawables) {
        window.draw(*dr);
    }
    if (!lines.empty()) {
        window.draw(&lines[0], lines.size(), sf::Lines);  // Dessine toutes les lignes d'un coup
    }

    window.display();
}

void WindowManager::AddDrawable(sf::Drawable* drawable) {
    drawables.push_back(drawable);
}

sf::Drawable* WindowManager::GetDrawable(int i) {
    return drawables[i];
}

void WindowManager::AddLine(sf::Vector2f pA, sf::Vector2f pB) {
    // Ajouter deux sommets au vecteur 'lines'
    lines.push_back(sf::Vertex(pA, sf::Color::Black)); 
    lines.push_back(sf::Vertex(pB, sf::Color::Black));
}