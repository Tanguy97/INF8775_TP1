#pragma once

#include "Utils.h"

using namespace std;

class Deck{
private:
    int deckSize; //Taille du paquet (n)
    vector<int> cards; //Indices des cartes contenues dans le paquet
    vector<int> ratings; //Valeurs ajoutées par chacune des cartes //Attention : n'utiliser qu'après avoir appelé la méthode "value"
    
public:
    //Accesseurs en lecture
    int getSize(); //Renvoie la taille du paquet
    int getCard(int id); //Renvoie la carte d'indice id
    int getRating(int id); //Renvoie la valeur apportée par la carte d'indice id
    
    //Accesseur en écriture
    void setCard(int newValue, int id); //Change la carte d'indice id
    
    //Trie les cartes du deck par ordre de valeur ajoutée décroissante
    void sort();
    
    int value(vector<int> values, vector<vector<int>> synergies); //Calcule la valeur totale du paquet sachant les tableaux de valeurs et de synergies
    
    int findLessValuableCard(vector<int> values, vector<vector<int>> synergies); //Renvoie l'indice de la carte la moins utile pour le deck
    int findMostValuableCardFrom(Deck *d, int lessValuableId, vector<int> values, vector<vector<int>> synergies); //Renvoie l'indice de la carte du deck d la plus utile pour le deck courant
    
    //Constructeurs
    Deck(); //Constructeur par défaut : paquet vide
    Deck(int n, vector<int> c);
    Deck(Deck const& d);
    
    Deck& operator=(Deck const& d);
};

