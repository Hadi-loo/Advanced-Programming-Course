#ifndef _BALL_HPP_
#define _BALL_HPP_

#include "table.hpp"

class Ball
{
public:
    Ball(double _x, double _y, double _vx, double _vy, Table *t);
    void move(double dt);
    double get_x() { return x; }
    double get_y() { return y; }
    double get_vx() { return vx; }
    double get_vy() { return vy; }
    void set_location(double _x, double _y);
    void set_speed(double _vx, double _vy);

private:
    double x;
    double y;
    double vx;
    double vy;
    Table *table;
};

#endif