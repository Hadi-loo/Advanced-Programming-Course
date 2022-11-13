#include "table.hpp"
#include <iostream>
using namespace std;

Table::Table(double w, double h)
{
    cout << "Table constructor called" << endl;
    if (w <= 0 || h <= 0)
        abort();
    width = w;
    height = h;
}

bool Table::contains_point(double x, double y)
{
    cout << "Table::contains_point called" << endl;
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Table::reflect(double &x, double &y, double &vx, double &vy)
{
    cout << "Table::reflect called2" << endl;
    if (x < 0)
    {
        x = -x;
        vx = -vx;
    }
    if (x >= width)
    {
        x = 2 * width - x;
        vx = -vx;
    }
    if (y < 0)
    {
        y = -y;
        vy = -vy;
    }
    if (y >= height)
    {
        y = 2 * height - y;
        vy = -vy;
    }
}