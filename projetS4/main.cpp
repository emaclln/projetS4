
#include <iostream>
#include "graphisme/svgfile.h"
#include "graphe.h"

int main()
{
    Svgfile plan;
    plan.addLine(20,70,80,90,"blue");
	Graphe graphe{"graphe.txt"};//instance de graphe
    std::cout << "Hello world!" << std::endl;
    return 0;
}




