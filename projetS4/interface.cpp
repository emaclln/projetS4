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

void Interface::affichageSvg (int selec)const
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->affichageSvg(selec);
}

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

