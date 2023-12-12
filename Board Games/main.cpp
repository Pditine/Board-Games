#include <thread>
#include "GameManager.h"

//GameManager gameManager = *GameManager::Instance();

void FixedUpdate()
{
    while (true)
    {
        switch (GameManager::Instance()->GetState())
        {
        case MainMenuState:
            break;
        case SelectLevelState:
            break;
        case TheGameState:
            GameManager::Instance()->FixedUpdateGame();
            break;
        case GameOverState:
            break;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(250000));
    }
}

void Update()
{
    switch (GameManager::Instance()->GetState())
    {
    case MainMenuState:
        GameManager::Instance()->UpdateMainMenu();
        break;
    case SelectLevelState:
        GameManager::Instance()->UpdateSelectLevel();
        break;
    case AboutState:
        GameManager::Instance()->UpdateAbout();
        break;
    case TheGameState:
        GameManager::Instance()->UpdateGame();
        break;
    case GameOverState:
        GameManager::Instance()->UpdateGameOver();
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
        if (GameManager::Instance()->GetState() == ExitGameState) return 0;
    }

    return 0;
}
