//
//  sommet.hpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include "coord.hpp"
#include "graphisme/svgfile.h"

class Arrete;

class Sommet
{
private :
    
    int m_indice;
    int m_marque;
    std::string m_nom;
    Coord m_coord;
    
    std::vector<Arrete*> m_Arrete;
    std::vector<Sommet*> m_adjacent;
    
    double m_Cvp;
    float m_Cd;
    double m_Cp;
    float m_Ci;
    float m_N_Cvp;
    float m_N_Cd;
    double m_N_Cp;
    float m_N_Ci;

public :
    Sommet(int indice, std::string nom, Coord mesCoord);
    
    void set_arrete(Arrete* nouvelle_adjacente);
    void set_adjacent(Sommet* nouveau);
    void set_Cvp(double cvp);
    void set_Cp(double cp, int degre);
    void setMarque(int selec);
    
    void affichageSVG (Svgfile& svgout,int& indice,Coord& milieu)const;
    void suppAdjacent(Arrete* supprimer);
    void calculCd(int degre);
    void caculCi();
    
    Coord getCoords()const;
    std::string getNom()const;
    std::vector<Arrete*> getArrete();
    std::vector<Sommet*> getAdjacent();
    int getMarque();
    int getId()const;
    double get_SommeIndice();
    double get_Cvp();
    
};

#endif // SOMMET_H_INCLUDED

