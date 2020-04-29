
#include <iostream>
#include "Interface.h"
#include "gestion console/menu.h"

int main()
{
    //affichageCommande();

//    int autoCin=1;
//    do
//    {
//
//        if(autoCin==2)
//            autoCin=gererDeffilement(true);
//        else
//            autoCin=gererDeffilement(false);
//
//    }while (autoCin!=1);
//
//    changerCouleurConsole(5);//rouge
//    std::cout<<std::endl<<"AU REVOIR !"<<std::endl;
//    changerCouleurConsole(4);//blanc

    /*Graphe ensemble{"graphe-test2.txt"};
    ensemble.remplirPoids("ponde-test2.txt");
    ensemble.calculCentralite();
    ensemble.afficherCentralite_Normalise(4);
    ensemble.afficherCentralite_NON_Normalise(4);
    ensemble.affichageSvg(2);*/

    Interface ensemble;
    ensemble.remplirFichier("graphe-test2.txt");
    ensemble.remplirPoids("ponde-test2.txt");
    ensemble.afficherConsole(0);
    ensemble.afficherListeAdjacence(0);

//    ensemble.affichageSvg();
    std::string s1="A";
    std::string s2="B";
    ensemble.ajoutGraphe();
    ensemble.suppArrete(s1,s2);
    ensemble.afficherConsole();
    ensemble.afficherListeAdjacence();
    s1="H";
    s2="B";
    ensemble.ajoutGraphe();
    ensemble.suppArrete(s1,s2);

    ensemble.afficherConsole();
    ensemble.afficherListeAdjacence();

    ensemble.affichageSvg();


    return 0;
}





