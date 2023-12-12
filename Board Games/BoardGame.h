#pragma once
#include <easyx.h>

class BoardGame
{
protected:
	IMAGE _gameBoard;

	virtual void Operate() = 0;

	virtual void SendBoardMessage(const char* message) = 0;

	virtual char* ReceiveBoardMessage() = 0;

	virtual void UpdateBoardImage() = 0;

	virtual void GameOverCheck() = 0;

public:
	virtual ~BoardGame() = default;

	void Update()
	{
		static char* message;

		ReceiveBoardMessage();
		UpdateBoardImage();
		GameOverCheck();
		Operate();
		GameOverCheck();
		SendBoardMessage(message);
	}

	IMAGE GetGameIcon()
	{
		return _gameBoard;
	}
};


