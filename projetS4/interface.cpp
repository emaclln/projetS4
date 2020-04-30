#include "Interface.h"



Interface::Interface()
{
    initialisation();
}

Interface::~Interface()
{
    for (auto it : m_graphes)
        delete it;
}

void Interface::initialisation ()
{
    m_indice=-1;
    m_selecSVG=4;
}

void Interface::copieGraphe()
{
    std::vector<Sommet*> buffer_s = m_graphes[m_indice]->getSommets();
    std::vector<Arrete*> buffer_a = m_graphes[m_indice]->getArretes();
    bool orient = m_graphes[m_indice]->getOrientation();
    m_graphes.push_back(new Graphe {buffer_s,buffer_a,orient} );
    m_indice += 1;
}

void Interface::suppArrete(std::string& s1,std::string& s2)
{

    m_graphes[m_indice]->suppArrete(s1,s2);

}



void Interface::remplirFichier(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});
    m_indice +=1;
}


void Interface::affichageSvg ()const
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->affichageSvg(m_selecSVG);

}

void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

void Interface::afficherConsole()const
{
    m_graphes[m_indice]->afficherConsole();
    std::cout<<std::endl;
}

void Interface::afficherListeAdjacence()const
{
    m_graphes[m_indice]->afficherListeAdjacence();
    std::cout<<std::endl;
}

void Interface::ajouterArrete(std::string& s1,std::string& s2)
{
    m_graphes[m_indice]->ajoutArrete(s1, s2);
}

void Interface::afficherCentralite_Normalise(int selec)
{
    m_graphes[m_indice]->afficherCentralite_Normalise(selec);
}

void Interface::afficherCentralite_NON_Normalise(int selec)
{
    m_graphes[m_indice]->afficherCentralite_NON_Normalise(selec);
}

void Interface::calculCentralite()
{
    m_graphes[m_indice]->calculCentralite();
}

void Interface::sauvegarderCentralite(std::string nomFichier)
{
    m_graphes[m_indice]->sauvegardeCentralite(nomFichier);
}

void Interface::retourEnArriere()
{
    int selec = (int) m_graphes.size() - 1;
    delete m_graphes[selec];
    m_indice = selec -1;
}

void Interface::setSelecSVG(int selec)
{
    m_selecSVG = selec;
}

void Interface::setIndice(int indice)
{
    if (indice>0)
        m_indice=indice;
    else
        std::cout<<std::endl<<"Indice invalide";
}
