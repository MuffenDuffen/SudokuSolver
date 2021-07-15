#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

#pragma region Types

struct Index
{
	int x, y, xy;

	explicit Index(const int pos_x = 0, const int pos_y = 0)
	{
		x = pos_x;
		y = pos_y;
		xy = x + y;
	}
};

struct Square
{
	int numbers[3][3]{};

	explicit Square(std::vector<int> nums = {0,0,0,0,0,0,0,0,0})
	{
		for (int i = 0; i < 9; i++)
		{
			numbers[i / 3][i % 3] = nums[i];
		}
	}
};

class Board
{
public:
	// int number_array[9][9] = {
	// 	{5,3,0,4,2,0,0,0,9},
	// 	{0,0,0,0,0,0,0,5,1},
	// 	{0,7,0,0,0,8,4,0,0},
	// 	{8,0,0,0,3,5,0,7,2},
	// 	{0,2,0,0,0,0,3,0,0},
	// 	{9,0,0,0,0,0,0,0,8},
	// 	{0,0,0,0,0,9,1,0,0},
	// 	{0,8,0,0,1,0,0,0,0},
	// 	{0,0,0,7,0,0,0,2,4}
	// };

	int number_array[9][9] = {
		{5,0,0,0,0,0,2,8,0},
		{0,0,0,2,0,9,0,4,5},
		{0,7,0,0,8,0,0,0,0},
		{3,0,8,0,5,2,4,1,7},
		{1,0,5,7,9,3,6,2,0},
		{7,0,6,0,0,0,0,0,9},
		{9,1,0,0,2,6,0,0,0},
		{2,0,0,0,0,0,0,0,4},
		{0,5,0,8,0,7,1,0,0}
	};
	
	std::array<Square, 9> square_array;

	Board()
	{
		int numbers[81];

		for (int i = 0; i < 81; ++i)
		{
			numbers[i] = number_array[i / 9][i % 9];
		}

		int index = 0;
		for (int a = 0; a < 81; a+=27)
		{
			for (int b = 0; b < 9; b += 3)
			{
				std::vector<int> squareNumbers;
				squareNumbers.reserve(9);
				for (int c = 0;c < 27; c += 9)
				{
					for (int d = 0; d < 3; ++d)
					{
						squareNumbers.push_back(numbers[a + b + c + d]);
					}
				}
				square_array[index] = Square(squareNumbers);
				index++;
			}
		}
	}
};

//{ 5, 3, 0, 4, 2, 0, 0, 0, 9 }
//{ 0, 0, 0, 0, 0, 0, 0, 5, 1 }
//{ 0, 7, 0, 0, 0, 8, 4, 0, 0 }
//{ 8, 0, 0, 0, 3, 5, 0, 7, 2 }
//{ 0, 2, 0, 0, 0, 0, 3, 0, 0 }
//{ 9, 0, 0, 0, 0, 0, 0, 0, 8 }
//{ 0, 0, 0, 0, 0, 9, 1, 0, 0 }
//{ 0, 8, 0, 0, 1, 0, 0, 0, 0 }
//{ 0, 0, 0, 7, 0, 0, 0, 2, 4 }

#pragma endregion 

#pragma region Done-Check
bool Done(Square square)
{
	bool done = true;
	for (auto& i : square.numbers)
		for (int j : i)
			if (j == 0)
				return false;	
	return true;	
}

bool Done(Board board)
{
	for (auto& i : board.number_array)
		for (int j : i)
			if (j == 0)
				return false;	
	return true;
}
#pragma endregion

#pragma region Getting Index
std::vector<Index> ZeroIndex(Square square)
{
	std::vector<Index> indexes;
	indexes.reserve(9);
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (square.numbers[x][y] == 0)
				indexes.emplace_back(x, y);
		}
	}
	return indexes;
}
Index GetIndex(Square square, const int number)
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (square.numbers[x][y] == number)
				return Index(x, y);
		}
	}
	return Index(-1, -1);
}

Index ToBoardIndex (Index square_index, const int square)
{
	switch (square)
	{
	case 0:
		break;
	case 1:
		square_index.y += 3;
		break;
	case 2:
		square_index.y += 6;
		break;
	case 3:
		square_index.x += 3;
		break;
	case 4:
		square_index.y += 3;
		square_index.x += 3;
		break;
	case 5:
		square_index.y += 6;
		square_index.x += 3;
		break;
	case 6:
		square_index.x += 6;
		break;
	case 7:
		square_index.y += 3;
		square_index.x += 6;
		break;
	case 8:
		square_index.y += 6;
		square_index.x += 6;
		break;
	default:
		break;
	}
	return square_index;
}

