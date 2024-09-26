#include "WindowManager.h"

WindowManager* WindowManager::instance = nullptr;

void WindowManager::CreateWindow() {
	window.create(sf::VideoMode(900, 900), "SFML works!");
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