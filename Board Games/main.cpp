// C++大作业-坦克大战-李健豪-202213093015.cpp

#include <thread>
#include "GameManager.h"

GameManager gameManager;

void FixedUpdate()
{
    while (true)
    {
        switch (gameManager.GetState())
        {
        case MainMenuState:
            break;
        case SelectLevelState:
            break;
        case theGameState:
            gameManager.FixedUpdateGame();
            break;
        case GameOverState:
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(250000));
    }
}

void Update()
{
    switch (gameManager.GetState())
    {
    case MainMenuState:
        gameManager.UpdateMainMenu();
        break;
    case SelectLevelState:
        gameManager.UpdateSelectLevel();
        break;
    case AboutState:
        gameManager.UpdateAbout();
        break;
    case theGameState:
        gameManager.UpdateGame();
        break;
    case GameOverState:
        gameManager.UpdateGameOver();
        break;
    case ExitGameState:
        return;
    }
}

int main()
{
    std::thread fixedUpdateThread(FixedUpdate);
    fixedUpdateThread.detach();


    while (true)
    {
        Update();
        if (gameManager.GetState() == ExitGameState) return 0;
    }

    return 0;
}
