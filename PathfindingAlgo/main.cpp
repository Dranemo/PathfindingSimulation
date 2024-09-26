
#include "WindowManager.h" 





int main()
{
    WindowManager windowManager;
    windowManager.CreateWindow();

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    windowManager.AddDrawable(&shape);

    while (windowManager.window.isOpen())
    {
        windowManager.Update();
    }

    return 0;
}