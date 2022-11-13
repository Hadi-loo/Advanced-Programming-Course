#ifndef __TABLE_HPP__
#define __TABLE_HPP__

class Table
{
public:
    Table(double w, double h);
    bool contains_point(double x, double y);
    void reflect(double &x, double &y, double &vx, double &vy);

private:
    double width;
    double height;
};

#endif