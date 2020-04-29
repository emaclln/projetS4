#include "Interface.h"



Interface::Interface()
{
    initialisation();
}

void Interface::initialisation ()
{
    m_indice=0;
    m_selecSVG=4;
}

void Interface::ajoutGraphe()
{
    std::vector<Sommet*> buffer_s = m_graphes[m_indice]->getSommets();
    std::vector<Arrete*> buffer_a = m_graphes[m_indice]->getArretes();
    int orient=m_graphes[m_indice]->getOrientation();
    m_graphes.push_back(new Graphe {buffer_s,buffer_a,orient});
    m_indice +=1;
}

void Interface::suppArrete(std::string& s1,std::string& s2,int i)
{
    if (i<0)
        m_graphes[m_indice]->suppArrete(s1,s2);
    else
        m_graphes[i]->suppArrete(s1,s2);

    std::cout<<std::endl<<"-"<<s1<<"-"<<s2<<"-";
}



void Interface::remplirFichier(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});
}


void Interface::affichageSvg ()const
{
    if (!m_graphes.empty())
    {
        if (i<0)
            m_graphes[m_indice]->affichageSvg(1);
        else
            m_graphes[i]->affichageSvg(1);
        m_graphes[m_indice]->affichageSvg(m_selecSVG);
	}

}

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

void Interface::afficherConsole(int i)const
{
    if (i<0)
        m_graphes[m_indice]->afficherConsole();
    else
        m_graphes[i]->afficherConsole();
    std::cout<<std::endl;
}

void Interface::afficherListeAdjacence(int i)const
{
    if (i<0)
        m_graphes[m_indice]->afficherListeAdjacence();
    else
        m_graphes[i]->afficherListeAdjacence();
    std::cout<<std::endl;
}

Interface::~Interface()
{
    for (auto it : m_graphes)
        delete it;
}
