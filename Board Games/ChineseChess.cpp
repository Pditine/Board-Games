#include "ChineseChess.h"
#include <graphics.h>
#include <string>
ChineseChess::ChineseChess()
{
	//loadimage(&_gameBoard,"Resources/ChineseChess/MainMenu0.png");
	loadimage(blackChessPieceImages + 1, "Resources/ChineseChess/BlackChessPiece1.GIF");
	loadimage(blackChessPieceImages + 2, "Resources/ChineseChess/BlackChessPiece2.GIF");
	loadimage(blackChessPieceImages + 3, "Resources/ChineseChess/BlackChessPiece3.GIF");
	loadimage(blackChessPieceImages + 4, "Resources/ChineseChess/BlackChessPiece4.GIF");
	loadimage(blackChessPieceImages + 5, "Resources/ChineseChess/BlackChessPiece5.GIF");
	loadimage(blackChessPieceImages + 6, "Resources/ChineseChess/BlackChessPiece6.GIF");
	loadimage(blackChessPieceImages + 7, "Resources/ChineseChess/BlackChessPiece7.GIF");
	loadimage(blackChessPieceImages + 8, "Resources/ChineseChess/BlackChessPiece0.GIF");

	loadimage(redChessPieceImages + 1, "Resources/ChineseChess/RedChessPiece1.GIF");
	loadimage(redChessPieceImages + 2, "Resources/ChineseChess/RedChessPiece2.GIF");
	loadimage(redChessPieceImages + 3, "Resources/ChineseChess/RedChessPiece3.GIF");
	loadimage(redChessPieceImages + 4, "Resources/ChineseChess/RedChessPiece4.GIF");
	loadimage(redChessPieceImages + 5, "Resources/ChineseChess/RedChessPiece5.GIF");
	loadimage(redChessPieceImages + 6, "Resources/ChineseChess/RedChessPiece6.GIF");
	loadimage(redChessPieceImages + 7, "Resources/ChineseChess/RedChessPiece7.GIF");
	loadimage(redChessPieceImages + 8, "Resources/ChineseChess/RedChessPiece0.GIF");
	loadimage(redWin, "Resources/ChineseChess/redWin.png");
	loadimage(blackWin, "Resources/ChineseChess/blackWin.png");
	loadimage(chessBoard, "Resources/ChineseChess/chessBoard.png");
	loadimage(chessFrame, "Resources/ChineseChess/ChessFrame.png");
	loadimage(_gameIcon, "Resources/ChineseChess/chessBoard.png");

	//loadimage(redChessPieceImages+0, "Resources/RP.GIF");


	//loadimage(blackChessPieceImages + 0, "Resources/BlackChessPiece0.GIF");

}

void ChineseChess::Operate() 
{

}

void ChineseChess::SendBoardMessage(const char* message) 
{

}

char* ChineseChess::ReceiveBoardMessage() 
{
	return nullptr;
}

void ChineseChess::UpdateBoardImage() 
{
	putimage(0, 0, chessBoard);
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 9; x++)
			drawAlpha(map[y][x].IsRed ? &redChessPieceImages[map[y][x].Id] : &blackChessPieceImages[map[y][x].Id], x * GRIDWIDTH, y * GRIDWIDTH);
	if (theSelectedGrid != nullptr)
		drawAlpha(chessFrame, theSelectedGrid->x * GRIDWIDTH, theSelectedGrid->y * GRIDWIDTH);
}

void ChineseChess::GameOverCheck() 
{
	
}


int ChineseChess::XCheck(const Grid (&map)[10][9], int x1, int x2, int y)
{
	if (x1 == x2) return -1;
	if (abs(x1 - x2) == 1) return 0;

	int amount = 0;
	if (x1 < x2)
	{
		for (int i = x1 + 1; i < x2; i++)
			if (map[y][i].Id != 0)
				amount++;
	}
	else
	{
		for (int i = x2 + 1; i < x1; i++)
			if (map[y][i].Id != 0)
				amount++;
	}
	return amount;
}

int ChineseChess::YCheck(const Grid (&map)[10][9], int x, int y1, int y2)
{
	if (y1 == y2) return -1;
	if (abs(y1 - y2) == 1) return 0;

	int amount = 0;
	if (y1 < y2)
	{
		for (int i = y1 + 1; i < y2; i++)
			if (map[i][x].Id != 0)
				amount++;
	}
	else
	{
		for (int i = y2 + 1; i < y1; i++)
			if (map[i][x].Id != 0)
				amount++;
	}
	return amount;
}


