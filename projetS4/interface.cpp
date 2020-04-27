#include "structure/Interface.h"

Interface::Interface(int indice, std::string nomFichier)
{
    m_indice=indice;
    m_graphes.push_back(new Graphe {nomFichier});
}

void Interface::affichageSvg ()const
{
    m_graphes[m_indice]->affichageSvg();
}

void Interface::ajoutGraphe(Graphe* nv)
{
    m_indice=m_indice+1; //on travail tj sur le dernier graphe
    m_graphes.push_back(nv);
}

void Interface::remplirPoids(std::string nomFichier)
{
    m_graphes[m_indice]->remplirPoids(nomFichier);
}
