
#include "Grid.h"
#include "InputManager.h"
#include "Menu.h"


int main()
{
    WindowManager* windowManager = WindowManager::GetInstance();
    windowManager->CreateWindow();

    Grid grid;
    Menu menu(&grid);
    InputManager::Awake();

    while (windowManager->window.isOpen())
    {
        InputManager::Update();
        menu.Update();
        grid.Update();
        windowManager->Update();
    }
    
    return 0;
} 