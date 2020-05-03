//
//  graphe.cpp
//  projet
//
//  Created by Charles HAMERY on 26/04/2020.
//  Copyright © 2020 Charles HAMERY. All rights reserved.
//

#include "graphe.h"

Graphe::Graphe(std::string nomFichier )//constructeur par fichier
{

    std::ifstream ifs{nomFichier};//lecture du fichier
    if (ifs)
    {
        int orientation;
        ifs >> orientation;
        if (! ifs.fail())
        {
            m_orientation=orientation;

            int ordre;
            ifs >> ordre;
            if (! ifs.fail())
            {
                m_ordre=ordre;
                for (int i=0; i<m_ordre; ++i)
                {
                    int indice;
                    std::string nom;
                    Coord mesCoord;
                    int x;
                    int y;

                    ifs >> indice >> nom >> x >> y;

                    mesCoord.set_coord(x,y);

                    m_sommets.push_back( new Sommet(indice, nom, mesCoord) );
                }

                int taille;
                ifs>>taille;
                if (!ifs.fail())
                {
                    m_taille=taille;
                    for (int i=0; i<m_taille; ++i)
                    {
                        int indice;
                        int num1;
                        int num2;

                        ifs >> indice >> num1 >> num2;

                        m_arretes.push_back(new Arrete(indice, m_sommets[num1], m_sommets[num2]));
                        m_sommets[num1]->set_adjacent(m_sommets[num2]);
                        m_sommets[num2]->set_adjacent(m_sommets[num1]);
                    }

                    m_ponderation = false;
                }
                else
                    std::cout<<std::endl<<"Probleme lecture taille du graphe";
            }
            else
                std::cout<<std::endl<<"Probleme lecture ordre du graphe";
        }
        else
            std::cout<<std::endl<<"Probleme lecture orientation du graphe";
    }
    else
        std::cout<<std::endl<<"Impossible d'ouvrir en lecture "<<nomFichier ;



};

Graphe::Graphe(std::vector<Sommet*> buffer_s,std::vector<Arrete*> buffer_a,bool orient,bool ponderation)//2eme constructeur
{
    m_orientation=orient;
    m_ordre = (int) buffer_s.size();
    m_taille = (int) buffer_a.size();
    m_ponderation = ponderation;

    for (size_t i=0; i<buffer_s.size(); i++)
        m_sommets.push_back(new Sommet{buffer_s[i]->getId(),buffer_s[i]->getNom(),buffer_s[i]->getCoords()});

    for (size_t i=0; i<buffer_a.size(); i++)
    {
        std::vector< Sommet*> buffer_e = buffer_a[i]->getExtremite();
        int id_e1 = 0, id_e2 = 0;

        for (auto it : m_sommets)
        {
            if (it->getId() == buffer_e[0]->getId())
                id_e1=it->getId();
            if (it->getId() == buffer_e[1]->getId())
                id_e2=it->getId();
        }

        m_arretes.push_back(new Arrete{buffer_a[i]->getIndice(),m_sommets[id_e1],m_sommets[id_e2],buffer_a[i]->getPoids()});
    }
}

Graphe::~Graphe()//destructeur
{
    for (auto it : m_sommets)
        delete it;
}

bool Graphe::getOrientation()const//permet de savoir si le graphe est orienté
{
    return m_orientation;
}

int Graphe::getOrdre()const//retourne la valeur du paramètre
{
    return m_ordre;
}

int Graphe::getTaille()const//retourne la valeur du paramètre
{
    return m_taille;
}

void Graphe::remplirPoids(std::string& nomFichier)//permet le remplissage des attributs poids de sommets et arrêtes par la lecture de fichier
{
    std::ifstream ifs{nomFichier};//lecture du fichier
    if (ifs)
    {
        int taille;
        ifs>>taille;
        if (!ifs.fail())
        {
            if (taille==m_taille)
            {
                int indice,poids;
                for (int i=0; i<taille; ++i)
                {
                    ifs>>indice>>poids;
                    m_arretes[indice]->remplirPoids(poids);
                }
                m_ponderation = true;

            }
            else
                std::cout<<std::endl<<"Probleme taille du graphe incompatible";
        }
        else
            std::cout<<std::endl<<"Probleme lecture taille du graphe";

    }
    else
        std::cout<<std::endl<<"Impossible d'ouvrir en lecture "<<nomFichier ;


}

