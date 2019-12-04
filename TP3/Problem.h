#pragma once

#include "Solution.h"

/*
 La classe Problem contient les informations sur les paramètres de l'exemplaire et sur l'état courant de la résolution.
 */

class Problem{
private :
    int deckSize; //Nombre de cartes dans chaque paquet (n)
    int nbDecks; //Nombre de paquets à constituer (m)
    vector<int> values; //Tableau des valeurs des cartes
    vector<vector<int>> synergies; //Tableau des synergies entre les paires de cartes

    Solution *bestSolution; //Meilleure solution trouvée jusqu'à présent

public :
    //Accesseurs en lecture
    int getDeckSize();
    int getNbDecks();

    int getSolutionValue(Solution *sol); //Renvoie la valeur d'une solution
    int getBestValue(); //Renvoie la valeur de la meilleur solution trouvée
    void printBestDeckValues(); //Affiche les valeurs des decks de la meilleure solution trouvée

    //Charge les données d'un exemplaire et les stocke dans les attributs de l'instance
    void loadExample(string filename);

    void initRandom(); //Initialise aléatoirement la meilleure solution
    void initGreedy(); //Initialise de façon gloutonne la meilleure solution
    void initCopy(Solution * s); //Initialisation par copie d'une solution
    
    Solution* saveBestSolution(); //Renvoie une copie de la meilleure solution trouvée
    
    void improveWorstDeck();
    void improveWorstDeck3();
    
    void solveLocalSearch(); //Effectue une recherche locale pour obtenir la meilleure solution possible
    void solveShareSearch();
    
    void writeOutput(string filename); //Ecrit la meilleure solution dans un fichier texte

    Problem(); //Constructeur par défaut : problème vide
};
