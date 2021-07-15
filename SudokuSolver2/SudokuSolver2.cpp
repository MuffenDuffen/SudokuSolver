#include <array>
#include <iostream>
#include <vector>

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

#pragma region Done

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

std::vector<Index> Find_Zeroes(int number_array[][])
{
    std::vector<Index> result;
    for (int a = 0; a < 9; a++)
        for(int b = 0; b < 9; b++)
            if(number_array[a][b] == 0)
                result.push_back(Index(a, b));
    return result;
}

Index GetIndex(int number_array[][], const int number)
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			if (number_array[x][y] == number)
				return Index(x, y);
		}
	}
	return Index(-1, -1);
}

#pragma endregion

int main()
{
    Board board;

    while (!Done(board))
    {
        
    }
    
    return 0;
}
