#include "Interface.h"


/// Constructeur de la classe Interface ///
Interface::Interface()
{
    initialisation();
}

/// Destructeur ///
Interface::~Interface()
{
    for (auto it : m_graphes)
        delete it;
}

/// Initialise les attributs ///
void Interface::initialisation ()
{
    m_indice=-1;
    m_selecSVG=4;
    m_normaliseSVG=false;
    m_indice_comparantSVG=-1;
    m_comparaisonSVG=false;
    m_graphes.clear();
}

/// Ajoute un graphe par copie de celui actuel ///
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

/// Supprime l'arrete choisie par l'utilisateur ///
void Interface::suppArrete(std::string& s1,std::string& s2)
{
    if(!m_graphes[m_indice]->suppArrete(s1,s2)) //si l'arrete n'a pas été trouvé donc pas de supp
        retourEnArriere(); //on supprime le graphe créé
}


/// Ajoute un graphe par lecture de fichier ///
void Interface::ajouterGraphe(std::string nomFichier)
{
    m_graphes.push_back(new Graphe {nomFichier});//création d'un graphe par initialisation de fichier
    m_indice +=1;
}

/// Affichage par svg ///
void Interface::affichageSvg ()const
{
    Svgfile::s_verbose = false;
    Svgfile svgout;
    svgout.addGrid(); //ajout du repère

    if (!m_graphes.empty())//si m_graphe n'est pas vide
    {
        if (!m_comparaisonSVG) //affichage graphe actuel
            m_graphes[m_indice]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,m_comparaisonSVG);
        else if (m_comparaisonSVG) //affichage graphes de la comparaison
        {
            m_graphes[m_indice_comparantSVG]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,1);
            m_graphes[m_indice]->affichageSvg(svgout,m_selecSVG,m_normaliseSVG,2);
        }
    }
}

/// Remplis le poids pour le graphe actuel ///
void Interface::remplirPoids(std::string nomFichier)
{
    if (!m_graphes.empty())
        m_graphes[m_indice]->remplirPoids(nomFichier);
}

/// Afficher sur la console le graphe actuel en mode fichier ///
void Interface::afficherConsole()const
{
    m_graphes[m_indice]->afficherConsole();
    std::cout<<std::endl;
}

/// Afficher sur la console la liste d'adjacence du graphe actuel ///
void Interface::afficherListeAdjacence()const
{
    m_graphes[m_indice]->afficherListeAdjacence();
    std::cout<<std::endl;
}

/// Ajout d'une arrete ///
void Interface::ajouterArrete(std::string& s1,std::string& s2)//En paramètre les noms des sommets selectionnées
{
    m_graphes[m_indice]->ajoutArrete(s1, s2);
}

/// Affiche en console les centralite normalise ///
void Interface::afficherCentralite_Normalise(int selec)//En paramètre un int pour connaître ce qu'on affiche
{
    m_graphes[m_indice]->afficherCentralite_Normalise(selec);
}

/// Affiche en console les centralite ///
void Interface::afficherCentralite_NON_Normalise(int selec)//En paramètre un int pour connaître ce qu'on affiche
{
    m_graphes[m_indice]->afficherCentralite_NON_Normalise(selec);
}

/// Calcul de toutes les centralite pour le graphe actuel ///
void Interface::calculCentralite()
{
    m_graphes[m_indice]->calculCentralite();
}

/// Sauvegarde dans un fichier de toutes les centralite pour le graphe actuel ///
void Interface::sauvegarderCentralite(std::string nomFichier)//En paramètre le nom du fichier de sauvegarde
{
    m_graphes[m_indice]->sauvegardeCentralite(nomFichier);
}

/// Retourne à l'étape precedente ///
void Interface::retourEnArriere()
{
    int selec = (int) m_graphes.size() - 1; //indice de la suppression
    if (selec > 0) //verifie que c'est possible
    {
        delete m_graphes[selec];
        m_graphes.erase(m_graphes.begin()+selec);
        m_indice = selec -1;
    }
    else
        std::cout<<std::endl<<"Retour en arriere impossible";

}

/// test la connexite du graphe actuel ///
void Interface::connexite()
{
    if(m_graphes[m_indice]->connexite())
        std::cout<<"Le graphe selectionne est un graphe connexe"<<std::endl;
    else
        std::cout<<"Le graphe selectionne n'est pas un graphe connexe"<<std::endl;
}

