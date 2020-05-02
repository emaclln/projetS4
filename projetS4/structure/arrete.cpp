//
//  arrete.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "arrete.h"

Arrete::Arrete(int indice, Sommet* un, Sommet* deux)
{
    m_indice = indice;
    m_poids = 0;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );
}

Arrete::Arrete(int indice, Sommet* un, Sommet* deux, int poids)
{
    m_indice = indice;
    m_poids=poids;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );

    m_extremite[0]->set_adjacent(m_extremite[1]);
    m_extremite[1]->set_adjacent(m_extremite[0]);
    m_extremite[0]->set_poids(m_extremite[1],m_poids);
    m_extremite[1]->set_poids(m_extremite[0],m_poids);
}

void Arrete::affichageSVG(Svgfile& svgout, int& indice, Coord& milieu,bool orientation, bool ponderation, int comparaison)const
{
    int milieu_ecran_x;
    int milieu_ecran_y=400;
    if (comparaison==0) //un seul grahe au centre
        milieu_ecran_x=500;

    if (comparaison==1) //graphe centre gauche = graphe lors d'une comparaison
        milieu_ecran_x=250;

    if (comparaison==2) //graphe centre droite = grpahe apres lors d'une comparaison
        milieu_ecran_x=750;

    if (m_extremite[0]->getCoords().getX()==milieu.getX() && m_extremite[0]->getCoords().getY()==milieu.getY())
    {
        int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
        int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;
        svgout.addLine(milieu_ecran_x,milieu_ecran_y,milieu_ecran_x-ecart_x1,milieu_ecran_y-ecart_y1,"black");

        if (orientation) //s'il est orienté
        {
            //extremité 0 vers 1

        }

        if (ponderation)//affichage poids
        {
            int milieu_arrete_x,milieu_arrete_y;
            milieu_arrete_x=ecart_x1/2;
            milieu_arrete_y=ecart_y1/2;

            svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,m_poids,"blue");
        }
    }
    else
    {
        if (m_extremite[1]->getCoords().getX()==milieu.getX() && m_extremite[1]->getCoords().getY()==milieu.getY() )
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            svgout.addLine(milieu_ecran_x,milieu_ecran_y,milieu_ecran_x-ecart_x0,milieu_ecran_y-ecart_y0,"black");

            if (orientation) //s'il est orienté
            {
                //extremité 0 vers 1

            }

            if (ponderation)//affichage poids
            {
                int milieu_arrete_x=ecart_x0/2;
                int milieu_arrete_y=ecart_y0/2;
                svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,m_poids,"blue");
            }
        }
        else
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
            int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;

            svgout.addLine(milieu_ecran_x-ecart_x0,milieu_ecran_y-ecart_y0,milieu_ecran_x-ecart_x1,
                           milieu_ecran_y-ecart_y1,"black");

            if (ponderation)//affichage poids
            {
                int milieu_arrete_x, milieu_arrete_y;
                milieu_arrete_y=(milieu_ecran_y-ecart_y0+milieu_ecran_y-ecart_y1)/2;
                if (milieu_ecran_x-ecart_x0>=milieu_ecran_x-ecart_x1)
                    milieu_arrete_x=((milieu_ecran_x-ecart_x0-milieu_ecran_x+ecart_x1)/2)+milieu_ecran_x-ecart_x1;
                else
                    milieu_arrete_x=((milieu_ecran_x-ecart_x1-milieu_ecran_x+ecart_x0)/2)+milieu_ecran_x-ecart_x0;

                if (milieu_ecran_y-ecart_y0>=milieu_ecran_y-ecart_y1)
                    milieu_arrete_y=((milieu_ecran_y-ecart_y0-milieu_ecran_y+ecart_y1)/2)+milieu_ecran_y-ecart_y1;
                else
                    milieu_arrete_y=((milieu_ecran_y-ecart_y1-milieu_ecran_y+ecart_y0)/2)+milieu_ecran_y-ecart_y0;


                svgout.addText(milieu_arrete_x,milieu_arrete_y,m_poids,"blue");
            }

            if (orientation) //s'il est orienté
            {
                //extremité 0 vers 1


            }
        }

    }
}

void Arrete::remplirPoids(int& poids)
{
    m_poids=poids;
    m_extremite[0]->set_poids(m_extremite[1], poids);
    m_extremite[1]->set_poids(m_extremite[0], poids);
}

int Arrete::getPoids()const
{
    return m_poids;
}

int Arrete::getIndice()const
{
    return m_indice;
}

void Arrete::suppAdjacent()
{
    m_extremite[0]->suppAdjacent(m_extremite[1]);
    m_extremite[1]->suppAdjacent(m_extremite[0]);
}

std::vector<Sommet*> Arrete::getExtremite()const
{
    return m_extremite;
}

bool Arrete::trouverArrete(std::string& s1, std::string& s2)
{
    int compteur=0;
    for (auto it : m_extremite)
        if(it->getNom()==s1 || it->getNom()==s2)
            compteur+=1;

    if (compteur==2) //si le nom des 2 sommets correspondent aux extremitées de l'arrete
        return true;
    else
        return false;
}

void Arrete::afficherConsole()const
{
    std::cout<<std::endl
             <<m_indice<<" ";
    for (auto it : m_extremite)
        std::cout<<it->getId()<<" ";
}
