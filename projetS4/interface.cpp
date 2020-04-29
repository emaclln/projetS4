#include "Interface.h"



Interface::Interface()
{
    initialisation();
}

void Interface::initialisation ()
{
    m_indice=0;
}

void Interface::ajoutGraphe()
{
    Graphe* nv= new Graphe{m_graphes[m_indice]};
    m_graphes.push_back(nv);
    m_indice +=1;
}

void Interface::suppArrete(std::string& s1,std::string& s2)
{
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
    std::cout<<std::endl<<m_indice;
}

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

void Interface::afficherConsole()const
{
    std::cout<<std::endl<<m_indice;
    m_graphes[m_indice]->afficherConsole();
    std::cout<<std::endl;

}

void Interface::afficherListeAdjacence()const
{
    std::cout<<std::endl<<m_indice;
    m_graphes[m_indice]->afficherListeAdjacence();
    std::cout<<std::endl;
}

Interface::~Interface()
{
    for (auto it : m_graphes)
        delete it;
}
