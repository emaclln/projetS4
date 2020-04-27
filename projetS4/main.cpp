
#include <iostream>
#include "structure/graphe.h"

int main()
{
	Graphe graphe{"graphe-test2.txt"};//instance de graphe
	graphe.affichageSvg();
	graphe.remplirPoids("ponde-test2.txt");
	graphe.affichageSvg();
    return 0;
}





