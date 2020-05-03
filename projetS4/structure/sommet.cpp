//
//  sommet.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "sommet.h"

Sommet::Sommet(int indice, std::string nom, Coord mesCoord)//Constructeur
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

int Sommet::getMarque()const//retourne la valeur du paramètre
{
    return m_marque;
}

void Sommet::set_poids(Sommet* extremite, double poids)//permet de donner une valeur au parametre poids de la pair m_adjacent
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

std::vector< std::pair<Sommet*, double >> Sommet::getAdjacent()//retourne le parametre
{
    return m_adjacent;
}

void Sommet::set_adjacent(Sommet* nouveau)//ajoute un sommet à m_adjacent avec un poids null
{
    m_adjacent.push_back(std::pair<Sommet*, double> (nouveau, 0));
}

Coord Sommet::getCoords()const//retourne le parametre : les coordonnées
{
    return m_coord;
}

int Sommet::getId()const//retourne le parametre : l'indice
{
    return m_indice;
}

std::string Sommet::getNom()const//retourne le parametre : le nom
{
    return m_nom;
}

void Sommet::affichageSVG (Svgfile& svgout,int& indice, Coord& milieu, double max,double min, int selec, bool normalise,int comparaison)const
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

    int milieu_ecran_x;
    int milieu_ecran_y=400;
    if (comparaison==0) //un seul grahe au centre
        milieu_ecran_x=500;

    if (comparaison==1) //graphe centre gauche = graphe lors d'une comparaison
        milieu_ecran_x=250;

    if (comparaison==2) //graphe centre droite = grpahe apres lors d'une comparaison
        milieu_ecran_x=750;


    if (m_coord.getX()==milieu.getX() && m_coord.getY()==milieu.getY() )
    {
        svgout.addDisk(milieu_ecran_x,milieu_ecran_y,5,svgout.makeRGB(r, g, b));
        svgout.addText(milieu_ecran_x-5,milieu_ecran_y-10,m_nom,"black");
        if (temp!=0) // afficher indice
            svgout.addText(milieu_ecran_x,milieu_ecran_y+22,indice_affiche,svgout.makeRGB(r, g, b));
    }
    else
    {
        int ecart_x=(milieu.getX()-m_coord.getX())*indice;
        int ecart_y=(milieu.getY()-m_coord.getY())*indice;
        svgout.addDisk(milieu_ecran_x-ecart_x,milieu_ecran_y-ecart_y,5,svgout.makeRGB(r, g, b));
        svgout.addText(milieu_ecran_x-ecart_x-5,milieu_ecran_y-ecart_y-10,m_nom,"balck");
        if (temp!=0) // afficher indice
            svgout.addText(milieu_ecran_x-ecart_x,milieu_ecran_y-ecart_y+22,indice_affiche,svgout.makeRGB(r, g, b));
    }
}

void Sommet::suppAdjacent(Sommet* supprimer)//supprime un adjacent selon le sommet en parametre
{
    int compt = 0;
    for(size_t i=0; i<m_adjacent.size(); ++i)
    {
        if(m_adjacent[i].first == supprimer)
            m_adjacent.erase(m_adjacent.begin() + compt);

        compt +=1;
    }
}

void Sommet::calculCd(int degre)//calcul de l'indice centralité de degré
{
    m_N_Cd = m_adjacent.size();
    m_Cd = m_N_Cd / (degre-1);
}

void Sommet::set_Cvp(double cvpN, double lambda)//modifie la valeur de Cvp
{
    m_Cvp = cvpN/lambda;
    m_N_Cvp = cvpN;
}

double Sommet::get_Cvp(bool selec)//retourne la valeur de Cvp si vrai
{
    if(selec)
        return m_Cvp;
    else
        return m_N_Cvp;
}

double Sommet::get_SommeIndice()//retourne la sommme des valeurs de Cvp des adjacent au sommet
{
    double somme = 0;

    for(auto it : m_adjacent)
        somme+= it.first->get_Cvp(true);

    return somme;
}

void Sommet::set_Cp(double cp, int degre)//modifie la valeur de Cp
{
    m_Cp = cp * (degre-1);
    m_N_Cp = cp;
}

void Sommet::caculCi(double nbre, int degre)//modifie la valeur de Ci
{
    m_N_Ci = nbre;
    m_Ci = (2*m_N_Ci)/(degre*degre - 3*degre +2);
}


double Sommet::get_Cp(bool selec)//retourne la valeur de Cp si vrai
{
    if(selec)
        return m_Cp;
    else
        return m_N_Cp;
}

double Sommet::get_Cd(bool selec)//retourne la valeur de Cd si vrai
{
    if(selec)
        return m_Cd;
    else
        return m_N_Cd;
}

double Sommet::get_Ci(bool selec)//retourne la valeur de Ci si vrai
{
    if(selec)
        return m_Ci;
    else
        return m_N_Ci;
}

void Sommet::afficherConsole()const//permet l'affichage du sommet dans la console
{
    std::cout<<std::endl
             <<m_indice<<" "<<m_nom<<" ";
    m_coord.afficherConsole();

}

void Sommet::afficherListeAdjacence()const//affiche les sommets adjacents dans la console
{
    std::cout<<std::endl
             <<m_nom<<" : ";
    for (auto it : m_adjacent)
        std::cout<<it.first->getNom()<<"-("<<it.second<<")  ";
}
