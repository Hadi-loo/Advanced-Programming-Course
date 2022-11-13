#include "table.hpp"
#include "ball.hpp"
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

void Table::reflect(Ball *b)
{
    cout << "Table::reflect called" << endl;
    double x = b->get_x();
    double y = b->get_y();
    double vx = b->get_vx();
    double vy = b->get_vy();

    while (!contains_point(x, y))
    {
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
    b->set_location(x, y);
    b->set_speed(vx, vy);
}