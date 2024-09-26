
#include "Grid.h"





int main()
{
    WindowManager* windowManager = WindowManager::GetInstance();
    windowManager->CreateWindow();

    Grid grid;


    while (windowManager->window.isOpen())
    {
        windowManager->Update();

        for (int i = 0; i < WindowManager::windowSize.y / Node::sizeNode.y; i++) {
            for (int j = 0; j < WindowManager::windowSize.x / Node::sizeNode.x; j++) {
                grid.grid[i][j]->Update();
            }
        }
    }

    return 0;
} 