bool Graphe::suppArrete(std::string& s1, std::string& s2)//supprime une arrête selon les noms des sommets en paramètre
{
    int compt = 0;
    bool trouver = false;

    for(auto it : m_arretes)
    {
        if(it->trouverArrete(s1,s2))
        {
            it->suppAdjacent();
            m_arretes.erase(m_arretes.begin() + compt);
            trouver=true;
        }

        ++compt;
    }

    if (!trouver)
        std::cout<<std::endl<<"Arrete introuvable";
    return trouver;
}

void Graphe::ajoutArrete(std::string& extremite_un, std::string& extremite_deux)//ajout une arrête selon les noms des sommets en paramètre
{
    int indice1 = -1;
    int indice2 = -1;
    int compt = 0;
    bool exist = false;

    for(auto it : m_arretes)
        if(it->trouverArrete(extremite_un,extremite_deux))
            exist = true;

    if(!exist)
    {
        for(auto it : m_sommets)
        {
            if(it->getNom() == extremite_un || it->getNom() == extremite_deux)
            {
                if(indice1 != indice2)
                    indice2 = compt;
                else
                    indice1 = compt;
            }

            ++compt;
        }

        m_arretes.push_back(new Arrete( (int) m_arretes.size(), m_sommets[indice1], m_sommets[indice2]));
        m_sommets[indice1]->set_adjacent(m_sommets[indice2]);
        m_sommets[indice2]->set_adjacent(m_sommets[indice1]);
    }
}


void Graphe::affichageSvg (Svgfile& svgout,int selec,bool normalise,int comparaison) const
{
    ///cherhons l'indice pour adapté le graphe à la taille de l'écran 1000*800
    int indice=100; // par défaut on le met à 100
    bool stop;
    //on verifie qu'avec cette indice on peut construire tout le grpahe sinon on le réduit
    int max_x=0,temp_x,max_y=0,temp_y;
    int min_x=0,min_y=0; //pour trouver le sommet centre par la suite

    int max_ecran_x;
    int max_ecran_y=800;

    if (comparaison==0) //un seul grahe au centre
        max_ecran_x=1000;

    if (comparaison==1 || comparaison==2) // 2 graphe affihes
        max_ecran_x=500;


    //recherche des points extreme du graphe
    do
    {
        stop=true;
        for (auto it : m_sommets)
        {
            temp_x=it->getCoords().getX();
            if (temp_x>max_x)
                max_x=temp_x;
            else if (temp_x<min_x)
                min_x=temp_x;

            temp_y=it->getCoords().getY();
            if (temp_y>max_y)
                max_y=temp_y;
            else if (temp_x<min_x)
                min_x=temp_x;
        }
        if (max_x*indice>max_ecran_x || max_y*indice>max_ecran_y) //depace
        {
            indice=indice-1;
            stop=false; //on revérifie qu'avec cet nouvel indice ce soit bon
        }

    }
    while (!stop);//tant que le grpahe rentre enier

    ///centrage

    //trouver le sommet centre
    temp_x=max_x-min_x;
    if (temp_x%2==0)//si la ifférence est pair
        temp_x=temp_x/2;
    else
        temp_x=(temp_x+1)/2; //milieu

    temp_y=max_y-min_y;
    if (temp_y%2==0)//si la ifférence est pair
        temp_y=temp_y/2;
    else
        temp_y=(temp_y+1)/2; //milieu

    Coord milieu;
    milieu.set_coord(temp_x,temp_y);

    ///dessin
    for (auto it : m_arretes)
    {
        it->affichageSVG(svgout,indice,milieu,m_orientation,m_ponderation,comparaison);
    }

    double max = 0;
    double min = 100;

    for (auto it : m_sommets)
    {
        if(max < it->get_Cd(true) && selec == 0)
            max =it->get_Cd(true);
        if(max < it->get_Cvp(true) && m_ponderation && selec == 1)
            max =it->get_Cvp(true);
        if(max < it->get_Cp(true) && m_ponderation && selec == 2)
            max =it->get_Cp(true);

        if(min > it->get_Cd(true) && selec == 0)
            min =it->get_Cd(true);
        if(min > it->get_Cvp(true) && m_ponderation && selec == 1)
            min =it->get_Cvp(true);
        if(min > it->get_Cp(true) && m_ponderation && selec == 2)
            min =it->get_Cp(true);
    }

    for (auto it : m_sommets)
        it->affichageSVG(svgout,indice,milieu,max,min,selec,normalise,comparaison);
}

