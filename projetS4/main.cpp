
#include <iostream>
#include "Interface.h"
#include "gestion console/menu.h"

/*source code : TP de Charles Hamery (fait avec Eloi Bastit) et Emma Collin (fait avec Julie Trochon) */

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

    return 0;
}

/*BIENVENUE ! Voici vos commandes :

< > load 'nom du fichier'
< > load ponderation 'nom du fichier'

< > calculer indices -> Calcul les indices de centralite
< > comparaison -> compare les indices
< > save indices 'nom du fichier'
< > sommet indice 'chiffre selection'
    -> affiche les sommets en couleur selon :
        -> 0 : Cd
        -> 1 : Cvp
        -> 2 : Cp
        -> 3 : Ci
        -> 4 : rien

< > supprimer (A-B) -> supprime l'arrete A-B

< > ajout graphe "nom fichier"
< > test de connexite
< > retour -> revient a l'etape precedente

< > stopAutoCin
< > startScript
< > help
< > exit
<
*/