#pragma endregion

#pragma region Fitting

bool FitsHorizontally(Board board, const int fit, const Index pos)
{
	for (int i = 0; i < 9; ++i) if (board.number_array[pos.x][i] == fit) return false;
	return true;
}
bool FitsVertically(Board board, const int fit, const Index pos)
{
	for (int i = 0; i < 9; ++i) if (board.number_array[i][pos.y] == fit) return false;
	return true;
}

bool Fits(Board board, const int number, Index board_2d_index, const int square_index)
{
	if (GetIndex(board.square_array[square_index], number).xy != -2) return false; //TODO make function do more

	if (!FitsHorizontally(board, number, board_2d_index) || !FitsVertically(board, number, board_2d_index)) return false;
	
	return true;
}

std::vector<int> OnlyNumber(const std::vector<int>& numbers)
{
	std::vector<int> onlyNumbers;
	onlyNumbers.reserve(numbers.size());

	for (int number : numbers)
	{
		auto iterator1 = std::find(numbers.begin(), numbers.end(), number);
		auto iterator2 = std::find(numbers.rbegin(), numbers.rend(), number);

		if (std::distance(numbers.begin(), iterator1) == std::distance(iterator2, numbers.rend() - 1))
			onlyNumbers.emplace_back(number);
	}
	
	onlyNumbers.shrink_to_fit();
	return onlyNumbers;
}

#pragma endregion

void OutputBoard(Board board)
{
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 9; ++j)
		{
			std::cout << board.number_array[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int main()
{
	Board board;
	Board previousBoard;

	while (!Done(board))
	{
		previousBoard = board;
		for (int i = 0; i < board.square_array.size(); i++)
		{
			Square square = board.square_array[i];
			if (!Done(square))
			{
				std::vector<Index> indexOfZero = ZeroIndex(square);

				std::vector<int> possibleSquareNumbers;
				std::vector<int> possiblePositions;

				for (const auto zero : indexOfZero)
				{
					std::vector<int> possibleNumbers;
					for (int j = 1; j < 10; ++j)
					{
						if (Fits(board, j, ToBoardIndex(zero, i), i))
						{
							possibleNumbers.emplace_back(j);
						}
					}

					possibleSquareNumbers.insert(possibleSquareNumbers.end(), possibleNumbers.begin(), possibleNumbers.end());
					possiblePositions.emplace_back(possibleNumbers.size());

					// If only one fits, insert it.
					if(possibleNumbers.size() == 1)
					{
						board.number_array[ToBoardIndex(zero, i).x][ToBoardIndex(zero, i).y] = possibleNumbers[0];
					}
				}
				
				// If only one spot in a square can fit a number, insert it
				std::vector<int> onlyPossible = OnlyNumber(possibleSquareNumbers);
				
				std::vector<std::vector<int>> lol;
				lol.reserve(possiblePositions.size());

				int index = 0;
				for (int j = 0; j < possiblePositions.size(); j++)
				{
					std::vector<int> possibleNumbers;
					possibleNumbers.reserve(possiblePositions.size());
					
					for (int k = 0; k < possiblePositions[j]; ++k)
					{
						possibleNumbers.emplace_back(possibleSquareNumbers[index + k]);

						for (int l = 0; l < onlyPossible.size(); ++l)
						{
							if (possibleSquareNumbers[index + k] == onlyPossible[l]) // 
							{
								board.number_array[ToBoardIndex(indexOfZero[j], i).x][ToBoardIndex(indexOfZero[j], i).y] = onlyPossible[l];
							}
						}
						
					}
					index += possiblePositions[j];
					
					lol.emplace_back(possibleNumbers);
				}
			}
		}

		bool changed = false;
		for (int a = 0; a < 9; ++a)
			for (int b = 0; b < 9; ++b)
				if (board.number_array[a][b] != previousBoard.number_array[a][b])
					changed = true;
		if (changed) OutputBoard(board);
	}

	std::cout << "DONE\n";
	OutputBoard(board);
	
	return 0;
}