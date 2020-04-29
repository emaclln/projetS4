//
//  graphe.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "graphe.h"

Graphe::Graphe(std::string nomFichier )
{

    std::ifstream ifs{nomFichier};//lecture du fichier
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    ifs >> m_orientation;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture orientation du graphe");

    ifs >> m_ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    for (int i=0; i<m_ordre; ++i)
    {
        int indice;
        std::string nom;
        Coord mesCoord;
        int x;
        int y;

        ifs >> indice >> nom >> x >> y;

        mesCoord.set_coord(x,y);

        m_sommets.push_back( new Sommet(indice, nom, mesCoord) );
    }

    ifs >> m_taille;

    for (int i=0; i<m_taille; ++i)
    {
        int indice;
        int num1;
        int num2;

        ifs >> indice >> num1 >> num2;

        m_arretes.push_back(new Arrete(indice, m_sommets[num1], m_sommets[num2]));
        m_sommets[num1]->set_adjacent(m_sommets[num2]);
        m_sommets[num2]->set_adjacent(m_sommets[num1]);
    }
};

Graphe::Graphe(std::vector<Sommet*> buffer_s,std::vector<Arrete*> buffer_a,int orient)
{
    m_orientation=orient;
    m_ordre=buffer_s.size();
    m_taille=buffer_a.size();
    for (size_t i=0; i<buffer_s.size(); i++)
    {
        m_sommets.push_back(new Sommet{buffer_s[i]->getId(),buffer_s[i]->getNom(),buffer_s[i]->getCoords()});
    }
    for (size_t i=0; i<buffer_a.size(); i++)
    {
        std::vector< Sommet*> buffer_e=buffer_a[i]->getExtremite();
        int id_e1, id_e2;
        for (auto it : m_sommets)
        {
            if (it->getId() == buffer_e[0]->getId())
                id_e1=it->getId();
            if (it->getId() == buffer_e[1]->getId())
                id_e2=it->getId();
        }
        m_arretes.push_back(new Arrete{buffer_a[i]->getIndice(),m_sommets[id_e1],m_sommets[id_e2],
                                       buffer_a[i]->getPonde(),buffer_a[i]->getPoids()});
    }


    //remplir les adjacents de m_sommets
//    for (size_t i=0; i<buffer_s.size(); i++)
//    {
//        for (size_t j=0; j<m_arretes.size(); j++)
//        {
//            std::vector< Sommet*> buffer_e=m_arretes[j]->getExtremite();
//            if (buffer_e[0]->getId()==buffer_s[i]->getId())
//                buffer_s[i]->set_poids(m_sommets[buffer_e[1]->getId()],m_arretes[j]->getPoids());
//            if (!m_orientation)
//            {
//                if (buffer_e[1]->getId()==buffer_s[i]->getId())
//                    buffer_s[i]->set_poids(m_sommets[buffer_e[0]->getId()],m_arretes[j]->getPoids());
//            }
//        }
//
//    }

}



bool Graphe::getOrientation()const
{
    return m_orientation;
}

int Graphe::getOrdre()const
{
    return m_ordre;
}

int Graphe::getTaille()const
{
    return m_taille;
}

void Graphe::remplirPoids(std::string& nomFichier)
{
    std::ifstream ifs{nomFichier};//lecture du fichier
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichier );

    int taille;
    ifs>>taille;
    if (ifs.fail())
        throw std::runtime_error("Probleme lecture taille du graphe");

    if (taille!=m_taille)
        throw std::runtime_error("Probleme taille du graphe incompatible");
    else
    {
        int indice,poids;
        for (int i=0; i<taille; ++i)
        {
            ifs>>indice>>poids;
            m_arretes[indice]->remplirPoids(poids);
        }
    }



}

void Graphe::suppArrete(std::string& s1, std::string& s2)
{
    int indice_arrete;
    bool trouvee=false;
    for(size_t i=0; i<m_arretes.size(); ++i)
    {
        if(m_arretes[i]->trouveeArrete(s1,s2))
        {
            indice_arrete=m_arretes[i]->getIndice();
            m_arretes[i]->suppAdjacent();
            //delete m_arretes[i];
            m_arretes.erase(m_arretes.begin() + indice_arrete);
            trouvee=true;
        }
    }
    if (!trouvee)
    {
        std::cout<<std::endl<<"Arrete introuvable";
    }
}


void Graphe::ajoutArrete(int indice, int  extremite_un, int extremite_deux)
{
    m_arretes.push_back(new Arrete(indice, m_sommets[extremite_un], m_sommets[extremite_deux]));
    m_sommets[extremite_un]->set_adjacent(m_sommets[extremite_deux]);
    m_sommets[extremite_deux]->set_adjacent(m_sommets[extremite_un]);
}


