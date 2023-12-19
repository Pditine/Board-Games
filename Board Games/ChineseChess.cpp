#include <Socket.h>
#include "ChineseChess.h"
#include <graphics.h>
#include <string>
#include "DEBUG.h"
#include "GameManager.h"
ChineseChess::ChineseChess()
{
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
	loadimage(_gameIcon, "Resources/ChineseChess/ChineseChessIcon.png");
	
}

std::string ChineseChess::OutputInformation(Grid& current, Grid& target)
{
	return std::to_string(current.x) + std::to_string(current.y) + std::to_string(target.x) + std::to_string(target.y);
}

std::string ChineseChess::Operate() 
{
	Log("操作");
	MOUSEMSG m = GetMouseMsg();
	while (true)
	{
		switch (state)
		{
		case SelectChess:
			while (true)
			{
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
						//WinOrLoseCheck(id, isRed);
						Log("操作输出:");
						Log(OutputInformation(*selectGrid, *targetGrid));
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
	return nullptr;
}

void ChineseChess::SendBoardMessage(const std::string& message)
{
	Log("发送信息:"+message);
	Socket->Send(message.c_str(),static_cast<int>(strlen(message.c_str())));
}

std::string ChineseChess::ReceiveBoardMessage() 
{
	Log("接受开始");
	char message[5];
	const int bytes_received = Socket->Receive(message, sizeof(message));
	if (bytes_received > 0)
		Log("接受成功");
	else
		Log("接受失败");

	message[bytes_received] = '\0';

	Log(message);
	int currentX = (int)message[0] - '0';
	int currentY = (int)message[1] - '0';
	int targetX = (int)message[2] - '0';
	int targetY = (int)message[3] - '0';

	int id = map[targetY][targetX].Id;
	bool isRed = map[targetY][targetX].IsRed;
	ApplyMove(map[currentY][currentX], map[targetY][targetX]);
	theSelectedGrid = nullptr;
	return message;
}

void ChineseChess::UpdateBoardImage() 
{
	Log("更新地图");
	putimage(0, 0, chessBoard);
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 9; x++)
			drawAlpha(map[y][x].IsRed ? &redChessPieceImages[map[y][x].Id] : &blackChessPieceImages[map[y][x].Id], x * GRIDWIDTH, y * GRIDWIDTH);
	if (theSelectedGrid != nullptr)
		drawAlpha(chessFrame, theSelectedGrid->x * GRIDWIDTH, theSelectedGrid->y * GRIDWIDTH);
}

bool ChineseChess::GameOverCheck() 
{
	Log("结束检测");
	bool redIsWin = true;
	bool blackIsWin = true;
	for (int y = 0; y <= 2; y++)
		for (int x = 3; x <= 5; x++)
		{
			if(map[y][x].Id == 7)
			{
				blackIsWin = false;
				break;
			}
		}
	for (int y = 7; y <= 9; y++)
		for (int x = 3; x <= 5; x++)
		{
			if (map[y][x].Id == 7)
			{
				redIsWin = false;
				break;
			}
		}
	if (redIsWin)
	{
		GameManager::Instance()->OnGameOver(redWin);
		return true;
	}
	if (blackIsWin)
	{
		GameManager::Instance()->OnGameOver(blackWin);
		return true;
	}
	return false;
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
	Log("初始化游戏");
	InitMap();
	initgraph(377, 417);
	putimage(0, 0, chessBoard);
	UpdateBoardImage();
}

void ChineseChess::ApplyMove(Grid& current, Grid& target)
{
	target.Id = current.Id;
	target.IsRed = current.IsRed;
	current.Id = 0;
}


