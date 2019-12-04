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
    deckValues = vector<int>(s.deckValues);
    deckOrder = vector<int>(s.deckOrder);
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
    deckValues = vector<int>();
    deckOrder = vector<int>();
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
    deckValues = vector<int>(s.deckValues);
    deckOrder = vector<int>(s.deckOrder);
    for(int i = 0; i<nbDecks; i++){
        decks.push_back(new Deck(*(s.decks[i])));
    }
}

//Constructeur complet : génération aléatoire de decks
Solution::Solution(int n, int m){
    deckSize = n;
    nbDecks = m;

    deckValues = vector<int>(m);
    deckOrder = vector<int>(m);
    for(int k = 0; k<m; k++){
        deckOrder[k] = k;
    }
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
    
    deckValues = vector<int>(m);
    deckOrder = vector<int>(m);
    for(int q = 0; q<m; q++){
        deckOrder[q] = q;
    }
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
    deckOrder = vector<int>(nbDecks); //L'ordre des decks est réinitialisé : chaque valeur correspondra bien au deck au même indice
    for(int q = 0; q<nbDecks; q++){
        deckOrder[q] = q;
    }
    
    int worstDeckValue = numeric_limits<int>::max();
    int currentValue = 0;
    
    for(int i=0; i<nbDecks; i++){
       currentValue = (decks[i])->value(values, synergies);
       deckValues[i] = currentValue;
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

//Trie les decks par ordre de valeur décroissante
void Solution::sortDecks(){
    vector<vector<int>> vectors = dualSort(deckValues, deckOrder);
    deckValues = vectors[0];
    deckOrder = vectors[1];
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



//Renvoie la valeur du i-ème paquet sachant les tableaux de valeurs et de synergies
int Solution::getDeckValue(int i, vector<int> values, vector< vector<int>> synergies){
    return decks[i]->value(values, synergies);
}


//Echange 2 cartes
void Solution::swapCards(int deck1, int deck2, int card1, int card2){
    int memo = decks[deck1]->getCard(card1);

    decks[deck1]->setCard(decks[deck2]->getCard(card2), card1);
    decks[deck2]->setCard(memo, card2);
}


//Echange 3 cartes (1->2->3->1)
void Solution::swap3Cards(int deck1, int deck2, int deck3, int card1, int card2, int card3){
    int memo = decks[deck1]->getCard(card1);
    
    decks[deck1]->setCard(decks[deck3]->getCard(card3), card1);
    decks[deck3]->setCard(decks[deck2]->getCard(card2), card3);
    decks[deck2]->setCard(memo, card2);
}


//Tente d'améliorer le pire deck en par échange de 2 cartes
void Solution::improveWorstDeck(vector<int> values, vector< vector<int>> synergies){
    int currentValue = value(values, synergies); //La valeur de la solution de départ : on met ici à jour les valeurs de tous les decks
    sortDecks(); //On trie les decks par ordre de valeur décroissante
    
    int c = deckSize - 1; //Rang de la carte du pire deck que l'on va essayer de remplacer (on commence par la pire carte, en supposant le deck trié)
    int d = 0; //Indice du deck dans lequel on va tenter de trouver une carte pour améliorer le pire deck (on commence par le meilleur deck)
    
    decks[deckOrder[nbDecks - 1]]->sort(); //On trie le pire deck
    int mostValuableId = -1; //L'indice de la carte du deck courant qui serait la plus utile pour améliorer le pire deck
    
    while(c > 0){ //Tant qu'on n'a pas essayé toutes les cartes du pire deck
        while(d<nbDecks - 1){ //Tant qu'on n'a pas parcouru tous les autres decks
            mostValuableId = decks[deckOrder[nbDecks - 1]]->findMostValuableCardFrom(decks[deckOrder[d]], c, values, synergies);
            if(mostValuableId >= 0){ //Une valeur négative signifie qu'aucun échange améliorant n'est possible avec le deck d
                swapCards(deckOrder[nbDecks - 1], deckOrder[d], c, mostValuableId); //Si on trouve un échange améliorant, on l'effectue
                c = deckSize - 1; //On reprend la recherche au départ
                d = 0;
                currentValue = value(values, synergies); //On remet à jour les valeurs des decks
                sortDecks(); //On trie à nouveau les decks
                decks[deckOrder[nbDecks - 1]]->sort(); //On trie à nouveau le pire deck
                cout << currentValue << endl;
            }
            d += 1;
        }
        c -= 1;
        d = 0;
    }
  
}


//Tente d'améliorer le pire deck en par échange de 3 cartes
void Solution::improveWorstDeck3(vector<int> values, vector< vector<int>> synergies){
    int currentValue = value(values, synergies); //La valeur de la solution de départ : on met ici à jour les valeurs de tous les decks
    sortDecks(); //On trie les decks par ordre de valeur décroissante
    
    int c = deckSize - 1; //Rang de la carte du pire deck que l'on va essayer de remplacer (on commence par la pire carte, en supposant le deck trié)
    
    int d1 = 0; //Indice du deck dans lequel on va tenter de trouver une carte pour améliorer le pire deck (on commence par le meilleur deck)
    int d2 = 1;
    
    decks[deckOrder[nbDecks - 1]]->sort(); //On trie le pire deck
    decks[deckOrder[d2]]->sort(); //On trie le deck intermédiaire
    int mostValuableId = -1; //L'indice de la carte du deck courant qui serait la plus utile pour améliorer le pire deck
    
    while(c > 0){ //Tant qu'on n'a pas essayé toutes les cartes du pire deck
        while(d1<nbDecks - 1){ //Tant qu'on n'a pas parcouru tous les autres decks
            mostValuableId = decks[deckOrder[nbDecks - 1]]->findMostValuableCardFrom(decks[deckOrder[d1]], c, values, synergies);
            if(mostValuableId >= 0){ //Une valeur négative signifie qu'aucun échange améliorant n'est possible avec le deck d
                swap3Cards(deckOrder[nbDecks - 1], deckOrder[d2],  deckOrder[d1], c, c, mostValuableId); //Si on trouve un échange améliorant, on l'effectue
                c = deckSize - 1; //On reprend la recherche au départ
                d1 = 0;
                currentValue = value(values, synergies); //On remet à jour les valeurs des decks
                sortDecks(); //On trie à nouveau les decks
                decks[deckOrder[nbDecks - 1]]->sort(); //On trie à nouveau le pire deck
                decks[deckOrder[d2]]->sort(); //On trie le deck intermédiaire
                cout << currentValue << endl;
            }
            d1 += 1;
        }
        c -= 1;
        d1 = 0;
    }
  
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