void Graphe::affichageSvg () const
{
    Svgfile svgout;
    svgout.addGrid();
    ///cherhons l'indice pour adapté le graphe à la taille de l'écran 1000*800
    int indice=100; // par défaut on le met à 100
    bool stop;
    //on verifie qu'avec cette indice on peut construire tout le grpahe sinon on le réduit
    int max_x=0,temp_x,max_y=0,temp_y;
    int min_x=0,min_y=0; //pour trouver le sommet centre par la suite
    //recherche des points extreme du graphe
    do
    {
        stop=true;
        for (auto it : m_sommets)
        {
            temp_x=it->getCoords().getX();
            if (temp_x>max_x)
                max_x=temp_x;
            else if (temp_x<min_x)
                min_x=temp_x;

            temp_y=it->getCoords().getY();
            if (temp_y>max_y)
                max_y=temp_y;
            else if (temp_x<min_x)
                min_x=temp_x;
        }
        if (max_x*indice>1000 || max_y*indice>800) //depace
        {
            indice=indice/2;
            stop=false; //on revérifie qu'avec cet nouvel indice ce soit bon
        }

    }
    while (!stop);//tant que le grpahe rentre enier

    ///centrage

    //trouver le sommet centre
    temp_x=max_x-min_x;
    if (temp_x%2==0)//si la ifférence est pair
        temp_x=temp_x/2;
    else
        temp_x=(temp_x+1)/2; //milieu

    temp_y=max_y-min_y;
    if (temp_y%2==0)//si la ifférence est pair
        temp_y=temp_y/2;
    else
        temp_y=(temp_y+1)/2; //milieu

    Coord milieu;
    milieu.set_coord(temp_x,temp_y);

    ///dessin
    for (auto it : m_arretes)
    {
        it->affichageSVG(svgout,indice,milieu,m_orientation);
    }

    for (auto it : m_sommets)
    {
        it->affichageSVG(svgout,indice,milieu);
    }

}

void Graphe::calculCd()
{
    for(auto it : m_sommets)
        it->calculCd(m_ordre);
}

void Graphe::calculCvp()
{
    for(auto it : m_sommets)
        it->set_Cvp(1);

    double ancien_lambda;
    double lambda = 0;

    do
    {
        double Sindice, SsIndice = 0;

        ancien_lambda = lambda;

        for(auto it : m_sommets)
        {
            Sindice = it->get_SommeIndice();
            SsIndice += Sindice*Sindice;
        }
        lambda = sqrt(SsIndice);

        for(auto it : m_sommets)
            it->set_Cvp(it->get_SommeIndice() / lambda);
    }
    while(lambda - ancien_lambda > 1);
}

void Graphe::calculCp()
{
    for(auto it : m_sommets)
    {
        double Slongueur = 0;

        for(auto s : m_sommets)
        {
            std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total = disjtra(it->getId(), s->getId());
            Slongueur += pred_I_total[m_sommets[s->getId()]].second;
        }

        it->set_Cp(1/Slongueur, m_ordre);
    }
}
void Graphe::caculCi()
{

}

std::map<Sommet*, std::pair<Sommet*, int>> Graphe::disjtra (int premier, int dernier)//parcours disjtra
{
    std::priority_queue< std::pair<Sommet*, int>, std::vector<std::pair<Sommet*,int> >,CompareSommet > maFile;
    std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total;

    for(auto s : m_sommets)//initialisation des marques des sommets à 0 et création de predI
        s->setMarque(0);

    maFile.push(std::make_pair(m_sommets[premier], 0) );
    m_sommets[premier]->setMarque(1);

    while(!maFile.empty())
    {
        int compt = 0;
        std::pair<Sommet*,int> buffer;

        buffer = maFile.top();
        maFile.pop();

        for(auto s : buffer.first->getAdjacent())
        {
            int total = buffer.second + s.second;

            if (s.first->getMarque() == 0 || pred_I_total[s.first].second > total)
            {
                s.first->setMarque(1);
                maFile.push(std::make_pair(s.first, total));
                pred_I_total[s.first] = std::make_pair(buffer.first, total);
            }

            ++compt;
        }
    }

    return pred_I_total;
}

void Graphe::afficherCentralite()
{
    for(auto it : m_sommets)
        it->afficherCentralite();
}

void Graphe::CalculCentralite()
{
    calculCd();
    calculCvp();
    calculCp();
}

void Graphe::afficherListeAdjacence()const
{
    std::cout<<std::endl
             <<"Liste d'adjacence :";
    for (auto it : m_sommets)
        it->afficherListeAdjacence();
}
void Graphe::afficherConsole()const
{
    std::cout<<std::endl
             <<"Graphe (format fichier):"
             <<std::endl<<m_orientation
             <<std::endl<<m_ordre;
    for (auto it : m_sommets)
        it->afficherConsole();
    std::cout<<std::endl<<m_taille;
    for (auto it : m_arretes)
        it->afficherConsole();



}

Graphe::~Graphe()
{
    for (auto it : m_sommets)
        delete it;
    for (auto it : m_arretes)
        delete it;
}


std::vector<Sommet*> Graphe::getSommets()const
{
    return m_sommets;
}

std::vector <Arrete*> Graphe::getArretes () const
{
    return m_arretes;
}


