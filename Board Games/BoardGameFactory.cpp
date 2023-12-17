#include "BoardGameFactory.h"
#include "ChineseChess.h"
#include "Gomoku.h"
//BoardGameFactory* BoardGameFactory::Instance()
//{
//	static BoardGameFactory* _instance;
//	return _instance;
//}

std::vector<BoardGame*> BoardGameFactory::CreateGames()
{
	std::vector<BoardGame*> games = { new ChineseChess(),new Gomoku()};
	return games;
}
