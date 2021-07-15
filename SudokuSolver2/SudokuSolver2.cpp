#include <array>
#include <iostream>
#include <vector>

#pragma region Types

struct Index
{
    int x, y;

    explicit Index(const int pos_x = 0, const int pos_y = 0)
    {
        x = pos_x;
        y = pos_y;
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

    int numbers[81] = {
        5,0,0,0,0,0,2,8,0,
        0,0,0,2,0,9,0,4,5,
        0,7,0,0,8,0,0,0,0,
        3,0,8,0,5,2,4,1,7,
        1,0,5,7,9,3,6,2,0,
        7,0,6,0,0,0,0,0,9,
        9,1,0,0,2,6,0,0,0,
        2,0,0,0,0,0,0,0,4,
        0,5,0,8,0,7,1,0,0
    };

    Board()
    {
        MakeSquares();
    }
    void MakeSquares()
    {
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

#pragma endregion

#pragma region Done-Checking

bool Done(Board board)
{
    for (auto& i : board.number_array)
        for (int j : i)
            if (j == 0)
                return false;	
    return true;
}

bool Done(Square square)
{
	bool done = true;
	for (auto& i : square.numbers)
		for (int j : i)
			if (j == 0)
				return false;	
	return true;	
}

#pragma endregion

#pragma region Number Finding

std::vector<Index> Find_Zeroes(int number_array[9][9])
{
    std::vector<Index> result;
    for (int a = 0; a < 9; a++)
        for(int b = 0; b < 9; b++)
            if(number_array[a][b] == 0)
                result.push_back(Index(a, b));
    return result;
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

#pragma endregion

#pragma region Converting

int GetSquareIndex(Index index)
{
    if(index.x < 3)
    {
        if(index.y < 3)
            return 0;
        if(index.y < 6)
            return  1;
        return 2;
    }
    if(index.x < 6)
    {
        if(index.y < 3)
            return 3;
        if(index.y < 6)
            return 4;
        return 5;
    }
    if(index.y < 3)
        return 6;
    if(index.y < 6)
        return  7;
    return 8;
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

bool Fits(Board board, const int number, const Index index, const int square_index)
{
    if (GetIndex(board.square_array[square_index], number).x == -1) return false;

    if (!FitsHorizontally(board, number, index) || !FitsVertically(board, number, index)) return false;
	
    return true;
}

#pragma endregion

int main()
{
    Board board;

    while (!Done(board))
    {
        std::vector<Index> zeroes = Find_Zeroes(board.number_array);

        int size = zeroes.size();
        
        std::array<std::vector<int>, size> possibleNumbers;
        for (int a = 0; a < size; a++)
        {
            std::vector<int> possibles;
            for (int number = 1; number < 10; ++number)
            {
                
            }
        }
    }
    
    return 0;
}
