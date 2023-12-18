#include <thread>
#include "GameManager.h"
void FixedUpdate()
{
    while (true)
    {
        switch (GameManager::Instance()->GetState())
        {
        case MainMenuState:
            break;
        case SelectGameState:
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
    case SelectGameState:
        GameManager::Instance()->UpdateSelectGame();
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
        if(!IsIconic(GameManager::Instance()->GetGameWindow()))
			Update();
        if (GameManager::Instance()->GetState() == ExitGameState) return 0;
    }

    return 0;
}
