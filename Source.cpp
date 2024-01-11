#include <iostream>
#include <vector>

#define NeedLengthForWin 3

#define Player1 1
#define Player2 2

#define WonSide_Unknown -1
#define WonSide_Tie 0

#define UnknownTile -1
#define FreeTile 0
#define CrossTile 1
#define TacTile 2

std::vector<std::pair<short, short>> Directions = {
	std::pair<short, short>{-1, 1}, std::pair<short, short>{0, 1}, std::pair<short, short>{1, 1},
	std::pair<short, short>{-1, 0}, std::pair<short, short>{1, 0},
	std::pair<short, short>{-1, -1}, std::pair<short, short>{0, -1}, std::pair<short, short>{1, -1},
};

std::vector<std::vector<std::pair<short, short>>> PossibleWins = {
	std::vector<std::pair<short, short>>{ {0,0}, {0,1}, {0,2} },
	std::vector<std::pair<short, short>>{ {1,0}, {1,1}, {1,2} },
	std::vector<std::pair<short, short>>{ {2,0}, {2,1}, {2,2} },
	std::vector<std::pair<short, short>>{ {0,0}, {1,0}, {2,0} },
	std::vector<std::pair<short, short>>{ {0,1}, {1,1}, {2,1} },
	std::vector<std::pair<short, short>>{ {0,2}, {1,2}, {2,2} },
	std::vector<std::pair<short, short>>{ {0,0}, {1,1}, {2,2} },
	std::vector<std::pair<short, short>>{ {2,0}, {1,1}, {0,2} }
};

short CurrentSideStep = Player1;
short WonSide = WonSide_Unknown;

std::vector<std::vector<short>> ClearBoard = {
	{FreeTile, FreeTile, FreeTile},
	{FreeTile, FreeTile, FreeTile},
	{FreeTile, FreeTile, FreeTile}
};

std::vector<std::vector<short>> Board = ClearBoard;

void DrawBoard()
{
	for (short Y = 0; Y < 3; Y++)
	{
		if (Y == 0)
		{
			std::cout << "  ";
			for (short Letter = 0; Letter < 3; Letter++)
				std::cout << " " << char(Letter + 'A') << "  ";
			std::cout << "\n";
		}
		for (short X = 0; X < 3; X++)
		{
			if (X == 0)
				std::cout << Y + 1 << " ";
			std::cout << " ";
			if (Board[Y][X] == FreeTile)
				std::cout << " ";
			else if (Board[Y][X] == CrossTile)
				std::cout << "x";
			else
				std::cout << "o";
			std::cout << " ";
			if (X != 2)
				std::cout << "|";
		}
		if (Y != 2)
			std::cout << "\n  ---+---+---\n";
	}
}

int main()
{
	while (true)
	{
		while (WonSide == WonSide_Unknown)
		{
			std::string UserInput = "";
			DrawBoard();
			std::cout << "\nEnter your step(" << (CurrentSideStep == Player1 ? "x" : "o") << "):\n";
			std::cin >> UserInput;
			system("cls");
			if (UserInput == "Restart" || UserInput == "R" || UserInput == "r")
			{
				CurrentSideStep = Player1;
				WonSide = WonSide_Unknown;
				Board = ClearBoard;
			}
			else if (UserInput == "Quit" || UserInput == "Q" || UserInput == "q")
				break;
			else if (UserInput.length() != 2)
				std::cout << "Wrong Step!\n";
			else
			{
				int X = 0, Y = UserInput[1] - '1';
				if (UserInput[0] >= 'A' && UserInput[0] <= 'C') X = UserInput[0] - 'A';
				else if (UserInput[0] >= 'a' && UserInput[0] <= 'c') X = UserInput[0] - 'a';
				if (X >= 0 && X <= 2 && Y >= 0 && Y <= 2)
				{
					if (Board[Y][X] == FreeTile)
					{
						Board[Y][X] = (CurrentSideStep == Player1 ? CrossTile : TacTile);
						int PossibleSteps = 0;
						for (std::vector<std::pair<short, short>> PossibleWinArray : PossibleWins)
						{
							short TilesLength = 1;
							short NeedTile = UnknownTile;
							for (std::pair<short, short> Position : PossibleWinArray)
							{
								short CurrentTile = Board[Position.second][Position.first];
								if (NeedTile == UnknownTile) NeedTile = CurrentTile;
								else if (CurrentTile == NeedTile && CurrentTile != FreeTile) TilesLength++;

								if (CurrentTile == FreeTile) PossibleSteps++;
							}
							if (TilesLength == NeedLengthForWin)
								WonSide = NeedTile == CrossTile ? Player1 : Player2;
						}
						if (PossibleSteps == 0 && WonSide == WonSide_Unknown)
							WonSide = WonSide_Tie;
						CurrentSideStep = (CurrentSideStep == Player1 ? Player2 : Player1);
					}
					else
						std::cout << "Position Already Claimed!\n";
				}
				else
					std::cout << "Wrong Step Position!\n";
			}
		}
		std::string UserInput = "";
		DrawBoard();
		if (WonSide == WonSide_Tie)
			std::cout << "\nNo one Won. Tie!";
		else
			std::cout << "\nWon: Player" << WonSide << "(" << (WonSide == Player1 ? "x" : "o") << ")";
		std::cout << "\nType \"Restart\" or \"R\" or \"r\" For restart the Game\nType \"Quit\" or \"Q\" or \"q\" For quit the Game(Or press Ctrl+C)\n";
		std::cin >> UserInput;
		if (UserInput == "Restart" || UserInput == "R" || UserInput == "r")
		{
			CurrentSideStep = Player1;
			WonSide = WonSide_Unknown;
			Board = ClearBoard;
		}
		else if (UserInput == "Quit" || UserInput == "Q" || UserInput == "q")
			break;
		system("cls");
	}
	return 0;
}
