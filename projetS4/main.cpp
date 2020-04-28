
#include <iostream>
#include "Interface.h"
#include "gestion console/menu.h"

int main()
{
    affichageCommande();

    int autoCin=1;
    do
    {

        if(autoCin==2)
            autoCin=gererDeffilement(true);
        else
            autoCin=gererDeffilement(false);

    }while (autoCin!=1);

    changerCouleurConsole(5);//rouge
    std::cout<<std::endl<<"AU REVOIR !"<<std::endl;
    changerCouleurConsole(4);//blanc

//    Interface ensemble{indice,"graphe-test2.txt"};
//    ensemble.affichageSvg();
//    ensemble.remplirPoids("ponde-test2.txt");
//	ensemble.affichageSvg();

    return 0;
}





