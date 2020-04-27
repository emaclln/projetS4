
#include <iostream>
#include "structure/interface.h"

int main()
{
    int indice=0;
    Interface ensemble{indice,"graphe-test2.txt"};
    ensemble.affichageSvg();
    ensemble.remplirPoids("ponde-test2.txt");
	ensemble.affichageSvg();

    return 0;
}





