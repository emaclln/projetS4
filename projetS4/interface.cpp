#include "Interface.h"

Interface::Interface(int indice, std::string nomFichier)
{
    m_indice=indice;
    m_graphes.push_back(new Graphe {nomFichier});
}

Interface::Interface()
{
    initialisation();
}

void Interface::initialisation ()
{
    m_indice=0;
}

void Interface::remplirFichier(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});
}

void Interface::affichageSvg ()const
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->affichageSvg();
}

void Interface::ajoutGraphe(Graphe* nv)
{
    m_indice=m_indice+1; //on travail tj sur le dernier graphe
    m_graphes.push_back(nv);
}

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

