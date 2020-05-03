
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
//    ensemble.afficherConsole();
//    ensemble.k_connexite();


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
< > ajouter (A-B) -> ajoute l'arrete A-B

< > ajout graphe "nom fichier"
< > test de connexite
< > retour -> revient a l'etape precedente

< > stopAutoCin
< > startScript
< > help
< > exit
<
*/


/*void Graphe::caculCi()
{
   std::map<int,std::pair< int,std::vector< std::vector<int>>> > cheminIndice;
    int depart = 0;
    int arrive = 5;

    std::queue<Sommet*> maFile;//file créé
    maFile.push(m_sommets[depart]);//on note se sommet dans file

    while(!maFile.empty())//tant que file pas null
    {
        int *nbre = new int;
        *nbre = maFile.front()->getId();//on retient ID du sommet
        maFile.pop();//on libère la file

        if(*nbre != arrive)
        {
            for(auto s : m_sommets[*nbre]->getAdjacent())//pour chaque adjacent
            {
                if(s.first->getId() != depart)//si blanc
                {
                    maFile.push(s.first);//rajoute à file

                    if (cheminIndice.find(s.first->getId()) != cheminIndice.end())
                    {
                        if(cheminIndice[s.first->getId()].first > cheminIndice[m_sommets[*nbre]->getId()].first+1)
                        {
                            std::pair< int,std::vector< std::vector<int>>> buffer = cheminIndice[m_sommets[*nbre]->getId()];
                            for(auto i : buffer.second)
                                i.push_back(m_sommets[*nbre]->getId());
                            buffer.first += 1;
                            cheminIndice[s.first->getId()] = buffer;
                        }
                        if(cheminIndice[s.first->getId()].first == cheminIndice[m_sommets[*nbre]->getId()].first+1)
                        {
                            std::pair< int,std::vector< std::vector<int>>> buffer = cheminIndice[m_sommets[*nbre]->getId()];
                            std::pair< int,std::vector< std::vector<int>>> buffer1 = cheminIndice[s.first->getId()];
                            for(auto i : buffer.second)
                            {
                                i.push_back(m_sommets[*nbre]->getId());
                                buffer1.second.push_back(i);
                            }
                            cheminIndice[s.first->getId()] = buffer1;
                        }
                    }
                    else
                    {
                        if(cheminIndice.find(m_sommets[*nbre]->getId()) != cheminIndice.end())
                        {
                            std::pair< int,std::vector< std::vector<int>>> buffer = cheminIndice[m_sommets[*nbre]->getId()];
                            for(auto i : buffer.second)
                                i.push_back(m_sommets[*nbre]->getId());
                            buffer.first += 1;
                            cheminIndice[s.first->getId()] = buffer;
                        }
                        else
                        {
                            std::pair< int,std::vector< std::vector<int>>> buffer;
                            std::vector<int> buffer1;
                            buffer1.push_back(m_sommets[*nbre]->getId());
                            buffer.first = 1;
                            buffer.second.push_back(buffer1);
                            cheminIndice[s.first->getId()] = buffer;
                        }
                    }
                }
            }
        }
        delete nbre;//libère mémoire
    }

}*/

