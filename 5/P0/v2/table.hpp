#ifndef _TABLE_HPP_
#define _TABLE_HPP_

class Ball;

class Table
{
public:
    Table(double w, double h);
    bool contains_point(double x, double y);
    void reflect(Ball *b);

private:
    double width;
    double height;
};

#endif