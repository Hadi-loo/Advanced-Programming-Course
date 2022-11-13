#include "ball.hpp"
#include <iostream>
using namespace std;

Ball::Ball(double _x, double _y, double _vx, double _vy, Table *t)
{
    cout << "Ball constructor called" << endl;
    table = t;
    set_location(_x, _y);
    set_speed(_vx, _vy);
    cout << "Initial position is: (" << x << ',' << y << ')' << endl;
}

void Ball::set_location(double _x, double _y)
{
    cout << "Ball::set_location called with (" << _x << ',' << _y << ')' << endl;
    if (!table->contains_point(_x, _y))
        abort();
    x = _x;
    y = _y;
}

void Ball::set_speed(double _vx, double _vy)
{
    cout << "Ball::set_speed called with (" << _vx << ',' << _vy << ')' << endl;
    vx = _vx;
    vy = _vy;
}

void Ball::move(double dt)
{
    cout << "Ball::move called" << endl;
    x += vx * dt;
    y += vy * dt;

    if (!table->contains_point(x, y))
        table->reflect(this);
    cout << "New position is: (" << x << ',' << y << ')' << endl;
}