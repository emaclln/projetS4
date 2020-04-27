#ifndef COORDS_H_INCLUDED
#define COORDS_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <stack>
#include <map>


class Coord
{
private :
    int m_x;
    int m_y;

public :
    void set_coord(int x, int y);
    int getY()const;
    int getX()const;

};

#endif // COORDS_H_INCLUDED
