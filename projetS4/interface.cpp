#include "Interface.h"



Interface::Interface()//Constructeur de la classe Interface
{
    initialisation();
}

Interface::~Interface()//Destructeur
{
    for (auto it : m_graphes)
        delete it;
}

void Interface::initialisation ()//Initialise les attributs
{
    m_indice=-1;
    m_selecSVG=4;
    m_normaliseSVG=false;
    m_indice_comparantSVG=-1;
    m_comparaisonSVG=false;
}

void Interface::copieGraphe()
{
    /*On recupère les données du graphe à copier */
    std::vector<Sommet*> buffer_s = m_graphes[m_indice]->getSommets();
    std::vector<Arrete*> buffer_a = m_graphes[m_indice]->getArretes();
    bool orient = m_graphes[m_indice]->getOrientation();
    bool ponderation =m_graphes[m_indice]->getPonde();
    
    m_graphes.push_back(new Graphe {buffer_s,buffer_a,orient,ponderation} );//Création du nouveau graphe
    m_indice += 1;//mise à jour de l'indice du vector graphe
}

void Interface::suppArrete(std::string& s1,std::string& s2)
{

    if(!m_graphes[m_indice]->suppArrete(s1,s2)) //si l'arrete n'a pas ÈtÈ trouvÈ donc pas de supp
        retourEnArriere(); //on supprime le graphe crÈÈ
}



void Interface::ajouterGraphe(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});//création d'un graphe par initialisation de fichier
    m_indice +=1;
}


void Interface::affichageSvg ()const //affichage par svg
{
    Svgfile::s_verbose = false;
    Svgfile svgout;
    svgout.addGrid();

    if (!m_graphes.empty())//si m_graphe n'est pas vide
    {
        if (!m_comparaisonSVG) //affichage graphe actuel
            m_graphes[m_indice]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,m_comparaisonSVG);
        else if (m_comparaisonSVG) //affichage graphe de la comparaison
        {
            m_graphes[m_indice_comparantSVG]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,1);
            m_graphes[m_indice]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,2);
        }
    }
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

void Interface::ajouterArrete(std::string& s1,std::string& s2)//En paramètre les noms des sommets selectionnées
{
    m_graphes[m_indice]->ajoutArrete(s1, s2);
}

void Interface::afficherCentralite_Normalise(int selec)//En paramètre un int pour connaître ce qu'on affiche
{
    m_graphes[m_indice]->afficherCentralite_Normalise(selec);
}

void Interface::afficherCentralite_NON_Normalise(int selec)//En paramètre un int pour connaître ce qu'on affiche
{
    m_graphes[m_indice]->afficherCentralite_NON_Normalise(selec);
}

void Interface::calculCentralite()
{
    m_graphes[m_indice]->calculCentralite();
}

void Interface::sauvegarderCentralite(std::string nomFichier)//En paramètre le nom du fichier de sauvegarde
{
    m_graphes[m_indice]->sauvegardeCentralite(nomFichier);
}

void Interface::retourEnArriere()
{
    int selec = (int) m_graphes.size() - 1;
    if (selec > 0)
    {
        delete m_graphes[selec];
        m_indice = selec -1;
    }
    else
        std::cout<<std::endl<<"Retour en arriere impossible";

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

    int id_dernier=(int) m_graphes.size(); //conversion du size_t en int

    if (indice_compare >= 0 && indice_compare < id_dernier)//verifie numÈro positif et inferieur ‡ size
    {
        m_graphes[m_indice]->calculCentralite(); //graphe actuel
        m_graphes[indice_compare]->calculCentralite();

        //pour l'affichage SVG
        set_indice_comparantSVG(indice_compare);
        setComparaisonSVG(1); //affichae 2 graphes

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

            setSelecSVG(selec); //pour l'affichage des indice
            setNormaliseSVG(true); //pour l'affichage des indice
        }
        else if (selec == 1 || selec ==2 || selec==4)
            std::cout<<std::endl<<"En l'absence de poids, le calcul du Cvp et du Cp est impossible";
        if(selec == 0 || selec == 4)
        {
            comparaisonCd(actuel,comparant);
            setSelecSVG(selec);
            setNormaliseSVG(true); //pour l'affichage des indice
        }
        if(selec == 3 || selec == 4)
        {
            comparaisonCi(actuel,comparant);
            setSelecSVG(selec);
            setNormaliseSVG(true);
        }



    }
    else
        std::cout<<"Numero d'etape invalide";

}

void Interface::comparaisonCvp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisÈ
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de vecteur propre des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cvp(true)-comparant[i]->get_Cvp(true))/comparant[i]->get_Cvp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCd(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisÈ
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de degre des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cd(true)-comparant[i]->get_Cd(true))/comparant[i]->get_Cd(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisÈ
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de proximite des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cp(true)-comparant[i]->get_Cp(true))/comparant[i]->get_Cp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCi(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisÈ
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee d'intermediarite des sommets :";
    for (size_t i=0;i<actuel.size();++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                           <<((actuel[i]->get_Ci(true)-comparant[i]->get_Ci(true))/comparant[i]->get_Ci(true))*100
                           <<"%";
    }
}

void Interface::set_indice_comparantSVG(int indice)
{
    m_indice_comparantSVG=indice;
}

void Interface::setComparaisonSVG(bool comparaison)
{
  m_comparaisonSVG=comparaison;
}

int Interface::getComparaisonSVG()const
{
    return m_comparaisonSVG;
}

bool Interface::get_indice_comparantSVG()const
{
    return m_indice_comparantSVG;
}

void Interface::k_connexite()
{
    m_graphes[m_indice]->k_connexite();
}