void Graphe::calculCd()//calcul pour tout sommets l'indice Cd
{
    for(auto it : m_sommets)
        it->calculCd(m_ordre);
}

void Graphe::calculCvp()//calcul pour tout sommets l'indice Cvp
{
    for(auto it : m_sommets)
        it->set_Cvp(1,1);

    double ancien_lambda;
    double lambda = 0;

    do
    {
        std::vector<double> sommeSucc;

        ancien_lambda = lambda;

        for(auto it : m_sommets)
            sommeSucc.push_back(it->get_SommeIndice());

        for(size_t i=0; i<sommeSucc.size(); ++i)
            lambda += (sommeSucc[i] * sommeSucc[i]);

        lambda = sqrt(lambda);

        for(size_t i=0; i<sommeSucc.size(); ++i)
            m_sommets[i]->set_Cvp(sommeSucc[i],lambda);

    }
    while(lambda - ancien_lambda == 0);
}

void Graphe::calculCp()//calcul pour tout sommets l'indice Cp
{
    for(auto it : m_sommets)
    {
        double Slongueur = 0;

        for(auto s : m_sommets)
        {
            std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total = disjtra(it->getId(), s->getId());//pour connaitre le chemin le plus court entre deux sommets
            Slongueur += pred_I_total[m_sommets[s->getId()]].second;
        }

        it->set_Cp(1/Slongueur, m_ordre);
    }
}


std::map<Sommet*, std::pair<Sommet*, int>> Graphe::disjtra (int premier, int dernier)//parcours disjtra
{

       std::priority_queue< std::pair<Sommet*, int>, std::vector<std::pair<Sommet*,int> >,CompareSommet > maFile;
       std::map<Sommet*, std::pair<Sommet*, int>> pred_I_total;

       for(auto s : m_sommets)//initialisation des marques des sommets à 0 et création de predI
           s->setMarque(0);

       maFile.push(std::make_pair(m_sommets[premier], 0) );
       m_sommets[premier]->setMarque(1);

       while(!maFile.empty())
       {
           int compt = 0;
           std::pair<Sommet*,int> buffer;

           buffer = maFile.top();
           maFile.pop();

           for(auto s : buffer.first->getAdjacent())
           {
               int total = buffer.second + 1;

               if (s.first->getMarque() == 0 || pred_I_total[s.first].second > total)
               {
                   s.first->setMarque(1);
                   maFile.push(std::make_pair(s.first, total));
                   pred_I_total[s.first] = std::make_pair(buffer.first, total);
               }

               ++compt;
           }
       }
       return pred_I_total;

}

std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> Graphe::disjtraCi(Sommet* depart)//disjtra modifié pour connaitre tout les parcours les plus courts entre 2 sommets
{
    std::priority_queue< std::pair<Sommet*, int>, std::vector<std::pair<Sommet*,int> >,CompareSommet > maFile;
    std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> pred_I_total;

    for(auto s : m_sommets)//initialisation des marques des sommets à 0 et création de predI
        s->setMarque(0);

    maFile.push(std::make_pair(depart, 0) );
    depart->setMarque(1);

    while(!maFile.empty())
    {
        std::pair<Sommet*,int> buffer;

        buffer = maFile.top();
        maFile.pop();

        for(auto s : buffer.first->getAdjacent())
        {
            int total = buffer.second + 1;

            if (s.first->getMarque() == 0 || pred_I_total[s.first].second > total)
            {
                s.first->setMarque(1);
                maFile.push(std::make_pair(s.first, total));

                std::vector<Sommet*> temp;
                temp.push_back(buffer.first);
                pred_I_total[s.first] = std::make_pair(temp, total);
            }
            else if(pred_I_total[s.first].second == total)
            {
                s.first->setMarque(1);
                pred_I_total[s.first].first.push_back(buffer.first);
            }
        }
    }

    return pred_I_total;
}

