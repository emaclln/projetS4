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

int Sommet::getMarque()const
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

void Sommet::affichageSVG (Svgfile& svgout,int& indice, Coord& milieu, double max,double min, int selec, bool normalise)const
{
    int r,g,b;
    double coeff;
    double indice_affiche;
    int temp=0;

    if(selec == 0)
    {
        if (!normalise)
        {
            coeff = m_N_Cd-min;
            //je recupere la valeur au centième près
            temp=m_N_Cd*100;
            indice_affiche=(double)temp/100;
        }
        else
        {
            coeff = m_Cd-min;
            //je recupere la valeur au centième près
            temp=m_Cd*100;
            indice_affiche=(double)temp/100;
        }

    }
    else if(selec == 1)
    {
        if (!normalise)
        {
            coeff = m_N_Cvp-min;
            temp=m_N_Cvp*100;
            indice_affiche=(double)temp/100;
        }
        else
        {
            coeff = m_Cvp-min;
            temp=m_Cvp*100;
            indice_affiche=(double)temp/100;

        }

    }

    else if(selec == 2)
    {
        if (!normalise)
        {
            coeff = m_N_Cp-min;
            temp=m_N_Cp*100;
            indice_affiche=(double)temp/100;
        }
        else
        {
            coeff = m_Cp-min;
            temp=m_Cp*1000;
            indice_affiche=(double)temp/1000;
        }
    }

    else if(selec == 3)
    {
        if (!normalise)
        {
            coeff = m_N_Ci-min;
            temp=m_N_Ci*100;
            indice_affiche=(double)temp/100;
        }
        else
        {
            coeff = m_Ci-min;
            temp=m_Ci*100;
            indice_affiche=(double)temp/100;
        }
    }
    else
    {
        coeff = 0;
        temp =0;
    }


    if(coeff < ((max-min) * 1/3) && max != 0)
    {
        r = 0;
        g = 0;
        b = (coeff / (max-min)) * 255;
    }
    else if(coeff > ((max-min) * 2/3) && max != 0)
    {
        r = 0;
        g = (coeff / (max-min)) * 255;
        b = 0;
    }
    else if( max != 0)
    {
        r = (coeff / (max-min)) * 255;
        g = 0;
        b = 0;
    }
    else
    {
        r = 170;
        g = 0;
        b = 100;
    }


    if (m_coord.getX()==milieu.getX() && m_coord.getY()==milieu.getY() )
    {
        svgout.addDisk(500,400,5,svgout.makeRGB(r, g, b));
        svgout.addText(500-5,400-10,m_nom,"black");
        if (temp!=0) // afficher indice
            svgout.addText(500,400+22,indice_affiche,svgout.makeRGB(r, g, b));
    }
    else
    {
        int ecart_x=(milieu.getX()-m_coord.getX())*indice;
        int ecart_y=(milieu.getY()-m_coord.getY())*indice;
        svgout.addDisk(500-ecart_x,400-ecart_y,5,svgout.makeRGB(r, g, b));
        svgout.addText(500-ecart_x-5,400-ecart_y-10,m_nom,"balck");
        if (temp!=0) // afficher indice
            svgout.addText(500-ecart_x,400-ecart_y+22,indice_affiche,svgout.makeRGB(r, g, b));
    }
}

void Sommet::suppAdjacent(Sommet* supprimer)
{
    int compt = 0;
    for(size_t i=0; i<m_adjacent.size(); ++i)
    {
        if(m_adjacent[i].first == supprimer)
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

void Sommet::afficherConsole()const
{
    std::cout<<std::endl
             <<m_indice<<" "<<m_nom<<" ";
    m_coord.afficherConsole();

}

void Sommet::afficherListeAdjacence()const
{
    std::cout<<std::endl
             <<m_nom<<" : ";
    for (auto it : m_adjacent)
        std::cout<<it.first->getNom()<<"-("<<it.second<<")  ";
}
