#pragma once
#include <vector>
#include "BoardGame.h"

class BoardGameFactory
{
private:
	//BoardGameFactory() {}
public:
	static std::vector<BoardGame*> CreateGames();

	//BoardGameFactory* Instance();
};