void Graphe::calculCiSommet()//calcul de l'indice Ci pour un sommet
/*le 4eme et 3eme for permettent de créer les pairs de sommet
 le 2eme for permet de savoir quel sommet étudier*/
{
    std::vector<double> ciS;

    for(size_t i = 0 ; i<m_sommets.size(); ++i)
        ciS.push_back(0);

    for(size_t i = 0 ; i<m_sommets.size(); ++i)
    {
        for(size_t d=0; d< m_sommets.size();++d)
           {
               for(size_t a=d; a< m_sommets.size();++a)
               {
                   if(d != a && i!=a && i!=d)
                   {
                       std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> pred_I_total = disjtraCi(m_sommets[d]);//connaitre tout les chemin entre un sommmet de départ et les autres
                       std::vector<std::vector<Sommet*>> chemin = recurCI(pred_I_total, m_sommets[a], m_sommets[d]);//renvoie tout les chemins possible entre dzux sommets
                       double cheminTotal = chemin.size();

                       double cheminVisite = 0;

                       for(auto c : chemin)
                           for(auto s : c)
                               if(s == m_sommets[i])
                                   cheminVisite +=1;

                       if(cheminVisite/cheminTotal > 0)
                           ciS[i] += cheminVisite/cheminTotal;
                   }
               }
           }
    }

    for(size_t i = 0 ; i<m_sommets.size(); ++i)
        m_sommets[i]->caculCi(ciS[i], m_ordre);
}

std::vector<std::vector<Sommet*>> Graphe::recurCI(std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> pred, Sommet* selec, Sommet* depart)//programme récursif pour connaitre les chemins entre 2 sommmets
{
    std::vector<std::vector<Sommet*>> chemin;

    if(selec->getId() == depart->getId())
    {
        std::vector<Sommet*> temp;
        temp.push_back(depart);
        chemin.push_back(temp);
    }
    else
    {
        for(auto i : pred[selec].first)
        {
            std::vector<std::vector<Sommet*>> buffer;
            buffer = recurCI(pred, i, depart);

            for(auto a : buffer)
            {
                a.push_back(selec);
                chemin.push_back(a);
            }
        }
    }

    return chemin;
}

void Graphe::afficherCentralite_Normalise(int selec)//selon le parmaetre l'affichage est différent
{

        if(selec == 1 || selec == 4)
        {
            std::cout<<std::endl<<"Affichage de la centralite normalisee de vecteur propre des sommets : "<<std::endl;
            for(auto it : m_sommets)
                std::cout<<it->getNom()<<": "<<it->get_Cvp(true)<<std::endl;
        }
        if(selec == 2 || selec == 4)
        {
            std::cout<<std::endl<<"Affichage de la centralite normalisee de proximite des sommets : "<<std::endl;
            for(auto it : m_sommets)
                std::cout<<it->getNom()<<": "<<it->get_Cp(true)<<std::endl;
        }

    if(selec == 0 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite normalisee de degre des sommets : "<<std::endl;
        for(auto it : m_sommets)
            std::cout<<it->getNom()<<": "<<it->get_Cd(true)<<std::endl;
    }

    if(selec == 3 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite normalisee d'intermediarite des sommets : "<<std::endl;
        for(auto it : m_sommets)
            std::cout<<it->getNom()<<": "<<it->get_Ci(true)<<std::endl;
    }
    if(selec == 5 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite normalisee d'intermediarite des arretes : "<<std::endl;
        for(auto it : m_arretes)
            std::cout<<it->getIndice()<<": "<<it->get_Ci(true)<<std::endl;
    }
}

