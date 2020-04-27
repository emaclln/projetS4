#include "coords.h"

void Coord::set_coord(int x, int y)
{
    m_x = x;
    m_y = y;
}

int Coord::getX()const
{
    return m_x;
}

int Coord::getY()const
{
    return m_y;
}
