
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

    Interface ensemble;
    ensemble.remplirFichier("graphe-test1.txt");
    ensemble.remplirPoids("ponde-test1.txt");
    ensemble.afficherConsole();
    ensemble.afficherListeAdjacence();

//    ensemble.affichageSvg();
    std::string s1="A";
    std::string s2="C";
    ensemble.ajoutGraphe();
    ensemble.suppArrete(s1,s2);
    ensemble.afficherConsole();
    ensemble.afficherListeAdjacence();
    //ensemble.affichageSvg();

//    std::string fichier="ponde-test1.txt";
//    Graphe a{"graphe-test1.txt"};
//    a.remplirPoids(fichier);
//    a.afficherConsole();
//    a.afficherListeAdjacence();
//
//    a.suppArrete(s1,s2);
//    a.afficherConsole();
//    a.afficherListeAdjacence();

    return 0;
}