void Graphe::afficherCentralite_NON_Normalise(int selec)//selon le parmaetre l'affichage est différent
{
   
        if(selec == 1 || selec == 4)
        {
            std::cout<<std::endl<<"Affichage de la centralite de vecteur propre des sommets : "<<std::endl;
            for(auto it : m_sommets)
                std::cout<<it->getNom()<<": "<<it->get_Cvp(false)<<std::endl;
        }
        if(selec == 2 || selec == 4)
        {
            std::cout<<std::endl<<"Affichage de la centralite de proximite des sommets : "<<std::endl;
            for(auto it : m_sommets)
                std::cout<<it->getNom()<<": "<<it->get_Cp(false)<<std::endl;
        }
    
    if(selec == 0 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite de degre des sommets : "<<std::endl;
        for(auto it : m_sommets)
            std::cout<<it->getNom()<<": "<<it->get_Cd(false)<<std::endl;
    }

    if(selec == 3 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite d'intermediarite des sommets : "<<std::endl;
        for(auto it : m_sommets)
            std::cout<<it->getNom()<<": "<<it->get_Ci(false)<<std::endl;
    }
    if(selec == 5 || selec == 4)
    {
        std::cout<<std::endl<<"Affichage de la centralite d'intermediarite des arretes : "<<std::endl;
        for(auto it : m_arretes)
            std::cout<<it->getIndice()<<": "<<it->get_Ci(false)<<std::endl;
    }
}

void Graphe::calculCentralite()//calcul tout les indices du graphe
{

    calculCvp();
    calculCp();
    calculCiArrete();
    calculCiSommet();

    calculCd();
    calculCi();
}

void Graphe::sauvegardeCentralite(std::string& nomFichier)//sauvegarde les indices des sommets sur un fichier dont le nom est reçu en paramètre
{
    std::ofstream monFlux(nomFichier.c_str());

    if(monFlux)
    {
        for(auto it : m_sommets)
        {
            monFlux << it->getId() <<" "<< it->get_Cd(false) <<" "<< it->get_Cd(true) <<" "
                    << it->get_Cvp(false) <<" "<< it->get_Cvp(true) <<" "<< it->get_Cp(false)
                    <<" "<< it->get_Cp(true) << std::endl;
        }
    }
    else
    {
        std::cout << "ERREUR: Impossible d'ouvrir le fichier lors de la sauvegarde des indices de centralite." << std::endl;
    }
}

void Graphe::afficherListeAdjacence()const//pour tout sommets affiche les adjacent
{
    std::cout<<std::endl
             <<"Liste d'adjacence :";
    for (auto it : m_sommets)
        it->afficherListeAdjacence();
}

void Graphe::afficherConsole()const//affiche en console le graphe
{
    std::cout<<std::endl
             <<"Graphe (format fichier):"
             <<std::endl<<m_orientation
             <<std::endl<<m_ordre;

    for (auto it : m_sommets)
        it->afficherConsole();

    std::cout<<std::endl<<m_taille;

    for (auto it : m_arretes)
        it->afficherConsole();
}

std::vector<Sommet*> Graphe::getSommets()const//retourne les sommets du graphe
{
    return m_sommets;
}

std::vector <Arrete*> Graphe::getArretes () const//retourne les arrêtes du graphes
{
    return m_arretes;
}


bool Graphe::connexite()//si vrai alors le graphe est connexe
{
    std::vector< Sommet* > pred_I;//vecteur des predescesseurs
    std::queue<Sommet*> maFile;//file créé

    for(auto i : m_sommets)//initialisation des sommets à blanc et des sommets de pred_I
        i->setMarque(0);

    maFile.push(m_sommets[0]);//on note se sommet dans file
    m_sommets[0]->setMarque(1);//sommet gris

    while(!maFile.empty())//tant que file pas null
    {
        int *nbre = new int;
        *nbre = maFile.front()->getId();//on retient ID du sommet
        maFile.front()->setMarque(2);//il devient noir
        pred_I.push_back( maFile.front() );
        maFile.pop();//on libère la file


        for(auto s : m_sommets[*nbre]->getAdjacent())//pour chaque adjacent
        {
            if(s.first->getMarque() == 0)//si blanc
            {
                maFile.push(s.first);//rajoute à file
                s.first->setMarque(-1);//devient gris
            }
        }
        delete nbre;//libère mémoire
    }

    if(m_sommets.size() == pred_I.size())
        return true;
    else
        return false;
}

bool Graphe::getPonde()const//vrai si graphe est pondéré
{
    return m_ponderation;

}


