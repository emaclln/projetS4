
#include <iostream>
#include "Interface.h"
#include "gestion console/menu.h"

/*source code : TP de Charles Hamery (fait avec Eloi Bastit) et Emma Collin (fait avec Julie Trochon) */
/*source code : Projet S3 de Charles Hamery et Emma Collin (fait avec Julie Trochon) */


int main()
{

    //affichageCommande();

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

//    Interface ensemble;
//    ensemble.remplirFichier("graphe-test2.txt");
//    ensemble.remplirPoids("ponde-test2.txt");
//    ensemble.calculCentralite();
//    ensemble.afficherCentralite_Normalise(0);
//    std::string s1="B";
//    std::string s2="A";
//    ensemble.copieGraphe();
//    ensemble.suppArrete(s1,s2);
//    ensemble.calculCentralite();
//    ensemble.afficherCentralite_Normalise(0);
//
//    ensemble.comparaison(-1,0);



    //ensemble.affichageSvg();


    return 0;
}
