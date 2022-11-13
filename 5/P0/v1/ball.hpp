#ifndef __BALL_HPP__
#define __BALL_HPP__
#include "table.hpp"

class Ball
{
public:
    Ball(double _x, double _y, double _vx, double _vy, Table *t);
    void move(double dt);
    double get_x();
    double get_y();
    double get_vx();
    double get_vy();

private:
    double x;
    double y;
    double vx;
    double vy;
    Table* table;
};

#endif