void Graphe::calculCiArrete()//calcul de l'indice Ci pour les arrêtes : même principe que les sommets
{
    std::vector<double> ciS;

    for(size_t i = 0 ; i<m_arretes.size(); ++i)
    {
        ciS.push_back(0);
        
        for(size_t d=0; d< m_sommets.size();++d)
           {
               for(size_t a=d; a< m_sommets.size();++a)
               {
                   if(d != a)
                   {
                       std::map<Sommet*,std::pair<std::vector<Sommet*>, int>> pred_I_total = disjtraCi(m_sommets[d]);
                       std::vector<std::vector<Sommet*>> chemin = recurCI(pred_I_total, m_sommets[a], m_sommets[d]);
                       double cheminTotal = chemin.size();

                       double cheminVisite = 0;

                       for(auto c : chemin)
                       {
                           std::vector<Arrete*> buffer;
                           
                            for(size_t i = 0 ; i<c.size();++i)
                            {
                                if(i != c.size()-1)
                                {
                                     for(auto e : m_arretes)//cherche les arrêtes du chemin
                                     {
                                        int compteur=0;
                                         
                                        for (auto it : e->getExtremite())
                                            if(it ==  c[i] || it == c[i+1] )
                                                compteur+=1;
                                         
                                        if(compteur == 2)
                                            buffer.push_back(e);
                                     }
                                }
                            }
                           
                           for(auto a : buffer)//compare les arrêtes du chemin à l'arrête selectionné
                               if(a == m_arretes[i])
                                   cheminVisite +=1;
                           
                       }
                       
                       if(cheminVisite/cheminTotal > 0)
                           ciS[i] += cheminVisite/cheminTotal;
                   }
               }
           }
    }

    for(size_t i = 0 ; i<m_arretes.size(); ++i)
        m_arretes[i]->caculCi(ciS[i], m_taille);
}


void Graphe::trouverTTchemins (std::vector<std::vector<Sommet*>>& tt_chemins, std::vector<Sommet*> chemin_divergent,Sommet* selectionne, Sommet* arrive)
{
    if (selectionne!=arrive) //tant que que je suis pas au sommet d'arrive
    {
        selectionne->setMarque(1);

        for (auto it : selectionne->getAdjacent()) //retourne un std::vector< std::pair<Sommet*, double >>
        {
            if (it.first->getMarque()!=1)
            {
                if (it.first != selectionne)
                {
                    std::vector<Sommet*> temp;
                    for (size_t i=0; i<chemin_divergent.size(); ++i) //je copie le chemin déjà parcouru
                        temp.push_back(chemin_divergent[i]);
                    temp.push_back(it.first); //j'ajoute le nv sommet parcouru
                    it.first->setMarque(1);
                    trouverTTchemins(tt_chemins,temp,it.first,arrive); //je continue le chemin en partant des adjacents

                }
            }
        }
        selectionne->setMarque(0);

    }
    else
    {
        selectionne->setMarque(0);
        tt_chemins.push_back(chemin_divergent); //qd je suis arrive au bout, je l'ajoute à tout les chemins
    }
}

void Graphe::k_connexite()
{
    //pour tout pair de sommet je cherche le nombre de chemin sommets-disjoints  allant de l'un à l'autre



    if (connexite())
    {
        for(size_t d=0; d< m_sommets.size(); ++d)
        {
            for(size_t a=d; a< m_sommets.size(); ++a)
            {
                if(d != a)
                {
                    for (auto it : m_sommets)
                        it->setMarque(0);

                    std::vector<std::vector<Sommet*>> tt_chemins_sa_sd;
                    std::vector<Sommet*> temp; //nous sert que pour le recursif de trouverTTchemin()

                    trouverTTchemins(tt_chemins_sa_sd,temp,m_sommets[a],m_sommets[d]);

                    int nb_chemin_sommets_disjoints_sa_sd=recherche_nb_chemin_sommets_disjoints(tt_chemins_sa_sd);

                    std::cout<<std::endl<<m_sommets[a]->getNom()<<"-"<<m_sommets[d]->getNom()<<" : "<<nb_chemin_sommets_disjoints_sa_sd;
                    for (auto it : tt_chemins_sa_sd)
                    {
                        std::cout<<std::endl;
                        for (auto et : it)
                            std::cout<<et->getNom();
                    }
                }
            }
        }
    }
    else
        std::cout<<std::endl<<"Votre graphe est non connexe."
                 <<std::endl<<"Etude de la k-connexite est impossible";

//    for (auto it : m_sommets)
//        it->setMarque(0);
//
//    std::vector<std::vector<Sommet*>> tt_chemins;
//    std::vector<Sommet*> temp;
//
//    trouverTTchemins(tt_chemins,temp,m_sommets[4],m_sommets[2]);
//
//    int nb_chemin_sommets_disjoints =recherche_nb_chemin_sommets_disjoints(tt_chemins);
//
//    std::cout<<std::endl<<m_sommets[4]->getNom()<<"-"<<m_sommets[2]->getNom()<<" :"<<nb_chemin_sommets_disjoints;
//    for (auto it : tt_chemins)
//    {
//        std::cout<<std::endl;
//        for (auto et : it)
//            std::cout<<et->getNom();
//    }


}

