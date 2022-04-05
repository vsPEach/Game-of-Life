#include <iostream>
#include <thread>
#include <fstream>

void set_alive(char** field, int x, int y)
{
    field[x][y] = '*';
}

char** init_field(int& rows, int& columns)
{
    std::ifstream f("setup.txt");
    f >> rows >> columns;
    char** field = new char *[rows];
    for (int i = 0; i < rows; i++)
    {
        field[i] = new char [columns];
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            field[i][j] = '-';
        }
    }

    while (!f.eof())
    {
        int x, y;
        f >> x >> y;
        set_alive(field, x, y);
    }

    return  field;
}

void print(char** field, int x, int y)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            std::cout << field[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

void print(char** field, int x, int y, bool f)
{
    std::cout << field[x][y] << std::endl;
}

int count_alive_neighbours(char **field, int x, int y, int rows, int columns)
{
    if (x == 0 and y == 0)
    {
        int neighbours = 0;
        if (field[x][y + 1] == '*') neighbours++;

        if (field[x + 1][y] == '*') neighbours++;

        if (field[x + 1][y + 1] == '*') neighbours++;

        return neighbours;
    }

    if (x == rows - 1 and y == 0)
    {
        int neighbours = 0;
        if (field[x - 1][y] == '*') neighbours++;
        if (field[x - 1][y + 1] == '*') neighbours++;

    }

    if (x == rows - 1 and y == columns - 1)
    {
        int neighbours = 0;
        if (field[x - 1][y - 1] == '*') neighbours++;

        if (field[x - 1][y] == '*') neighbours++;

        if (field[x][y - 1] == '*') neighbours++;
        return neighbours;
    }

    if (x == 0 and y == columns - 1)
    {
        int neighbours = 0;
        if (field[x - 1][y] == '*') neighbours++;
        if (field[x - 1][y - 1] == '*') neighbours++;
        if (field[x][y - 1] == '*') neighbours++;
        return neighbours;
    }

    if (x == 0 and y > 0)
    {
        int neighbours = 0;
        if (field[x][y + 1] == '*') neighbours++;
        if (field[x][y - 1] == '*') neighbours++;

        if (field[x + 1][y] == '*') neighbours++;
        if (field[x + 1][y + 1] == '*') neighbours++;
        if (field[x + 1][y - 1] == '*') neighbours++;

        return neighbours;
    }

    if ( rows > x > 0 and columns > y > 0)
    {
        int neighbours = 0;

        if (field[x + 1][y + 1] == '*') neighbours++;
        if (field[x + 1][y] == '*') neighbours++;
        if (field[x + 1][y - 1] == '*') neighbours++;

        if (field[x][y + 1] == '*') neighbours++;
        if (field[x][y - 1] == '*') neighbours++;

        if (field[x - 1][y + 1] == '*') neighbours++;
        if (field[x - 1][y] == '*') neighbours++;
        if (field[x - 1][y - 1] == '*') neighbours++;
        return neighbours;
    }

}


int main(int argc, char *argv[])
{
    int rows, columns;
    char **field = init_field(rows, columns);
    print(field, rows, columns);
    std::cout << count_alive_neighbours(field, 0, 0, rows, columns);
}