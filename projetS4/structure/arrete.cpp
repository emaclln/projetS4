//
//  arrete.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "arrete.h"

Arrete::Arrete(int indice, Sommet* un, Sommet* deux)//constructeur Un
{
    m_indice = indice;
    m_poids = 0;
    m_extremite.push_back( un );
    m_extremite.push_back( deux );
}

Arrete::Arrete(int indice, Sommet* un, Sommet* deux, int poids)//Constructeur Deux
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

void Arrete::affichageSVG(Svgfile& svgout, int& indice, Coord& milieu,bool orientation, bool ponderation, int comparaison, bool normalise,int selec)const
{
    double Ci=0;
    int temp;
    if (normalise)
    {
        //j'arondi au milième
        temp=m_Ci*1000;
        Ci=(double)temp/1000;
    }
    else
    {
        //j'arondis au centième
        temp=m_N_Ci*100;
        Ci=(double)temp/100;
    }

    //je determine le centre du graphe selon si on aficche 1 ou 2 graphes
    int milieu_ecran_x;
    int milieu_ecran_y=400;

    if (comparaison==0) //un seul grahe au centre
        milieu_ecran_x=500;

    if (comparaison==1) //graphe centre gauche = graphe lors d'une comparaison
        milieu_ecran_x=250;

    if (comparaison==2) //graphe centre droite = grpahe apres lors d'une comparaison
        milieu_ecran_x=750;

    //si l'extremite 0 est le milieu du graphe
    if (m_extremite[0]->getCoords().getX()==milieu.getX() && m_extremite[0]->getCoords().getY()==milieu.getY())
    {
        //calcul de coordonnées de la 2e extremite
        int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
        int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;

        svgout.addLine(milieu_ecran_x,milieu_ecran_y,milieu_ecran_x-ecart_x1,milieu_ecran_y-ecart_y1,"black");

        if (orientation) //s'il est orienté
        {
            //extremité 0 vers 1

        }

        if (ponderation || selec==5)//affichage soit indice Ci arrete soit poids
        {
            int milieu_arrete_x,milieu_arrete_y;
            milieu_arrete_x=ecart_x1/2;
            milieu_arrete_y=ecart_y1/2;

            if (selec == 5) // si Ci
                svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,Ci,"red");

            else
                svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,m_poids,"blue");
        }
    }
    else
    {
        //si l'extremite 1 est le milieu du graphe
        if (m_extremite[1]->getCoords().getX()==milieu.getX() && m_extremite[1]->getCoords().getY()==milieu.getY() )
        {
            //calcul de coordonnées de la 2e extremite
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;

            svgout.addLine(milieu_ecran_x,milieu_ecran_y,milieu_ecran_x-ecart_x0,milieu_ecran_y-ecart_y0,"black");

            if (orientation) //s'il est orienté
            {
                //extremité 0 vers 1

            }

            if (ponderation || selec == 5)//affichage poids ou indice Ci
            {
                int milieu_arrete_x,milieu_arrete_y;
                milieu_arrete_x=ecart_x0/2;
                milieu_arrete_y=ecart_y0/2;

                if (selec == 5) //si Ci
                    svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,Ci,"red");

                else
                    svgout.addText(milieu_ecran_x-milieu_arrete_x,milieu_ecran_y-milieu_arrete_y+5,m_poids,"blue");
            }
        }
        else
        {
            //Sinon je calcule les coordonnée des extremite en fonction du milieu
            int ecart_x0=(milieu.getX()-m_extremite[0]->getCoords().getX())*indice;
            int ecart_y0=(milieu.getY()-m_extremite[0]->getCoords().getY())*indice;
            int ecart_x1=(milieu.getX()-m_extremite[1]->getCoords().getX())*indice;
            int ecart_y1=(milieu.getY()-m_extremite[1]->getCoords().getY())*indice;

            svgout.addLine(milieu_ecran_x-ecart_x0,milieu_ecran_y-ecart_y0,milieu_ecran_x-ecart_x1,
                           milieu_ecran_y-ecart_y1,"black");

            if (ponderation || selec == 5)//affichage poids ou indice
            {
                int milieu_arrete_x, milieu_arrete_y;
                milieu_arrete_y=(milieu_ecran_y-ecart_y0+milieu_ecran_y-ecart_y1)/2;

                //calcul en focntion de la position des sommets l'un à l'autre
                if (milieu_ecran_x-ecart_x0>=milieu_ecran_x-ecart_x1)
                    milieu_arrete_x=((milieu_ecran_x-ecart_x0-milieu_ecran_x+ecart_x1)/2)+milieu_ecran_x-ecart_x1;
                else
                    milieu_arrete_x=((milieu_ecran_x-ecart_x1-milieu_ecran_x+ecart_x0)/2)+milieu_ecran_x-ecart_x0;

                if (milieu_ecran_y-ecart_y0>=milieu_ecran_y-ecart_y1)
                    milieu_arrete_y=((milieu_ecran_y-ecart_y0-milieu_ecran_y+ecart_y1)/2)+milieu_ecran_y-ecart_y1;
                else
                    milieu_arrete_y=((milieu_ecran_y-ecart_y1-milieu_ecran_y+ecart_y0)/2)+milieu_ecran_y-ecart_y0;

                if (selec == 5) // si Ci
                    svgout.addText(milieu_arrete_x,milieu_arrete_y+5,Ci,"red");

                else
                    svgout.addText(milieu_arrete_x,milieu_arrete_y+5,m_poids,"blue");
            }

            if (orientation) //s'il est orienté
            {
                //extremité 0 vers 1


            }
        }

    }
}

void Arrete::remplirPoids(int& poids)//remplissage du paramètre poids
{
    m_poids=poids;
    m_extremite[0]->set_poids(m_extremite[1], poids);
    m_extremite[1]->set_poids(m_extremite[0], poids);
}

int Arrete::getPoids()const//retourne la valeur du paramètre
{
    return m_poids;
}

int Arrete::getIndice()const//retourne la valeur du paramètre
{
    return m_indice;
}

void Arrete::suppAdjacent()//permet de supprimer l'arrête au niveau des sommets
{
    m_extremite[0]->suppAdjacent(m_extremite[1]);
    m_extremite[1]->suppAdjacent(m_extremite[0]);
}

std::vector<Sommet*> Arrete::getExtremite()const//retourne la valeur du paramètre
{
    return m_extremite;
}

bool Arrete::trouverArrete(std::string& s1, std::string& s2)//si les noms recu en paramètre correspond aux noms des sommets de l'arrête alors retourne vrai sinon faux
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

void Arrete::afficherConsole()const//affichage en console
{
    std::cout<<std::endl
             <<m_indice<<" ";
    for (auto it : m_extremite)
        std::cout<<it->getId()<<" ";
}

void Arrete::caculCi(double nbre, int degre)//calcul de l'indice Ci
{
    m_N_Ci = nbre;
    m_Ci = m_N_Ci/((degre-1)*degre);
}

double Arrete::get_Ci(bool selec)//retourne la valeur du paramètre
{
    if(selec)
        return m_Ci;
    else
        return m_N_Ci;
}
