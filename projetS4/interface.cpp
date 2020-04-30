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
    m_normaliseSVG=false;
}

void Interface::copieGraphe()
{
    std::vector<Sommet*> buffer_s = m_graphes[m_indice]->getSommets();
    std::vector<Arrete*> buffer_a = m_graphes[m_indice]->getArretes();
    bool orient = m_graphes[m_indice]->getOrientation();
    bool ponderation =m_graphes[m_indice]->getPonde();
    m_graphes.push_back(new Graphe {buffer_s,buffer_a,orient,ponderation} );
    m_indice += 1;
}

void Interface::suppArrete(std::string& s1,std::string& s2)
{

    if(!m_graphes[m_indice]->suppArrete(s1,s2)) //si l'arrete n'a pas été trouvé donc pas de supp
        retourEnArriere(); //on supprime le graphe créé
}



void Interface::remplirFichier(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});
    m_indice +=1;
}


void Interface::affichageSvg ()const
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->affichageSvg(m_selecSVG,m_normaliseSVG);
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


void Interface::connexite()
{
    if(m_graphes[m_indice]->connexite())
        std::cout<<"Le graphe selectionne est un graphe connexe"<<std::endl;
    else
        std::cout<<"Le graphe selectionne n'est pas un graphe connexe"<<std::endl;
}

void Interface::setNormaliseSVG(bool normalise)
{
    m_normaliseSVG=normalise;
}

void Interface::setIndice(int indice)
{
    if (indice>0)
        m_indice=indice;
    else
        std::cout<<std::endl<<"Indice invalide";
}

int Interface::getIndice()const
{
    return m_indice;
}

void Interface::comparaison(int indice_compare, int selec)
{
    if (indice_compare==-1) //etape precedente
        indice_compare=m_indice-1;

    int id_dernier=m_graphes.size(); //conversion du size_t en int

    if (indice_compare >= 0 && indice_compare < id_dernier)//verifie numéro positif et inferieur à size
    {
        m_graphes[m_indice]->calculCentralite(); //graphe actuel
        m_graphes[indice_compare]->calculCentralite();

        //calcul de difference
        std::vector<Sommet*> actuel=m_graphes[m_indice]->getSommets();
        std::vector<Sommet*> comparant=m_graphes[indice_compare]->getSommets();

        std::cout<<std::endl<<"Comparaison des inidices pour chaque sommet :";

        if(m_graphes[m_indice]->getPonde())
        {
            if(selec == 1 || selec == 4)
                comparaisonCvp(actuel,comparant);
            if(selec == 2 || selec == 4)
                comparaisonCp(actuel,comparant);
        }
        if(selec == 0 || selec == 4)
            comparaisonCd(actuel,comparant);

//        if(selec == 3 || selec == 4)
//            comparaisonCi(actuel,comparant);
    }
    else
        std::cout<<"Numero d'etape invalide";

}

void Interface::comparaisonCvp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de vecteur propre des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cvp(true)-comparant[i]->get_Cvp(true))/comparant[i]->get_Cvp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCd(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de degre des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cd(true)-comparant[i]->get_Cd(true))/comparant[i]->get_Cd(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de proximite des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cp(true)-comparant[i]->get_Cp(true))/comparant[i]->get_Cp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCi(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
//    std::cout<<std::endl<<"Affichage de la centralite normalisee d'intermediarite des sommets :";
//    for (size_t i=0;i<actuel.size();++i)
//    {
//        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
//                           <<((actuel[i]->get_Ci(true)-comparant[i]->get_Ci(true))/comparant[i]->get_Ci(true))*100
//                           <<"%";
//    }
}
