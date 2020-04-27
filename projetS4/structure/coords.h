//
//  coord.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef coord_h
#define coord_h

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
};
#endif /* coord_hpp */

