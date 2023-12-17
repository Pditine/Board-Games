#include "BoardGameFactory.h"
#include "ChineseChess.h"
//BoardGameFactory* BoardGameFactory::Instance()
//{
//	static BoardGameFactory* _instance;
//	return _instance;
//}

std::vector<BoardGame*> BoardGameFactory::CreateGames()
{
	std::vector<BoardGame*> games = { new ChineseChess() };
	return games;
}
