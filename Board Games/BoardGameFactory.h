#pragma once
#include <vector>
#include "BoardGame.h"

class BoardGameFactory
{
public:
	static std::vector<BoardGame*> CreateGames();
};