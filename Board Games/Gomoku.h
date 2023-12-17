#pragma once
#include "BoardGame.h"
class Gomoku : public BoardGame
{
protected:
	void Operate() override;

	void SendBoardMessage(const char* message) override;

	char* ReceiveBoardMessage() override;

	void UpdateBoardImage() override;

	void GameOverCheck() override;

public:
	Gomoku();

	void InitGame() override;

};

