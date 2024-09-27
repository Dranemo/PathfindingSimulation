
#include "Grid.h"





int main()
{
    WindowManager* windowManager = WindowManager::GetInstance();
    windowManager->CreateWindow();

    Grid grid;

    while (windowManager->window.isOpen())
    {
        grid.Update();
        windowManager->Update();
    }

    return 0;
} 