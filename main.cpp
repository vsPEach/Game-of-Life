#include <iostream>
#include <thread>
#include <fstream>

void set_alive(char** field, int x, int y)
{
    field[x][y] = '*';
}

char** init_field(int& x, int& y)
{
    std::ifstream f("setup.txt");
    f >> x >> y;
    char** field = new char *[x];
    for (int i = 0; i < x; i++)
    {
        field[i] = new char [y];
    }
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            field[i][j] = '-';
        }
    }

    while (!f.eof())
    {
        int rows, columns;
        f >> rows >> columns;
        set_alive(field, rows, columns);
    }

    return  field;
}

void print(char **field, int x, int y)
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

int main(int argc, char *argv[])
{
    int x, y;
    char **field = init_field(x, y);
    print(field, x, y);
}