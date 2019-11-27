#include "Deck.h"

Deck& Deck::operator=(Deck const& d){
    deckSize = d.deckSize;
    cards = vector<int>(d.cards);
    
    return *this;
}

//Constructeur par défaut : paquet vide
Deck::Deck(){
    deckSize = 0;
    cards = vector<int>();
}

//Constructeur par copie
Deck::Deck(Deck const& d) : deckSize(d.deckSize), cards(d.cards)
{ 
}

//Constructeur complet
Deck::Deck(int n, vector<int> c){
    deckSize = n;
    cards = c;
}

//Renvoie la taille du paquet
int Deck::getSize(){
    return deckSize;
}

//Renvoie la carte d'indice id
int Deck::getCard(int id){
    return cards[id];
}

//Accesseur en écriture
void Deck::setCard(int newValue, int id){
    cards[id] = newValue;
}

//Calcule la valeur totale du paquet sachant les tableaux de valeurs / synergies
int Deck::value(vector<int> values, vector<vector<int>> synergies){
    int totalValue = 0;
    
    for(int i = 0; i<deckSize; i++){
        if(cards[i] >= 0){ //Une valeur négative représente une case vide
            totalValue += values[cards[i]]; //Somme des qualités de base des cartes
            for(int j = i; j<deckSize; j++){
                if(cards[j] >= 0){
                    totalValue += synergies[cards[i]][cards[j]]; //Somme des synergies de chaque paire de cartes
                }
            }
        }
    }
    
    return totalValue;
}