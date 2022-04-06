#pragma clang diagnostic push
#pragma ide diagnostic ignored "Simplify"
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

void remove_field(char** field, int rows, int columns);

int count_alive_neighbours(char** field, int x, int y, int rows, int columns) {
    int neighbours = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 and j == 0) continue; //without counting itself

            if (x == 0 and y == 0)
                if (i == - 1 and j == -1) continue; //for top left corner

            if (x == 0 and y == columns - 1)
                if ((i == -1) or (i == 0 and j == -1) or (i == 1 and j == 1)) continue; //for top right corner

            if (x == rows - 1 and y == 0)
                if ((i == 1) or (i == -1 and j == -1) or (i == 0 and j == -1)) continue; //for bottom left corner

            if (x == rows - 1 and y == columns - 1)
                if ((i == 1) or (i == 0 and j == 1) or (i == -1 and j == 1)) continue; // for bottom right corner

            if (0 < x < rows - 1 and y == 0)
                if (j == -1) continue;

            if (0 < y < columns - 1 and x == 0)
                if (i == -1) continue;

            if (y == columns - 1 and  0 < x < rows - 1)
                if (j == 1) continue;

            if (x == rows - 1 and 0 < y < columns - 1)
                if (i == 1) continue;

            if (field[x + i][y + j] == '*') neighbours++;
        }
    }

    return neighbours;
}

void check_changes(char** field, int rows, int columns, bool& life);

char** next_generation(char** current_field, int rows, int columns) {

    char** next_field = current_field;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            if (current_field[i][j] == '-')
                if (count_alive_neighbours(current_field, i, j, rows, columns) == 3)
                    set_alive(next_field, i, j);
            if (current_field[i][j] == '*')
                if (count_alive_neighbours(current_field, i, j, rows, columns) > 3 or count_alive_neighbours(current_field, i, j, rows, columns) < 2)
                    next_field[i][j] = '-';

        }

    return next_field;
}


int main (int argc, char *argv[])
{
    int rows, columns;
    char **field = init_field(rows, columns);
    print(field, rows, columns);
    std::cout << '\n';
    char **next_field = next_generation(field, rows, columns);
    print(next_field, rows, columns);
}
