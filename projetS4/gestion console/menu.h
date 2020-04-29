#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <sstream>

//#include <windows.h>
#include "../Interface.h"

int gererCommande(std::string& commande,Interface& monInterface);
int gererDeffilement(bool autoCin);

void changerCouleurConsole (int couleur);
void affichageCommande();
void gotoligcol(int A, int B);


#endif // MENU_H_INCLUDED
