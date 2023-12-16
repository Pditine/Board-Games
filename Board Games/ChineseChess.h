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

	//0-��,1-��,2-��,3-��,4-��,5-��,6-ʿ,7-��
	void InitMap();

	int XCheck(const Grid(&map)[10][9], int x1, int x2, int y);

	int YCheck(const Grid(&map)[10][9], int x, int y1, int y2);

	/**
 * \brief �Ϸ��Լ���
 * \param map ��ͼ
 * \param current ѡ�����ӵĸ���
 * \param targetX Ŀ�����x
 * \param targetY Ŀ�����y
 * \return
 */
	bool CanMoveToTarget(const Grid(&map)[10][9], const Grid& current, const int targetX, int targetY);

	/**
 * \brief �ƶ�����
 * \param current ѡ�����Ӹ���
 * \param target Ŀ�����
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

