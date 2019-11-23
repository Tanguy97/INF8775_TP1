#include "Solution.h"

//Copie une solution
Solution& Solution::operator=(Solution const& s) 
{
    deckSize = s.deckSize;
    nbDecks = s.nbDecks;
    
    decks = vector<Deck *>();
    for(int i = 0; i<nbDecks; i++){
        decks.push_back(new Deck(*(s.decks[i])));
    }
    
    return *this;
}

//Constructeur par défaut : solution vide
Solution::Solution(){
    deckSize = 0;
    nbDecks = 0;
    decks = vector<Deck*>();
}

//Constructeur par recopie
Solution::Solution(Solution const& s) 
{
    deckSize = s.deckSize;
    nbDecks = s.nbDecks;
    
    decks = vector<Deck *>();
    for(int i = 0; i<nbDecks; i++){
        decks.push_back(new Deck(*(s.decks[i])));
    }
}

//Constructeur complet : génération aléatoire de decks
Solution::Solution(int n, int m){
    deckSize = n;
    nbDecks = m;

    decks = vector<Deck*>();
    
    int nbCards = n*m;
    int id = 0;
    
    Deck* currentDeck = new Deck();
    vector<int> currentCards;
    
    //Génération d'un mélange aléatoire des cartes
    vector<int> shuffle = generateRandomShuffle(nbCards);
    
    //Création des decks en partageant le paquet de cartes mélangé
    for(int i=0; i<nbDecks; i++){
         for(int j=0; j<deckSize; j++){
             id = i*deckSize + j;
             //Ajout de la carte shuffle[id] au deck courant
             currentCards.push_back(shuffle[id]);
         }
         currentDeck = new Deck(deckSize, currentCards);
         decks.push_back(currentDeck);
         
         currentCards = vector<int>();
    }
}

//Calcule la valeur totale de la solution : celle du paquet le plus faible
int Solution::value(vector<int> values, vector< vector<int>> synergies){
    int worstDeckValue = numeric_limits<int>::max();
    int currentValue = 0;
    
    for(int i=0; i<nbDecks; i++){
        currentValue = (decks[i])->value(values, synergies);
        if(currentValue < worstDeckValue){
            worstDeckValue = currentValue;
        }      
    }
    
    return worstDeckValue;
}

//Accesseurs en lecture
int Solution::getDeckSize(){
    return deckSize;
}

int Solution::getNbDecks(){
    return nbDecks;
}

//Echange 2 cartes
void Solution::swapCards(int deck1, int deck2, int card1, int card2){
    int memo = decks[deck1]->getCard(card1);
    
    decks[deck1]->setCard(decks[deck2]->getCard(card2), card1);
    decks[deck2]->setCard(memo, card2);
}

//Ecriture du résultat
void Solution::writeOutput(string filename){
    ofstream exemplaire(filename); //Ouverture en écriture du fichier texte
    
    if(exemplaire){
        for(int i=0; i<nbDecks; i++){
            for(int j=0; j<deckSize; j++){
                exemplaire << decks[i]->getCard(j) << " ";
            }
            exemplaire << "\n";
        }
        exemplaire.close();
    }
}