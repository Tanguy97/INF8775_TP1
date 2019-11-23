#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Deck{
private:
    int deckSize; //Taille du paquet (n)
    vector<int> cards; //Indices des cartes contenues dans le paquet
    
public:
    //Accesseurs en lecture
    int getSize(); //Renvoie la taille du paquet
    int getCard(int id); //Renvoie la carte d'indice id
    
    //Accesseur en écriture
    void setCard(int newValue, int id); //Change la carte d'indice id
    
    int value(vector<int> values, vector<vector<int>> synergies); //Calcule la valeur totale du paquet sachant les tableaux de valeurs et de synergies
    
    //Constructeurs
    Deck(); //Constructeur par défaut : paquet vide
    Deck(int n, vector<int> c);
    Deck(Deck const& d);
    
    Deck& operator=(Deck const& d);
};

