#pragma once
#include "BoardGame.h"
class Gomoku : public BoardGame
{
protected:
	std::string Operate() override;

	void SendBoardMessage(const std::string& message) override;

	std::string ReceiveBoardMessage() override;

	void UpdateBoardImage() override;

	bool GameOverCheck() override;

public:
	Gomoku();

	void InitGame() override;

};

