#include "Deck.h"

Deck& Deck::operator=(Deck const& d){
    deckSize = d.deckSize;
    cards = vector<int>(d.cards);
    ratings = vector<int>(d.ratings);
    
    return *this;
}

//Constructeur par défaut : paquet vide
Deck::Deck(){
    deckSize = 0;
    cards = vector<int>();
    ratings = vector<int>();
}

//Constructeur par copie
Deck::Deck(Deck const& d) : deckSize(d.deckSize), cards(d.cards), ratings(d.ratings)
{ 
}

//Constructeur complet
Deck::Deck(int n, vector<int> c){
    deckSize = n;
    cards = c;
    ratings = vector<int>(n);
}

//Renvoie la taille du paquet
int Deck::getSize(){
    return deckSize;
}

//Renvoie la carte d'indice id
int Deck::getCard(int id){
    return cards[id];
}

//Renvoie la valeur apportée par la carte d'indice id
int Deck::getRating(int id){
    return ratings[id];
}

//Renvoie l'indice de la carte la moins utile pour le deck
int Deck::findLessValuableCard(vector<int> values, vector<vector<int>> synergies){
    int lessValuableId = 0;
    int maxValueWithout = numeric_limits<int>::min();
    
    int memoCard = 0;
    int currentValueWithout = numeric_limits<int>::min();
    
    for(int i=0; i<deckSize; i++){
        memoCard = cards[i];
        cards[i] = -1;
        currentValueWithout = value(values, synergies);
        if(currentValueWithout > maxValueWithout){
            maxValueWithout = currentValueWithout;
            lessValuableId = i;
        }
        cards[i] = memoCard;
    }
    
    return lessValuableId;
}

 //Renvoie l'indice de la carte du deck d la plus utile pour le deck courant si un mouvement améliorant est possible
//Renvoie -1 sinon
int Deck::findMostValuableCardFrom(Deck *d, int lessValuableId, vector<int> values, vector<vector<int>> synergies){
    int initialValue = value(values, synergies); //La valeur initiale du deck courant
    
    int mostValuableId = -1; //L'indice de la carte du deck d la plus utile pour le deck courant
    int maxValueWith = initialValue; //La valeur virtuelle du deck courant après l'échange optimal
    
    int memoLessValuableCard = cards[lessValuableId]; //La carte à remplacer dans le deck courant
    int currentValueWith = numeric_limits<int>::min(); //La valeur virtuelle du deck courant après l'échange courant
    
    int memoCard = -1;
    
    int currentValueWithout = numeric_limits<int>::min(); //La valeur virtuelle du deck d après l'échange courant
    
    for(int i=0; i<deckSize; i++){
        memoCard = d->getCard(i);
        cards[lessValuableId] =  memoCard; //Mise à jour du deck courant
        currentValueWith = value(values, synergies); //Calcul de la valeur apportée au deck courant par l'échange
        d->setCard(memoLessValuableCard, i); //Mise à jour du deck d
        currentValueWithout =  d->value(values, synergies); //Calcul de la valeur apportée au deck d par l'échange
        if(currentValueWith > maxValueWith && currentValueWithout > initialValue){
            maxValueWith = currentValueWith;
            mostValuableId = i;
        }
        d->setCard(memoCard, i); //Restauration du deck d
    }
    
    cards[lessValuableId] = memoLessValuableCard;
    
    return mostValuableId;
}
    


//Accesseur en écriture
void Deck::setCard(int newValue, int id){
    cards[id] = newValue;
}


 //Trie les cartes du deck par ordre de valeur ajoutée décroissante
void Deck::sort(){
    vector<vector<int>> vectors = dualSort(ratings, cards);
    ratings = vectors[0];
    cards = vectors[1];
}


//Calcule la valeur totale du paquet sachant les tableaux de valeurs / synergies
int Deck::value(vector<int> values, vector<vector<int>> synergies){
    int totalValue = 0;
    int currentRating = 0; //La valeur ajoutée de la carte courante
    
    for(int i = 0; i<deckSize; i++){
        if(cards[i] >= 0){ //Une valeur négative représente une case vide
            currentRating += values[cards[i]]; //Somme des qualités de base des cartes
            for(int j = i; j<deckSize; j++){
                if(cards[j] >= 0){
                    currentRating += synergies[cards[i]][cards[j]]; //Somme des synergies de chaque paire de cartes
                }
            }
            ratings[i] = currentRating; 
            totalValue += currentRating;
            currentRating = 0;
        }
    }
    
    return totalValue;
}