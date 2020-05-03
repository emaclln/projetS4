
///            CODE REPRIS DE NOTRE PROJET S3             ///
/// Auteur : Emma Collin, Charles Hamery et Julie Trochon ///


#include "menu.h"
#include "../Interface.h"
#include "util.h"

/// Code d'appel des fonction associés à la commande ///

int gererCommande(std::string& commande,Interface& monInterface)
{
    int stop=0;

    if (commande.empty())
        std::cout<<std::endl<<"Vous n'avez pas demander d'action."<<std::endl;
    else
    {
        if (commande.find("ponderation") != std::string::npos) //charge le fichier de pondération
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

                    fichier.erase(0,1); //efface l'espace
                    monInterface.remplirPoids(fichier);
                }
                else
                {
                    changerCouleurConsole(3); //rouge
                    std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier a ouvrir";
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

                fichier.erase(0,1); //efface l'espace
                monInterface.initialisation();
                monInterface.ajouterGraphe(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier a ouvrir";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("calculer indice") != std::string::npos) //calculer les indice de centralité
        {
            monInterface.calculCentralite();

            //definission des parametres affichage
            int selec=4;
            if (commande.find("Cvp")!=std::string::npos)
                selec=1;
            else if (commande.find("Cp")!=std::string::npos)
                selec=2;
            else if (commande.find("Cd")!=std::string::npos)
                selec=0;
            else if (commande.find("Ci sommet")!=std::string::npos)
                selec=3;
            else if (commande.find("Ci arrete")!=std::string::npos)
                selec=5;
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
                monInterface.setNormaliseSVG(false); //affichage SVG non normalise par defaut
            }

        }
        else if (commande.find("save indice") != std::string::npos) //sauvegarde dans un fichier les indices calculer
        {
            commande.erase(0,12); //efface 'save inidice'
            if (commande.find(" ")!=std::string::npos)
            {
                std::string fichier;
                size_t debut = commande.find(" ")+1;

                //recupere le nom du fichier
                for (auto i=debut; i<commande.size(); ++i)
                    fichier+=commande[i];

                monInterface.sauvegarderCentralite(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier de sauvegarde";
                changerCouleurConsole(4); //blanc
            }
        }

        else if (commande.find("supprimer") != std::string::npos) //supprime une arrete
        {
            if (commande.find('(') != std::string::npos)
            {
                size_t debut=commande.find('(')+1;

                if (commande.find('-')!=std::string::npos)
                {
                    std::string nom_extremite1;
                    std::string nom_extremite2;

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
                        ///suppression de l'arrete
                        monInterface.suppArrete(nom_extremite1,nom_extremite2);
                        ///calcul automatique des nouveaux indices
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
                std::cout<<std::endl<<"Vous n'avez pas indiquer l'arrete a supprimer";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("ajouter") != std::string::npos) //ajout d'une arrete
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
                        ///ajout de l'arrete
                        monInterface.ajouterArrete(nom_extremite1,nom_extremite2);
                        //calcul des nouveaux indices
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
                std::cout<<std::endl<<"Vous n'avez pas indiquer l'arrete a supprimer";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("test de k-connexite")!=std::string::npos) //test la k-connexite du graphe actuel
        {
            monInterface.k_connexite();
        }
        else if (commande.find("test de connexite")!=std::string::npos) //test la connexite du graphe actuel
        {
            monInterface.connexite();
        }
        else if (commande.find("comparaison")!=std::string::npos) //compare les indices entre 2 graphes
        {
            ///on determine les options de comparaison et d'affichage
            int selec=4;
            int indice_compare;
            if (commande.find("Cvp")!=std::string::npos)
                selec=1;
            else if (commande.find("Cp")!=std::string::npos)
                selec=2;
            else if (commande.find("Cd")!=std::string::npos)
                selec=0;
            else if (commande.find("Ci sommet")!=std::string::npos)
                selec=3;
            else if (commande.find("Ci arrete")!=std::string::npos)
                selec=5;

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
        else if (commande.find("retour")!=std::string::npos) //supprime l'etape actuelle et revient à l'étape d'avant
        {
            monInterface.retourEnArriere();
        }
        else if (commande.find("ajout graphe")!=std::string::npos) //ajoute un graphe
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

                monInterface.ajouterGraphe(fichier);
            }
            else
            {
                changerCouleurConsole(3); //rouge
                std::cout<<std::endl<<"Vous n'avez pas donne le nom du fichier a ouvrir";
                changerCouleurConsole(4); //blanc
            }
        }
        else if (commande.find("affichage console adjacence")!=std::string::npos)  // afficher la liste d'adjacence du graphe actuel
        {
            monInterface.afficherListeAdjacence();
        }
        else if (commande.find("affichage console graphe")!=std::string::npos)  // afficher le graphe actuel façon fichier
        {
            monInterface.afficherConsole();
        }
        else if (commande.find("help")!=std::string::npos)  // afficher les commandes
        {
            affichageCommande();
        }
        else if(commande.find("stopAuto")!=std::string::npos) //à mettre à la fin du script si on veut en créé un
        {
            util::stopAutoCin();
        }
        else if(commande.find("startScript")!=std::string::npos) //lance un un fichier "script.txt" qui fait des commandes automatiques
        {
            stop=2;
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

    monInterface.affichageSvg(); //affiche le graphe actuel

    if (monInterface.getComparaisonSVG()) //il faut afficher 2 graphes
    {
        //on initialise l'affichage pour le prochain affichage
        monInterface.setComparaisonSVG(0);
        monInterface.setNormaliseSVG(false);
        monInterface.setSelecSVG(4);
    }



    return stop;
}

/// Permet de changer la couleur de la console (choix de couleur donné en paramètre) ///

void changerCouleurConsole(int couleur)
{
    switch (couleur)
    {
    case 1 : //vert sur fond noir
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0x02);
        break;
    }
    case 2 : //bleu-vert sur fond noir
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0x0b);
        break;
    }
    case 3 : //rouge sur fond noir
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0x0c);
        break;
    }
    case 4 : //blanc sur fond noir
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0x07);
        break;
    }
    case 5 : //jaune sur fond noir
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole,0x06);
        break;
    }
    }
}




///Boucle de commande ///

int gererDeffilement(bool autoCin)
{
    Interface monInterface;
    std::string commande; //recupere la saisi de l'utilisateur
    int stop;

    if (autoCin)
        util::startAutoCin("script.txt",100); //si jamais on veut faire un script c'est possible
                                             // actuellement aucun fichier script a été créé

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
    while(stop!=1 && stop!=2); //en fonction de l'autoCin ou pas

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
        if(regle=="<")
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
    HANDLE hout;
    COORD Position;

    hout = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = A;
    Position.Y = B;

    SetConsoleCursorPosition(hout,Position);
}

