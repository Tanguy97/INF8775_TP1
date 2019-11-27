#pragma once

#include <limits>

#include "Deck.h"
#include "Utils.h"

/*
 Une solution est un ensemble de Decks qui respecte les contraintes du problème (nombre de decks, nombre de cartes par deck, chaque carte est présente exactement une fois...)
 */

class Solution{
private:
    int deckSize; //Nombre de cartes dans chaque paquet (n)
    int nbDecks; //Nombre de paquets à constituer (m)
    int minValue;
    int maxValue;
    int bestDeck;
    int worstDeck;
    vector<Deck*>  decks; //Ensemble des n paquets de la solution

public:
    //Accesseurs en lecture
    int getDeckSize();
    int getNbDecks();
    int getMinValue();
    int getMaxValue();
    int getBestDeck();
    int getWorstDeck();
    void setValue(vector<int> values, vector< vector<int>> synergies);
    void swapCards(int deck1, int deck2, int card1, int card2); //Echange 2 cartes

    int value(vector<int> values, vector< vector<int>> synergies); //Renvoie la valeur du paquet le plus faible sachant les tableaux de valeurs et de synergies

    void writeOutput(string filename); //Ecrit la solution dans un fichier texte

    //Constructeurs
    Solution(); //Constructeur par défaut : solution vide
    Solution(int n, int m); //Génération aléatoire des decks
    Solution(Solution const& s);

    Solution& operator=(Solution const& s) ;
};