int Graphe::recherche_nb_chemin_sommets_disjoints(std::vector<std::vector<Sommet*>> tt_chemins)
{
    int nb_chemin_sommets_disjoints=0;
//    std::vector <std::vector<Sommet*>> chemins_disjoints;
//    std::vector <std::vector<Sommet*>> chemins_taille_min;
//    std::vector <Sommet*> sommets_des_chemins_disjoints;
//
//
//    int taille_min=999;
//    //je recupère le chemin le plus et si y en a plusieurs ceux qui sont sommets disjoints
//    for (auto it : tt_chemins)
//    {
//        if ((int)it.size()!=1) //on prend pas en compte
//        {
//            if ((int)it.size()<taille_min)
//                taille_min=(int)it.size();
//
//        }
//    }
//    do
//    {
//        for (auto it : tt_chemins)
//        {
//            if ((int)it.size()==taille_min)
//                chemins_taille_min.push_back(it);
//        }
//        if (chemins_taille_min.size()!=1)
//        {
//            for (size_t j=0; j<chemins_taille_min.size(); ++j)
//            {
//                for  (size_t k=j; k<chemins_taille_min.size(); ++k)
//                {
//                    if (k!=j)
//                    {
//                        int compt=0;
//                        for (size_t l=0; l<chemins_taille_min[j].size()-1; ++l)
//                            for (size_t e=0; e<chemins_taille_min[k].size()-1; ++e)
//                                if (chemins_taille_min[j][l] == chemins_taille_min[k][e])
//                                {
//                                    compt=+1;
//                                }
//
//                        if (compt==0)
//                        {
//                            chemins_disjoints.push_back(chemins_taille_min[j]);
//                            chemins_disjoints.push_back(chemins_taille_min[k]);
//                            for (size_t l=0; l<chemins_taille_min[j].size()-1; ++l)
//                                sommets_des_chemins_disjoints.push_back(tt_chemins[j][l]);
//                            for (size_t e=0; e<chemins_taille_min[k].size()-1; ++e)
//                                sommets_des_chemins_disjoints.push_back(tt_chemins[k][e]);
//                            for (auto it : tt_chemins)
//                                if ((int)it.size()==taille_min)
//                                    it.clear();
//                        }
//                    }
//                }
//            }
//        }
//        else
//        {
//            chemins_disjoints.push_back(chemins_taille_min[0]);
//            for (size_t l=0; l<chemins_taille_min[0].size()-1; ++l)
//                sommets_des_chemins_disjoints.push_back(tt_chemins[0][l]);
//            for (auto it : tt_chemins)
//                if ((int)it.size()==taille_min)
//                    it.clear();
//
//        }
//        taille_min=+1;
//
//    }
//    while (sommets_des_chemins_disjoints.empty());
//
//    int i=0;
//
//
//    do
//    {
//        int compteur=0;
//        if (tt_chemins[i].size()==1) //chemin direct
//            chemins_disjoints.push_back(tt_chemins[i]);
//        else
//        {
//            for (size_t j=0; j<tt_chemins[i].size();++j)
//                for (auto it : sommets_des_chemins_disjoints)
//                    if (tt_chemins[i][j]==it)
//                        compteur=+1;
//            if (compteur == 0)
//            {
//                chemins_disjoints.push_back(tt_chemins[i]);
//                for (size_t l=0; l<tt_chemins[i].size()-1; ++l)
//                    sommets_des_chemins_disjoints.push_back(tt_chemins[i][l]);
//            }
//        }
//        ++i;
//
//    }
//    while (i<(int)tt_chemins.size());
//
    return nb_chemin_sommets_disjoints;

}

