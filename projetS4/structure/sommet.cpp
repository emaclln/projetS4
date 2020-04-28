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

void Sommet::set_arrete(Arrete* nouvelle_adjacente)
{
    m_Arrete.push_back( nouvelle_adjacente);
}

void Sommet::setMarque(int selec)//donne une valeur au paramètre
{
    m_marque = selec;
}

int Sommet::getMarque()
{
    return m_marque;
}

std::vector<Arrete*> Sommet::getArrete()
{
    return m_Arrete;
}

std::vector<Sommet*> Sommet::getAdjacent()
{
    return m_adjacent;
}

void Sommet::set_adjacent(Sommet* nouveau)
{
    m_adjacent.push_back( nouveau);
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

void Sommet::suppAdjacent(Arrete* supprimer)
{
    int compt = 0;
    for(auto it : m_Arrete)
    {
        if(it == supprimer)
            m_Arrete.erase(m_Arrete.begin() + compt);
            
        compt +=1;
    }
}

void Sommet::calculCd(int degre)
{
    m_Cd = m_Arrete.size() / (degre-1);
    m_N_Cd = m_Arrete.size();
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
        somme+= it->get_Cvp();
        
    return somme;
}

void Sommet::set_Cp(double cp, int degre)
{
    m_Cp = cp * (degre-1);
    m_N_Cp = cp;
    
    std::cout<< cp <<std::endl;
}

void Sommet::caculCi()
{
    
}
