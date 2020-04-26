#include <iostream>
#include "graphisme/svgfile.h"

int main()
{
    Svgfile plan;
    plan.addLine(20,70,80,90,"blue");
    std::cout << "Hello world!" << std::endl;
    return 0;
}

