//
//  sommet.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "sommet.h"

Sommet::Sommet(int indice, std::string nom, Coord mesCoord)
{
    m_indice = indice;
    m_nom = nom;
    m_coord = mesCoord;
    m_marque = -1;
}

Sommet::Sommet (Sommet* mere)
{
    m_indice=mere->getId();
    m_nom=mere->getNom();
    m_coord=mere->getCoords();
    m_marque=mere->getMarque();
    std::map<std::pair<Sommet*, double >,std::pair<Sommet*, double >> transpose;
    for (size_t i= 0;i<mere->m_adjacent.size();++i)
    {
        Sommet* nv_s =new Sommet{mere->m_adjacent[i].first};
        double nv=m_adjacent[i].second;
        m_adjacent[i].first=nv_s;
        transpose[mere->m_adjacent[i]]=std::make_pair(nv_s,nv);
    }

}

void Sommet::setMarque(int selec)//donne une valeur au paramètre
{
    m_marque = selec;
}

int Sommet::getMarque()
{
    return m_marque;
}

void Sommet::set_poids(Sommet* extremite, double poids)
{
    int compt = 0;
    for(auto it : m_adjacent)
    {
        if(it.first == extremite)
            m_adjacent.erase(m_adjacent.begin() + compt);

        compt +=1;
    }

    m_adjacent.push_back(std::pair<Sommet*, double> (extremite, poids));

}

std::vector< std::pair<Sommet*, double >> Sommet::getAdjacent()
{
    return m_adjacent;
}

void Sommet::set_adjacent(Sommet* nouveau)
{
    m_adjacent.push_back(std::pair<Sommet*, double> (nouveau, 0));
}

Coord Sommet::getCoords()const
{
    return m_coord;
}

int Sommet::getId()const
{
    return m_indice;
}

std::string Sommet::getNom()const
{
    return m_nom;
}

void Sommet::affichageSVG (Svgfile& svgout,int& indice, Coord& milieu)const
{
    if (m_coord.getX()==milieu.getX() && m_coord.getY()==milieu.getY() )
    {
        svgout.addDisk(500,400,5,"red");
        svgout.addText(500-5,400-10,m_nom,"red");
    }
    else
    {
        int ecart_x=(milieu.getX()-m_coord.getX())*indice;
        int ecart_y=(milieu.getY()-m_coord.getY())*indice;
        svgout.addDisk(500-ecart_x,400-ecart_y,5,"red");
        svgout.addText(500-ecart_x-5,400-ecart_y-10,m_nom,"red");
    }
}

void Sommet::suppAdjacent(Sommet* supprimer)
{
    int compt = 0;
    for(auto it : m_adjacent)
    {
        if(it.first == supprimer)
            m_adjacent.erase(m_adjacent.begin() + compt);

        compt +=1;
    }
}

void Sommet::calculCd(int degre)
{
    m_N_Cd = m_adjacent.size();
    m_Cd = m_N_Cd / (degre-1);
}

void Sommet::set_Cvp(double cvp)
{
    m_Cvp = cvp;
}

double Sommet::get_Cvp()
{
    return m_Cvp;
}

double Sommet::get_SommeIndice()
{
    double somme = 0;

    for(auto it : m_adjacent)
        somme+= it.first->get_Cvp();

    return somme;
}

void Sommet::set_Cp(double cp, int degre)
{
    m_Cp = cp * (degre-1);
    m_N_Cp = cp;
}

void Sommet::caculCi()
{

}

void Sommet::afficherCentralite()
{
    std::cout<<m_nom<<" : "<<"Cd "<<m_Cd<<"/ Cvp "<<m_Cvp<<"/ Cp "<<m_Cp<<std::endl;
    std::cout<<m_nom<<" : "<<"CdN "<<m_N_Cd<<"/ CpN "<<m_N_Cp<<std::endl;
}