/// test la k-connexite du graphe actuel ///
void Interface::k_connexite()
{
    m_graphes[m_indice]->k_connexite();
}

/// Programme de comparaison ///
//appel les differentes comparaisons selon la selection de l'utilisateur
void Interface::comparaison(int indice_compare, int selec)
{
    if (indice_compare==-1) //etape precedente
        indice_compare=m_indice-1;

    int id_dernier=(int) m_graphes.size(); //conversion du size_t en int

    if (indice_compare >= 0 && indice_compare < id_dernier)//verifie numéro positif et inferieur à size
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

        if(selec == 1 || selec == 4)
            comparaisonCvp(actuel,comparant);

        if(selec == 2 || selec == 4)
            comparaisonCp(actuel,comparant);

        if(selec == 0 || selec == 4)
            comparaisonCd(actuel,comparant);

        if(selec == 3 || selec == 4)
            comparaisonCiSommet(actuel,comparant);

        if (selec == 5 || selec == 4)
        {
            std::vector<Arrete*> actuel_a = m_graphes[m_indice]->getArretes();
            std::vector<Arrete*> comparant_a = m_graphes[indice_compare]->getArretes();
            comparaisonCiArrete(actuel_a,comparant_a);
        }

        // modifie les option d'affichage
        setSelecSVG(selec);
        setNormaliseSVG(true);



    }
    else
        std::cout<<"Numero d'etape invalide";

}

void Interface::comparaisonCvp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de vecteur"<<std::endl<<" propre des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cvp(true)-comparant[i]->get_Cvp(true))/comparant[i]->get_Cvp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCd(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de degre"<<std::endl<<" des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cd(true)-comparant[i]->get_Cd(true))/comparant[i]->get_Cd(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCp(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee de"<<std::endl<<" proximite des sommets :";
    for (size_t i=0; i<actuel.size(); ++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                 <<((actuel[i]->get_Cp(true)-comparant[i]->get_Cp(true))/comparant[i]->get_Cp(true))*100
                 <<"%";
    }
}

void Interface::comparaisonCiSommet(std::vector<Sommet*>& actuel,std::vector<Sommet*>& comparant) //valeur normalisé
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee"<<std::endl<<" d'intermediarite des sommets :";
    for (size_t i=0;i<actuel.size();++i)
    {
        std::cout<<std::endl<<actuel[i]->getNom()<<" : "
                           <<((actuel[i]->get_Ci(true)-comparant[i]->get_Ci(true))/comparant[i]->get_Ci(true))*100
                           <<"%";
    }
}

void Interface::comparaisonCiArrete(std::vector <Arrete*>& actuel,std::vector<Arrete*>& comparant)
{
    std::cout<<std::endl<<"Affichage de la centralite normalisee"<<std::endl<<" d'intermediarite des arretes :";
    for (size_t i=0;i<actuel.size();++i)
    {
        std::vector<Sommet*> temp=actuel[i]->getExtremite();
        std::cout<<std::endl<<temp[0]->getNom()<<"-"<<temp[1]->getNom()<<" : "
                           <<((actuel[i]->get_Ci(true)-comparant[i]->get_Ci(true))/comparant[i]->get_Ci(true))*100
                           <<"%";
    }
}

/// Ensemble des set ///
void Interface::set_indice_comparantSVG(int indice)
{
    m_indice_comparantSVG=indice;
}

void Interface::setComparaisonSVG(bool comparaison)
{
  m_comparaisonSVG=comparaison;
}

void Interface::setNormaliseSVG(bool normalise)
{
    m_normaliseSVG=normalise;
}

void Interface::setSelecSVG(int selec)
{
    m_selecSVG = selec;
}

void Interface::setIndice(int indice)
{
    if (indice>0 && indice < (int)m_graphes.size())
        m_indice=indice;
    else
        std::cout<<std::endl<<"Indice invalide";
}

/// Ensemble des get ///
int Interface::getComparaisonSVG()const
{
    return m_comparaisonSVG;
}

bool Interface::get_indice_comparantSVG()const
{
    return m_indice_comparantSVG;
}

int Interface::getIndice()const
{
    return m_indice;
}
