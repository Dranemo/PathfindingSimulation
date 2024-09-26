
#include "Grid.h"





int main()
{
    WindowManager* windowManager = WindowManager::GetInstance();
    windowManager->CreateWindow();

    Grid grid;


    while (windowManager->window.isOpen())
    {
        windowManager->Update();
    }

    return 0;
} 