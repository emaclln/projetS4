#include "Interface.h"

Interface::Interface(int indice)
{
    m_indice=indice;
}

void Interface::creationGraphe(std::string nomFichier)
{
    m_indice +=1;
    m_graphes.push_back(new Graphe {nomFichier});
}

void Interface::affichageSvg ()const
{
    m_graphes[m_indice]->affichageSvg();
}

void Interface::remplirPoids(std::string nomFichier)
{
    m_graphes[m_indice]->remplirPoids(nomFichier);
}
