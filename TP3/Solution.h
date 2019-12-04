#pragma once

#include "Deck.h"

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
    
    vector<int> deckValues; //Valeur de chaque deck
    vector<int> deckOrder; //Indices des decks associés aux valeurs de deckValues
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
    
    void sortDecks(); //Trie les decks par ordre de valeur décroissante
    
    void swapCards(int deck1, int deck2, int card1, int card2); //Echange 2 cartes
    void swap3Cards(int deck1, int deck2, int deck3, int card1, int card2, int card3); //Echange 3 cartes (1->2->3->1)
    
    void improveWorstDeck(vector<int> values, vector< vector<int>> synergies);
    void improveWorstDeck3(vector<int> values, vector< vector<int>> synergies);

    int getDeckValue(int i, vector<int> values, vector< vector<int>> synergies); //Renvoie la valeur du i-ème paquet sachant les tableaux de valeurs et de synergies
    int value(vector<int> values, vector< vector<int>> synergies); //Renvoie la valeur du paquet le plus faible sachant les tableaux de valeurs et de synergies
    
    void writeOutput(string filename); //Ecrit la solution dans un fichier texte

    //Constructeurs
    Solution(); //Constructeur par défaut : solution vide
    Solution(int n, int m); //Génération aléatoire des decks
    Solution(int n, int m, vector<int> values, vector< vector<int>> synergies);  //Construction gloutonne
    Solution(Solution const& s);

    Solution& operator=(Solution const& s) ;
};
