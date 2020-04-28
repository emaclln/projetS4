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
    m_ponderation=false;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );
}

void Arrete::affichageSVG(Svgfile& svgout, int& indice, Coord& milieu,bool orientation)const
{
    if (m_extremite[0]->getCoords().getX()==milieu.getX() && m_extremite[0]->getCoords().getY()==milieu.getY())
    {
        int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
        int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;
        svgout.addLine(500,400,500-ecart_x1,400-ecart_y1,"black");

        if (orientation) //s'il est orienté
        {
            //extremité 0 vers 1
            
        }

        if (m_ponderation)//affichage poids
        {
            int milieu_arrete_x,milieu_arrete_y;
            milieu_arrete_x=ecart_x1/2;
            milieu_arrete_y=ecart_y1/2;

            svgout.addText(500-milieu_arrete_x,400-milieu_arrete_y+5,m_poids,"blue");
        }
    }
    else
    {
        if (m_extremite[1]->getCoords().getX()==milieu.getX() && m_extremite[1]->getCoords().getY()==milieu.getY() )
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            svgout.addLine(500,400,500-ecart_x0,400-ecart_y0,"black");

            if (orientation) //s'il est orienté
            {
                //extremité 0 vers 1

            }

            if (m_ponderation)//affichage poids
            {
                int milieu_arrete_x=ecart_x0/2;
                int milieu_arrete_y=ecart_y0/2;
                svgout.addText(500-milieu_arrete_x,400-milieu_arrete_y+5,m_poids,"blue");
            }
        }
        else
        {
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
            int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;

            svgout.addLine(500-ecart_x0,400-ecart_y0,500-ecart_x1,400-ecart_y1,"black");

            if (m_ponderation)//affichage poids
            {
                int milieu_arrete_x, milieu_arrete_y;
                milieu_arrete_y=(400-ecart_y0+400-ecart_y1)/2;
                if (500-ecart_x0>=500-ecart_x1)
                    milieu_arrete_x=((500-ecart_x0-500+ecart_x1)/2)+500-ecart_x1;
                else
                    milieu_arrete_x=((500-ecart_x1-500+ecart_x0)/2)+500-ecart_x0;

                if (400-ecart_y0>=400-ecart_y1)
                    milieu_arrete_y=((400-ecart_y0-400+ecart_y1)/2)+400-ecart_y1;
                else
                    milieu_arrete_y=((400-ecart_y1-400+ecart_y0)/2)+400-ecart_y0;


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
    m_ponderation=true;
    m_extremite[0]->set_poids(m_extremite[1], poids);
    m_extremite[1]->set_poids(m_extremite[0], poids);
}

int Arrete::getPoids()
{
        return m_poids;
}

int Arrete::getIndice()
{
    return m_indice;
}

void Arrete::suppAdjacent()
{
    m_extremite[0]->suppAdjacent(m_extremite[1]);
    m_extremite[1]->suppAdjacent(m_extremite[0]);
}
