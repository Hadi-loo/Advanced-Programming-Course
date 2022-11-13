#include <iostream>
#include <cstdlib>
#include "table.hpp"
#include "ball.hpp"
using namespace std;

int main()
{
    Table t(100, 50);
    Ball b(10, 20, 25, 5, &t);
    b.move(10);
}