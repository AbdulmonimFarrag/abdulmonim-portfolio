#include <iostream>
#include <ctime>
using namespace std;

bool AddingNewTile(int grid[4][4])
{
    int empty[16][2];
    int count = 0;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
            {
                empty[count][0] = i;
                empty[count][1] = j;
                count++;
            }

    if (count == 0) return false;

    int r = rand() % count;
    int tile = (rand() % 10 == 0) ? 4 : 2;
    grid[empty[r][0]][empty[r][1]] = tile;
    return true;
}

void PrintGrid(int grid[4][4])
{
    cout << "\nGrid:\n";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
            cout << grid[i][j] << "\t";
        cout << "\n";
    }
}

bool CheckWin(int grid[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 2048)
                return true;
    return false;
}

bool CheckGameOver(int grid[4][4])
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j] == 0)
                return false;

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i][j] == grid[i][j + 1])
                return false;

    for (int j = 0; j < 4; j++)
        for (int i = 0; i < 3; i++)
            if (grid[i][j] == grid[i + 1][j])
                return false;

    return true;
}

void reverseRow(int row[4])
{
    for (int i = 0; i < 2; i++)
        swap(row[i], row[3 - i]);
}

bool moveLine(int line[4])
{
    int old[4];
    for (int i = 0; i < 4; i++) old[i] = line[i];

    int temp[4] = { 0 }, idx = 0;

    for (int i = 0; i < 4; i++)
        if (line[i] != 0)
            temp[idx++] = line[i];

    for (int i = 0; i < 3; i++)
        if (temp[i] != 0 && temp[i] == temp[i + 1])
        {
            temp[i] *= 2;
            temp[i + 1] = 0;
        }

    int final[4] = { 0 };
    idx = 0;
    for (int i = 0; i < 4; i++)
        if (temp[i] != 0)
            final[idx++] = temp[i];

    for (int i = 0; i < 4; i++)
        line[i] = final[i];

    for (int i = 0; i < 4; i++)
        if (old[i] != line[i])
            return true;

    return false;
}

bool moveLeft(int grid[4][4])
{
    bool moved = false;
    for (int i = 0; i < 4; i++)
        if (moveLine(grid[i]))
            moved = true;
    return moved;
}

bool moveRight(int grid[4][4])
{
    bool moved = false;
    for (int i = 0; i < 4; i++)
    {
        reverseRow(grid[i]);
        if (moveLine(grid[i])) moved = true;
        reverseRow(grid[i]);
    }
    return moved;
}

bool moveUp(int grid[4][4])
{
    bool moved = false;
    for (int col = 0; col < 4; col++)
    {
        int line[4];
        for (int row = 0; row < 4; row++)
            line[row] = grid[row][col];

        if (moveLine(line)) moved = true;

        for (int row = 0; row < 4; row++)
            grid[row][col] = line[row];
    }
    return moved;
}

bool moveDown(int grid[4][4])
{
    bool moved = false;
    for (int col = 0; col < 4; col++)
    {
        int line[4];
        for (int row = 0; row < 4; row++)
            line[row] = grid[row][col];

        reverseRow(line);
        if (moveLine(line)) moved = true;
        reverseRow(line);

        for (int row = 0; row < 4; row++)
            grid[row][col] = line[row];
    }
    return moved;
}

int main()
{
    int grid[4][4] = { 0 };
    srand(time(0));

    AddingNewTile(grid);
    AddingNewTile(grid);

    char move;
    while (true)
    {
        PrintGrid(grid);
        cout << "\nMove (W A S D): ";
        cin >> move;

        bool moved = false;

        if (move == 'a' || move == 'A') moved = moveLeft(grid);
        else if (move == 'd' || move == 'D') moved = moveRight(grid);
        else if (move == 'w' || move == 'W') moved = moveUp(grid);
        else if (move == 's' || move == 'S') moved = moveDown(grid);
        else
        {
            cout << "\nInvalid move!\n";
            continue;
        }

        if (moved) AddingNewTile(grid);

        if (CheckWin(grid))
        {
            PrintGrid(grid);
            cout << "\nYOU WIN!\n";
            break;
        }

        if (CheckGameOver(grid))
        {
            PrintGrid(grid);
            cout << "\nGAME OVER!\n";
            break;
        }
    }

    return 0;
}
