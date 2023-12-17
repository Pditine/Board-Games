#include "GameManager.h"
#include <windows.h>
#include <fstream>
#include "BoardGameFactory.h"
#include <iostream>

#ifdef _DEBUG
#define Log(x) std::cout<<x<<std::endl
#else Log(x)
#endif

GameManager* GameManager::Instance()
{
	static GameManager* instance = new GameManager();

	return instance;
}

std::vector<BoardGame*>& GameManager::GetGames()
{
	return _games;
}

GameState GameManager::GetState()
{
	return _state;
}

#pragma region 进入状态

void GameManager::OnMainMenu()
{
	putimage(0, 0, &_mainMenuImages[0]);
	_mainMenuSelect = 0;
	_state = MainMenuState;
}

void GameManager::OnSelectGame()
{
	putimage(0, 0, _games[0]->GetGameIcon());
	_selectLeverlSelect = 0;
	_state = SelectGameState;
}

void GameManager::OnAbout()
{
	putimage(0, 0, &_aboutBackground);
	_state = AboutState;
}

void GameManager::OnGame()
{
	//InitLevelScene();
	_state = TheGameState;
}

void GameManager::OnGameOver(bool isWin)
{
	if (isWin)
	{
		putimage(0, 0, _gameOverImages);
	}
	else
	{
		putimage(0, 0, _gameOverImages + 1);
	}
	_state = GameOverState;
}

void GameManager::OnExitGame()
{
	_state = ExitGameState;
}

#pragma endregion

#pragma region 更新状态

void GameManager::UpdateMainMenu()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (!_mainMenuButtonIsPress)
		{
			_mainMenuSelect--;
			if (_mainMenuSelect < 0)
			{
				_mainMenuSelect = 2;
			}
			putimage(0, 0, &_mainMenuImages[_mainMenuSelect]);
			_mainMenuButtonIsPress = true;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (!_mainMenuButtonIsPress)
		{
			_mainMenuSelect++;
			if (_mainMenuSelect > 2)
			{
				_mainMenuSelect = 0;
			}
			putimage(0, 0, &_mainMenuImages[_mainMenuSelect]);
			_mainMenuButtonIsPress = true;
		}
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		if (!_mainMenuButtonIsPress)
		{
			switch (_mainMenuSelect)
			{
			case 0:
				OnSelectGame();
				break;
			case 1:
				OnAbout();
				break;
			case 2:
				OnExitGame();
				break;
			}
		}
	}
	else
	{
		_mainMenuButtonIsPress = false;
	}
}

void GameManager::UpdateSelectGame()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (!_selectLevelsButtonIsPress)
		{
			_selectLeverlSelect--;
			if (_selectLeverlSelect < 0)
			{
				_selectLeverlSelect = _games.size()-1;
			}
			//putimage(0, 0, _selectGameBackground);
			putimage(0, 0, _games[_selectLeverlSelect]->GetGameIcon());
			_selectLevelsButtonIsPress = true;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!_selectLevelsButtonIsPress)
		{
			_selectLeverlSelect++;
			if (_selectLeverlSelect >= _games.size())
			{
				_selectLeverlSelect = 0;
			}
			//putimage(0, 0, _selectGameBackground);
			putimage(0, 0, _games[_selectLeverlSelect]->GetGameIcon());
			_selectLevelsButtonIsPress = true;
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
	{
		if (!_selectLevelsButtonIsPress)
		{
			OnMainMenu();
		}
	}
	else if (GetAsyncKeyState(VK_CONTROL))
	{
		if (!_selectLevelsButtonIsPress)
		{
			OnGame();
		}
	}
	else
	{
		_selectLevelsButtonIsPress = false;
	}
}

void GameManager::UpdateAbout()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		OnMainMenu();
	}
}

void GameManager::UpdateGame()
{
	//Map::Instance()->Update();
}

void GameManager::UpdateGameOver()
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		OnMainMenu();
	}
}

void GameManager::FixedUpdateGame()
{
	/*Map::Instance()->FixedUpdate();
	if (Map::Instance()->GetMyTank()->isDestroy)
	{
		OnGameOver(false);
		return;
	}
	std::list<EnemyTank>::iterator a = Map::Instance()->_enemyTanks.begin();
	for (int i = 0; i < Map::Instance()->_enemyTanks.size(); i++)
	{
		if (!a->isDestroy)return;
		a++;
	}
	OnGameOver(true);*/
}

#pragma endregion

//void GameManager::InitLevelScene()
//{
//	//Map::Instance()->Init(_selectLeverlSelect);
//	//Map::Instance()->PrintMap();
//}
//
//
GameManager::GameManager()
{
	_games = BoardGameFactory::CreateGames();
	loadimage(_mainMenuImages, "Resources/MainMenu0.png");
	loadimage(_mainMenuImages + 1, "Resources/MainMenu1.png");
	loadimage(_mainMenuImages + 2, "Resources/MainMenu2.png");

	//loadimage(_selectLevelsImages, "Resources/SelectLevel1.png");
	//loadimage(_selectLevelsImages + 1, "Resources/SelectLevel2.png");
	//loadimage(_selectLevelsImages + 2, "Resources/SelectLevel3.png");
	//loadimage(_selectLevelsImages + 3, "Resources/SelectLevel4.png");
	//loadimage(_selectLevelsImages + 4, "Resources/SelectLevel5.png");
	loadimage(_selectGameBackground, "Resources/SelectGameBackground.png");
	loadimage(&_aboutBackground, "Resources/About.png");

	loadimage(_gameOverImages, "Resources/GameOver0.png");
	loadimage(_gameOverImages + 1, "Resources/GameOver1.png");

	InitGame();
}

void GameManager::InitGame()
{
	initgraph(400, 400);
	putimage(0, 0, &_mainMenuImages[0]);
	//char input[5];
	//InputBox(input, 5, "输入", "聊天框", "null");
}