bool ChineseChess::CanMoveToTarget(const Grid (&map)[10][9], const Grid& current, const int targetX, int targetY)
{
	if (current.Id == 0) return false; // 选择的格子为空
	if (targetX == current.x && targetY == current.y) return false; // 目标格与选择的格子一致

	const Grid targetGrid = map[targetY][targetX];
	if (targetGrid.Id != 0 && targetGrid.IsRed == current.IsRed) return false;

	int chessCount; // 目标格与当前格之间的有棋子的格子数量
	switch (current.Id)
	{
	case 1:
		// 兵
		if (targetX != current.x)
			return false;

		if (current.IsRed)
			return targetY == current.y - 1;
		return targetY == current.y + 1;

	case 2:
		// 炮
		if (current.x == targetX)
			chessCount = YCheck(map, targetX, current.y, targetY);
		else if (current.y == targetY)
			chessCount = XCheck(map, targetX, current.x, targetY);
		else
			return false;

		if (targetGrid.Id == 0)
		{
			if (chessCount == 0) return true;
			return false;
		}
		if (chessCount == 1) return true;
		return false;


	case 3:
		// 车
		if (current.x == targetX)
			chessCount = YCheck(map, targetX, current.y, targetY);
		else if (current.y == targetY)
			chessCount = XCheck(map, targetX, current.x, targetY);
		else
			return false;

		if (chessCount == 0 || chessCount == 1)
			return true;
		return false;

	case 4:
		// 马
		if (abs(targetX - current.x) + abs(targetY - current.y) == 3)
		{
			// todo: 马脚
			return true;
		}
		return false;

	case 5:
		// 象
		if (abs(targetX - current.x) == 2 && abs(targetY - current.y) == 2)
		{
			// todo: 象脚
			return true;
		}
		return false;


	case 6:
		// 士
		if (current.IsRed)
		{
			if (targetY < 7 || targetX < 3 || targetX > 5)
				return false;
			return abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1;
		}
		if (targetY > 2 || targetX < 3 || targetX > 5)
			return false;
		return abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1;

	case 7:
		// 帅
	{
		if (current.IsRed)
		{
			if (targetY < 7 || targetX < 3 || targetX > 5)
			{
				return false;
			}
			return (abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1) ||
				(abs(targetX - current.x) == 1 && targetY == current.y) ||
				(abs(targetY - current.y) == 1 && targetX == current.x);
		}
		if (targetY > 2 || targetX < 3 || targetX > 5)
		{
			return false;
		}
		return (abs(targetX - current.x) == 1 && abs(targetY - current.y) == 1) ||
			(abs(targetX - current.x) == 1 && targetY == current.y) ||
			(abs(targetY - current.y) == 1 && targetX == current.x);
	}
	case 8:
		// 升级兵
		return (abs(targetX - current.x) == 1 && targetY == current.y) ||
			(abs(targetY - current.y) == 1 && targetX == current.x);

	default:
		return false;
	}
}


void ChineseChess::InitMap()
{
	int intMap[10][9] =
	{
		3,4,5,6,7,6,5,4,3,
		0,0,0,0,0,0,0,0,0,
		0,2,0,0,0,0,0,2,0,
		1,0,1,0,1,0,1,0,1,
		0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,
		1,0,1,0,1,0,1,0,1,
		0,2,0,0,0,0,0,2,0,
		0,0,0,0,0,0,0,0,0,
		3,4,5,6,7,6,5,4,3,
	};

	for (int y = 0; y < 10; y++)	
	{
		for (int x = 0; x < 9; x++)
		{
			Grid newGrid;
			newGrid.Id = intMap[y][x];
			newGrid.x = x;
			newGrid.y = y;
			newGrid.IsRed = y >= 5;
			map[y][x] = newGrid;
		}
	}
}

void ChineseChess::InitGame()
{
	InitMap();
	initgraph(377, 417);
	putimage(0, 0, chessBoard);
	UpdateBoardImage();
}

std::string ChineseChess::OutputInformation(Grid & current, Grid & target)
{
	std::cout << std::to_string(current.x) + std::to_string(current.y) + std::to_string(target.x) + std::to_string(target.y) << std::endl;
	return std::to_string(current.x) + std::to_string(current.y) + std::to_string(target.x) + std::to_string(target.y);
}

void ChineseChess::WinOrLoseCheck(int id, bool isRed)
{
	if (id == 7)
	{
		if (isRed)
		{
			putimage(0, 0, blackWin);
		}
		else
		{
			putimage(0, 0, redWin);
		}
	}
}

std::string ChineseChess::SelectChessPiece()
{
	MOUSEMSG m = GetMouseMsg();
	while (true)
	{
		switch (state)
		{
		case SelectChess:
			while (true)
			{
				std::cout << "走出个虎虎生风" << std::endl;
				while (!m.mkLButton || theSelectedGrid == nullptr || theSelectedGrid->Id == 0)
				{
					m = GetMouseMsg();
					theSelectedGrid = &map[m.y / GRIDWIDTH][m.x / GRIDWIDTH];
				}
				if (theSelectedGrid->Id != 0)
				{
					UpdateBoardImage();
					state = PutChess;
					break;
				}
			}
			break;
		case PutChess:
			while (true)
			{
				std::cout << "走出个恍如隔世" << std::endl;
				m = GetMouseMsg();
				if (m.mkLButton)
				{
					targetGrid = &map[m.y / GRIDWIDTH][m.x / GRIDWIDTH];
					if (theSelectedGrid != nullptr && CanMoveToTarget(map, *theSelectedGrid, targetGrid->x, targetGrid->y))
					{
						int id = targetGrid->Id;
						bool isRed = targetGrid->IsRed;
						ApplyMove(*theSelectedGrid, *targetGrid);
						Grid* selectGrid = theSelectedGrid;
						theSelectedGrid = nullptr;
						UpdateBoardImage();
						WinOrLoseCheck(id, isRed);
						return OutputInformation(*selectGrid, *targetGrid);
					}
					theSelectedGrid = nullptr;
					UpdateBoardImage();
					state = SelectChess;
					break;
				}
				else if (m.mkRButton)
				{
					theSelectedGrid = nullptr;
					UpdateBoardImage();
					state = SelectChess;
					break;
				}
			}
			break;
		}
	}
}

void ChineseChess::ApplyMove(Grid& current, Grid& target)
{
	target.Id = current.Id;
	target.IsRed = current.IsRed;
	current.Id = 0;
}


