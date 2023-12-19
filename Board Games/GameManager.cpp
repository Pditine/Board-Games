#include "Socket.h"
#include "GameManager.h"
#include <windows.h>
#include "BoardGameFactory.h"
#include <iostream>
#include "DEBUG.h"

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

HWND GameManager::GetGameWindow() const
{
	return _theGameWindow;
}

#pragma region 进入状态

void GameManager::OnMainMenu()
{
	_theGameWindow = initgraph(400, 400);
	putimage(0, 0, &_mainMenuImages[0]);
	_mainMenuSelect = 0;
	_state = MainMenuState;
}

void GameManager::OnSelectGame()
{
	putimage(0, 0, _games[0]->GetGameIcon());
	_GameIndex = 0;
	_state = SelectGameState;
}

void GameManager::OnAbout()
{
	putimage(0, 0, &_aboutBackground);
	_state = AboutState;
}

void GameManager::OnServerGame()
{
	//currentGame = _games[_GameIndex];
	_state = TheGameState;
	currentGame->InitGame();
	currentGame->Update();
	currentGame->HasFaceOff();
}

void GameManager::OnClientGame()
{
	//currentGame = _games[_GameIndex];
	_state = TheGameState;
	currentGame->HasFaceOff();
	currentGame->InitGame();
	currentGame->Update();
}


void GameManager::OnGameOver(const IMAGE* const image)
{
	putimage(0,0,image);
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
			_GameIndex--;
			if (_GameIndex < 0)
			{
				_GameIndex = _games.size()-1;
			}
			putimage(0, 0, _games[_GameIndex]->GetGameIcon());
			_selectLevelsButtonIsPress = true;
		}
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (!_selectLevelsButtonIsPress)
		{
			_GameIndex++;
			if (_GameIndex >= _games.size())
			{
				_GameIndex = 0;
			}
			putimage(0, 0, _games[_GameIndex]->GetGameIcon());
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
	else if (GetAsyncKeyState(VK_UP))
	{
		if (!_selectLevelsButtonIsPress)
		{
			ServerSocket* server = new ServerSocket();
			if (!server->IsValid()) return;
			// 显示服务端IP
			Log("IP:" + server->GetIpAddress());
			// 等待客户端连接，至连接成功
			putimage(0, 0, _blackBackground);
			drawtext(("等待连接...\nIP地址:" + server->GetIpAddress()).c_str(), new RECT{80, 100, 340, 300}, DT_BOTTOM);
			while (!server->Accept()) {}
			currentGame = _games[_GameIndex];
			currentGame->Socket = server;
			currentGame->SetIsServer(true);
			OnServerGame();
		}
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		std::string tips = "请输入服务端IP地址";
		if (!_selectLevelsButtonIsPress)
		{
			// 创建客户端socket并连接到服务器
			ClientSocket* client = new ClientSocket();
			while (true)
			{
				char server_ip[15];
				InputBox(server_ip, 15,tips.c_str(), "", "null");
				std::cout << server_ip << std::endl;
				if (client->Connect(server_ip))
					// 连接成功
					break;
				tips = R"(连接失败，请重新输入服务端IP地址)";
			}
			if (!client->IsValid()) return;
			currentGame = _games[_GameIndex];
			currentGame->Socket = client;
			currentGame->SetIsServer(false);
			OnClientGame();
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
	Log("更新游戏");
	currentGame->Update();
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

}

#pragma endregion
GameManager::GameManager()
{
	_games = BoardGameFactory::CreateGames();
	loadimage(_mainMenuImages, "Resources/MainMenu0.png");
	loadimage(_mainMenuImages + 1, "Resources/MainMenu1.png");
	loadimage(_mainMenuImages + 2, "Resources/MainMenu2.png");
	loadimage(_selectGameBackground, "Resources/SelectGameBackground.png");
	loadimage(&_aboutBackground, "Resources/About.png");
	loadimage(_gameOverImages, "Resources/GameOver0.png");
	loadimage(_gameOverImages + 1, "Resources/GameOver1.png");
	loadimage(_blackBackground, "Resources/BlackBackground.png");

	InitGame();
}

void GameManager::InitGame()
{
	_theGameWindow = initgraph(400, 400);
	putimage(0, 0, &_mainMenuImages[0]);
	//char input[5];
	//InputBox(input, 5, "输入", "聊天框", "null");
}

