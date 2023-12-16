#pragma once
#include "BoardGame.h"
#include <iostream>
#define GRIDWIDTH 41

enum SelectState
{
	SelectChess, PutChess
};

struct Grid
{
	int Id;
	bool IsRed;
	int x;
	int y;
};

class ChineseChess: BoardGame
{
private:
	Grid map[10][9];
	IMAGE redChessPieceImages[9];
	IMAGE blackChessPieceImages[9];
	IMAGE chessBoard;
	Grid* theSelectedGrid;
	Grid* targetGrid;
	bool turn;
	IMAGE chessFrame;
	SelectState state = SelectChess;
	IMAGE redWin;
	IMAGE blackWin;

	std::string SelectChessPiece();

	//0-空,1-兵,2-炮,3-车,4-马,5-相,6-士,7-将
	void InitMap();

	int XCheck(const Grid(&map)[10][9], int x1, int x2, int y);

	int YCheck(const Grid(&map)[10][9], int x, int y1, int y2);

	/**
 * \brief 合法性检验
 * \param map 地图
 * \param current 选中棋子的格子
 * \param targetX 目标格子x
 * \param targetY 目标格子y
 * \return
 */
	bool CanMoveToTarget(const Grid(&map)[10][9], const Grid& current, const int targetX, int targetY);

	/**
 * \brief 移动棋子
 * \param current 选中棋子格子
 * \param target 目标格子
 */
	void ApplyMove(Grid& current, Grid& target);

	void WinOrLoseCheck(int id, bool isRed);

	std::string OutputInformation(Grid& current, Grid& target);
public:
	ChineseChess();
	void InitGame() override;
protected:
	void Operate() override;

	void SendBoardMessage(const char* message) override;

	char* ReceiveBoardMessage() override;

	void UpdateBoardImage() override;

	void GameOverCheck() override;
};

