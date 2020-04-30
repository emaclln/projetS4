
///            CODE REPRIS DE NOTRE PROJET S3             ///
/// Auteur : Emma Collin, Charles Hamery et Julie Trochon ///


#include "menu.h"
#include "../Interface.h"
#include "util.h"

/// Code des fonction associés à la commande ///

int gererCommande(std::string& commande,Interface& monInterface)
{
    int stop=0;

    if (commande.empty())
        std::cout<<std::endl<<"Vous n'avez pas demander d'action."<<std::endl;
    else
    {
        if (commande.find("ponderation") != std::string::npos) //recharger le dernier fichier ouvert
        {
            if (commande.find("load")!=std::string::npos)
            {
                commande.erase(0,5); //on efface "load"
                if (commande.find(" ")!=std::string::npos)
                {
                    std::string fichier;
                    size_t debut= commande.find(" ");

                    //recupere le nom du fichier
                    for (auto i=debut; i<commande.size(); ++i)
                        fichier+=commande[i];

                    fichier.erase(0,1);
                    monInterface.remplirPoids(fichier);
                }
                else
                {
                    changerCouleurConsole(3); //rouge
                    std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier"<<std::endl<<"a ouvrir";
                    changerCouleurConsole(4); //blanc
                }
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"L'action demandee n'est pas repertoriee.";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("load")!=std::string::npos) //charger un fichier .txt en donnant son nom
        {
            if (commande.find(" ")!=std::string::npos)
            {
                std::string fichier;
                size_t debut= commande.find(" ");

                //recupere le nom du fichier
                for (auto i=debut; i<commande.size(); ++i)
                    fichier+=commande[i];

                fichier.erase(0,1);
                monInterface.initialisation();
                monInterface.remplirFichier(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier"<<std::endl<<"a ouvrir";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("calculer indice") != std::string::npos) //revenir a l'etat precedent (la derniere copie)
        {
            monInterface.calculCentralite();

            //affichage
            int selec=4;
            if (commande.find("Cvp")!=std::string::npos)
                selec=1;
            else if (commande.find("Cp")!=std::string::npos)
                selec=2;
            else if (commande.find("Cd")!=std::string::npos)
                selec=0;
            else if (commande.find("Ci")!=std::string::npos)
                selec=3;
            monInterface.setSelecSVG(selec);

            if (commande.find("non normalise")!=std::string::npos)
            {
                monInterface.afficherCentralite_NON_Normalise(selec);
                monInterface.setNormaliseSVG(false);
            }
            else if (commande.find("normalise")!=std::string::npos)
            {
                monInterface.afficherCentralite_Normalise(selec);
                monInterface.setNormaliseSVG(true);

            }
            else
            {
                monInterface.afficherCentralite_NON_Normalise(selec);
                monInterface.afficherCentralite_Normalise(selec);
                monInterface.setNormaliseSVG(false); //affichage non normalise par defaut
            }

        }
        else if (commande.find("save indice") != std::string::npos) //enregistrer dans un fichier la situation actuelle
        {
            commande.erase(0,12);
            if (commande.find(" ")!=std::string::npos)
            {
                std::string fichier;
                size_t debut = commande.find(" ");

                //recupere le nom du fichier
                for (auto i=debut; i<commande.size(); ++i)
                    fichier+=commande[i];

                monInterface.sauvegarderCentralite(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier"<<std::endl<<"de sauvegarde";
                changerCouleurConsole(4); //blanc
            }
        }

        else if (commande.find("supprimer") != std::string::npos) //cacher les noms des blocs
        {
            if (commande.find('(') != std::string::npos)
            {
                size_t debut=commande.find('(')+1;

                if (commande.find('-')!=std::string::npos)
                {
                    std::string nom_extremite1;
                    std::string nom_extremite2;

                    nom_extremite1.erase();
                    nom_extremite2.erase();

                    for (size_t i=debut; i<commande.find('-'); ++i)
                    {
                        nom_extremite1+=commande[i];
                    }
                    if (commande.find('-')!=std::string::npos)
                    {
                        debut=commande.find('-')+1;
                        for (size_t i=debut; i<commande.find(')'); ++i)
                        {
                            nom_extremite2+=commande[i];
                        }
                        ///creation par copie
                        monInterface.copieGraphe();
                        monInterface.suppArrete(nom_extremite1,nom_extremite2);
                        ///suppression de l'arrete

                        monInterface.calculCentralite();
                    }
                    else
                    {
                        changerCouleurConsole(3); //rouge
                        std::cout<<std::endl<<"Probleme syntaxe. "<<std::endl<<"Lecture impossible.";
                        changerCouleurConsole(4); //blanc
                    }
                }
                else
                {
                    changerCouleurConsole(3); //rouge
                    std::cout<<std::endl<<"Vous avez oublie le tiret. "<<std::endl<<"Lecture impossible.";
                    changerCouleurConsole(4); //blanc
                }
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas indiquer l'arrete "<<std::endl<<"a supprimer";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("ajouter") != std::string::npos) //cacher les noms des blocs
        {
            if (commande.find('(') != std::string::npos)
            {
                size_t debut=commande.find('(')+1;

                if (commande.find('-')!=std::string::npos)
                {
                    std::string nom_extremite1;
                    std::string nom_extremite2;

                    nom_extremite1.erase();
                    nom_extremite2.erase();

                    for (size_t i=debut; i<commande.find('-'); ++i)
                    {
                        nom_extremite1+=commande[i];
                    }
                    if (commande.find('-')!=std::string::npos)
                    {
                        debut=commande.find('-')+1;
                        for (size_t i=debut; i<commande.find(')'); ++i)
                        {
                            nom_extremite2+=commande[i];
                        }
                        ///creation par copie
                        monInterface.copieGraphe();
                        monInterface.ajouterArrete(nom_extremite1,nom_extremite2);
                        ///suppression de l'arrete

                        monInterface.calculCentralite();
                    }
                    else
                    {
                        changerCouleurConsole(3); //rouge
                        std::cout<<std::endl<<"Probleme syntaxe. "<<std::endl<<"Lecture impossible.";
                        changerCouleurConsole(4); //blanc
                    }
                }
                else
                {
                    changerCouleurConsole(3); //rouge
                    std::cout<<std::endl<<"Vous avez oublie le tiret. "<<std::endl<<"Lecture impossible.";
                    changerCouleurConsole(4); //blanc
                }
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas indiquer l'arrete "<<std::endl<<"a supprimer";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("test de connexite")!=std::string::npos) //enregistrer en memoire (pas fichier) un copie de l'etat actuel
        {
            monInterface.connexite();
        }
        else if (commande.find("comparaison")!=std::string::npos)
        {
            int selec=4;
            int indice_compare;
            if (commande.find("Cvp")!=std::string::npos)
                selec=1;
            else if (commande.find("Cp")!=std::string::npos)
                selec=2;
            else if (commande.find("Cd")!=std::string::npos)
                selec=0;
            else if (commande.find("Ci")!=std::string::npos)
                selec=3;
            std::string reponse;
            std::cout<<std::endl<<"Vous etes a l'etape "<<monInterface.getIndice()
                     <<std::endl<<"Avec quel graphe souhaitez vous comparer ?"
                     <<std::endl<<"(precedent/initial/autre) : ";
            std::getline(std::cin,reponse);
            if (reponse.find("precedent")!=std::string::npos)
            {
                indice_compare=-1;
                monInterface.comparaison(indice_compare,selec);
            }
            else if (reponse.find("initial")!=std::string::npos)
            {
                indice_compare=0;
                monInterface.comparaison(indice_compare,selec);
            }
            else if (reponse.find("autre")!=std::string::npos)
            {
                std::cout<<std::endl<<"Taper le numero de l'etape souhaitee : ";
                std::cin>>indice_compare;
                monInterface.comparaison(indice_compare,selec);
            }
            else
            {
                changerCouleurConsole(3);
                std::cout<<std::endl<<"Reponse invalide."<<std::endl;
                changerCouleurConsole(4);

            }

        }
        else if (commande.find("retour")!=std::string::npos)
        {
            monInterface.retourEnArriere();
        }
        else if (commande.find("ajout graphe")!=std::string::npos)
        {
            commande.erase(0,12); //on efface "ajout graphe "
            if (commande.find(".txt")!=std::string::npos)
            {
                std::string fichier;

                size_t debut= commande.find(" ");

                //recupere le nom du fichier
                for (auto i=debut; i<commande.size(); ++i)
                    fichier+=commande[i];

                fichier.erase(0,1);

                monInterface.remplirFichier(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier"<<std::endl<<"a ouvrir";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("help")!=std::string::npos)  // afficher les commandes
        {
            affichageCommande();
        }
        else if(commande.find("stopAuto")!=std::string::npos)
        {
            util::stopAutoCin();
        }
        else if(commande.find("startScript")!=std::string::npos)
        {
            stop=2;
        }
        else if(commande.find("sommet indice")!=std::string::npos)
        {
            commande.erase(0,13); //on efface "ajout graphe "
            size_t debut = commande.find(" ");

            monInterface.setSelecSVG(commande[debut+1] - 48);
        }
        else if (commande.find("exit") != std::string::npos) //quitter l'application
        {
            if(commande.size() == 4)
                stop=1;
        }
        else
        {
            changerCouleurConsole(3);
            std::cout<<std::endl<<"L'action demandee n'est pas repertoriee."<<std::endl;
            changerCouleurConsole(4);
        }
    }

    monInterface.affichageSvg();

    return stop;
}

/// Permet de changer la couleur de la console (choix de couleur donné en paramètre) ///

void changerCouleurConsole(int couleur)
{
//    switch (couleur)
//    {
//    case 1 : //vert sur fond noir
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,0x02);
//        break;
//    }
//    case 2 : //bleu-vert sur fond noir
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,0x0b);
//        break;
//    }
//    case 3 : //rouge sur fond noir
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,0x0c);
//        break;
//    }
//    case 4 : //blanc sur fond noir
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,0x07);
//        break;
//    }
//    case 5 : //jaune sur fond noir
//    {
//        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//        SetConsoleTextAttribute(hConsole,0x06);
//        break;
//    }
//    }
}




///Boucle de jeu ///

int gererDeffilement(bool autoCin)
{
    Interface monInterface;
//    monInterface.remplirFichier("graphe-test2.txt");
//    monInterface.remplirPoids("ponde-test2.txt");
    std::string commande; //recupere la saisi de l'utilisateur
    int stop;

    if (autoCin)
        util::startAutoCin("script.txt",100);

    do
    {
        commande.clear();
        stop=0;

        std::cout<<">";

        changerCouleurConsole(2);//bleu-vert
        std::getline(std::cin,commande); //recupere la commande
        changerCouleurConsole(4);//blanc

        stop = gererCommande(commande,monInterface);
        std::cout<<std::endl;
    }
    while(stop!=1 && stop!=2);

    return stop;
}


/// Affiche sur le coté les différentes comandes possibles stockées dans un fichier ///

void affichageCommande()
{
    system("cls");
    std::string regle;
    int x=60;
    int y=2;
    util::startAutoCin("regle.txt",8);
    for(int i=0; i<200; ++i)
    {
        if(regle == "<")
        {
            x=60;
            y+=1;
        }
        x+=regle.size()+1;
        gotoligcol(x,y);
        std::cin >> regle;
    }
    util::stopAutoCin();
    gotoligcol(0,0);


}

/// Gère la position du curseur de la console ///

void gotoligcol(int A, int B)
{
//    HANDLE hout;
//    COORD Position;
//
//    hout = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    Position.X = A;
//    Position.Y = B;
//
//    SetConsoleCursorPosition(hout,Position);
}

