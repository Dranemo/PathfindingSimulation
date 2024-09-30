
#include "Grid.h"
#include "InputManager.h"


int main()
{
    WindowManager* windowManager = WindowManager::GetInstance();
    windowManager->CreateWindow();

    Grid grid;
    InputManager::Awake();

    while (windowManager->window.isOpen())
    {
        InputManager::Update();
        grid.Update();
        windowManager->Update();
    }
    
    return 0;
} 