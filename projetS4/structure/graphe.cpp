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

void Graphe::remplirPoids(std::string nomFichier)
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
        for (int i=0; i<taille;++i)
        {
            ifs>>indice>>poids;
            m_arretes[indice]->remplirPoids(poids);
        }
    }



}

void Graphe::suppArrete(int indice_Arrete)
{
    for(auto it : m_arretes)
    {
        if(it->getIndice() == indice_Arrete)
        {
            it->suppAdjacent();
            m_arretes.erase(m_arretes.begin() + indice_Arrete);
        }
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

void Graphe::afficherCentralité()
{
    for(auto it : m_sommets)
        it->afficherCentralité();
}

void Graphe::CalculCentralité()
{
    calculCd();
    calculCvp();
    calculCp();
}
