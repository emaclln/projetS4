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

void Sommet::affichageSVG (Svgfile& svgout,int& indice, Coord& milieu, double max, int selec)const
{
    int r,g,b;
    double coeff;
    
    if(selec == 0)
        coeff = m_Cd;
    else if(selec == 1)
        coeff = m_Cvp;
    else if(selec == 2)
        coeff = m_Cp;
    else
        coeff = m_Ci;
    
    if(coeff < (max * 1/3) && max != 0)
    {
        r = 40;
        g = 250;
        b = (coeff / max) * 255 + 170;
    }
    else if(coeff > (max * 2/3) && max != 0)
    {
        r = 50;
        g = (coeff / max) * 255 + 85;
        b = 50;
    }
    else if( max != 0)
    {
        r = (coeff / max) * 255 + 100;
        g = 100;
        b = 100;
    }
    else
    {
        r = 170;
        g = 100;
        b = 100;
    }
    
    
    if (m_coord.getX()==milieu.getX() && m_coord.getY()==milieu.getY() )
    {
        svgout.addDisk(500,400,5,svgout.makeRGB(r, g, b));
        svgout.addText(500-5,400-10,m_nom,"black");
    }
    else
    {
        int ecart_x=(milieu.getX()-m_coord.getX())*indice;
        int ecart_y=(milieu.getY()-m_coord.getY())*indice;
        svgout.addDisk(500-ecart_x,400-ecart_y,5,svgout.makeRGB(r, g, b));
        svgout.addText(500-ecart_x-5,400-ecart_y-10,m_nom,"balck");
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

void Sommet::set_Cvp(double cvpN, double lambda)
{
    m_Cvp = cvpN/lambda;
    m_N_Cvp = cvpN;
}

double Sommet::get_Cvp(bool selec)
{
    if(selec)
        return m_Cvp;
    else
        return m_N_Cvp;
}

double Sommet::get_SommeIndice()
{
    double somme = 0;
    
    for(auto it : m_adjacent)
        somme+= it.first->get_Cvp(true);
        
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

double Sommet::get_Cp(bool selec)
{
    if(selec)
        return m_Cp;
    else
        return m_N_Cp;
}

double Sommet::get_Cd(bool selec)
{
    if(selec)
        return m_Cd;
    else
        return m_N_Cd;
}
