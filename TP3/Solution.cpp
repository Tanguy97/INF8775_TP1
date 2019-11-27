#include "Solution.h"

//Copie une solution
Solution& Solution::operator=(Solution const& s)
{
    deckSize = s.deckSize;
    nbDecks = s.nbDecks;
    minValue=s.minValue;
    maxValue=s.maxValue;
    worstDeck=s.worstDeck;
    bestDeck=s.bestDeck;
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
    minValue=0;
    maxValue=0;
    worstDeck=0;
    bestDeck=0;
    decks = vector<Deck*>();
}

//Constructeur par recopie
Solution::Solution(Solution const& s)
{
    deckSize = s.deckSize;
    nbDecks = s.nbDecks;
    minValue=s.minValue;
    maxValue=s.maxValue;
    worstDeck=s.worstDeck;
    bestDeck=s.bestDeck;
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


//Constructeur complet : génération gloutonne des decks
Solution::Solution(int n, int m, vector<int> values, vector< vector<int>> synergies){
    deckSize = n;
    nbDecks = m;
    decks = vector<Deck*>();
    
    int nbCards = deckSize*nbDecks;
    vector<int> remainingCards(nbCards); //Indices des cartes à répartir dans les decks (initialement 0, 1, ..., nbCards-1)
    for(int l=0; l<nbCards; l++){
        remainingCards[l] = l;
    }
    
    vector<int> cards(deckSize, -1); //Une valeur négative représente une case vide dans un deck
    
    for(int i=0; i<nbDecks; i++){
        decks.push_back(new Deck(deckSize, cards));
    }
    
    int cardId = -1;
    
    for(int b=0; b<nbDecks; b++){
        cardId = popRandomElement(remainingCards);
        decks[b]->setCard(cardId, 0);
    }
    
    vector<int> currentDeckValues(nbDecks, numeric_limits<int>::min()); //On stocke les valeurs courantes de chaque deck
    
    int bestCardId = 0;
    int currentValue = numeric_limits<int>::min();
    
    for(int a=1; a<deckSize; a++){
        for(int j=0; j<nbDecks; j++){ //Remplissage des decks
            for(int k=0; k<remainingCards.size(); k++){
                decks[j]->setCard(remainingCards[k], a);
                currentValue = decks[j]->value(values, synergies);
                if(currentValue > currentDeckValues[j]){
                    bestCardId = k;
                    currentDeckValues[j] = currentValue;
                }
            }
            decks[j]->setCard(remainingCards[bestCardId], a);
            swap(remainingCards[bestCardId], remainingCards[remainingCards.size() - 1]);
            remainingCards.pop_back();
        }
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

void Solution::setValue(vector<int> values, vector< vector<int>> synergies){
  minValue = numeric_limits<int>::max();
  maxValue = numeric_limits<int>::min();
  worstDeck=0;
  bestDeck=0;
  int currentValue = 0;
  for(int i=0; i<nbDecks; i++){
      currentValue = (decks[i])->value(values, synergies);
      if(currentValue < minValue){
          worstDeck = i;
          minValue = currentValue;
      }
      if(currentValue > maxValue){
          bestDeck = i;
          maxValue = currentValue;
      }
  }
}

//Accesseurs en lecture
int Solution::getDeckSize(){
    return deckSize;
}

int Solution::getNbDecks(){
    return nbDecks;
}

int Solution::getMinValue(){
    return minValue;
}

int Solution::getMaxValue(){
    return maxValue;
}

int Solution::getWorstDeck(){
    return worstDeck;
}

int Solution::getBestDeck(){
    return bestDeck;
}

int Solution::getDeckValue(int i, vector<int> values, vector< vector<int>> synergies){
    return decks[i]->value(values, synergies);
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
