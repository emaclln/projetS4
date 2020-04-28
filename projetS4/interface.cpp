#include "Interface.h"



Interface::Interface()
{
    initialisation();
}

void Interface::initialisation ()
{
    m_indice=0;
}

void Interface::ajoutGraphe(std::string& s1,std::string& s2)
{
    Graphe* nv= new Graphe{m_graphes[m_indice]};
    m_graphes.push_back(nv);
    m_indice +=1;
    m_graphes[m_indice]->suppArrete(s1,s2);
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

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

