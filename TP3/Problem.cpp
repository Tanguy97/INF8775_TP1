#include "Problem.h"
#include <math.h>
#include <time.h>
//Constructeur par défaut : problème vide
Problem::Problem(){
    deckSize = 0;
    nbDecks = 0;
    values = vector<int>();
    synergies = vector<vector<int>>();
    bestSolution = new Solution();
}

//Accesseurs en lecture
int Problem::getDeckSize(){
    return deckSize;
}

int Problem::getNbDecks(){
    return nbDecks;
}

//Calcule la valeur d'une solution
int Problem::getSolutionValue(Solution *sol){
    return sol->value(values, synergies);
}

//Renvoie la valeur de la meilleure solution
int Problem::getBestValue(){
    return getSolutionValue(bestSolution);
}

//Charge les données d'un exemplaire et les stocke dans les attributs de l'instance
void Problem::loadExample(string filename){
    values = vector<int>(); //Les paramètres sont réinitialisés avant de charger un nouvel exemplaire
    synergies = vector<vector<int>>();
    bestSolution = new Solution();

    int *n = &deckSize;
    int *m = &nbDecks;

    ifstream exemplaire(filename); //Ouverture en lecture du fichier texte

    if(exemplaire){
        exemplaire >> *n; //Lecture de la taille des paquets
        exemplaire >> *m; //Lecture du nombre de paquets
        int nbCartes = (*n)*(*m);

        int value = 0;
        vector<int> cardSynergies;

        //Remplissage du tableau de valeurs
        for(int k=0; k<nbCartes; k++){
            exemplaire >> value; //Lecture de la valeur de la k-ième carte
            values.push_back(value);
        }

        //Remplissage du tableau de synergies
        for(int i=0; i<nbCartes; i++){
            for(int j=0; j<nbCartes; j++){
                exemplaire >> value; //Lecture de la synergie entre la i-ème et la j-ième carte
                cardSynergies.push_back(value);
            }
            synergies.push_back(cardSynergies);
            cardSynergies = vector<int>();
        }
        exemplaire.close();
    }
}

//Initialise aléatoirement la meilleure solution
void Problem::initRandom(){
    bestSolution = new Solution(deckSize, nbDecks);
}

//Effectue une recherche locale pour obtenir la meilleure solution possible
void Problem::solveLocalSearch(){
    //Voisinage : solutions obtenues en échangeant 2 cartes de 2 decks distincts de la solution courante

    int d = 0; //Indice du deck courant
    int c = 0; //Indice de la carte courante
    int d2 = 1; //Indice du deck avec lequel on échange
    int c2 = 0; //Indice de la carte avec laquelle on échange

    int bestValue = getBestValue();
    int currentValue = numeric_limits<int>::min();
    Solution *currentSolution = new Solution();

    //Boucle while : on choisit ici le premier voisin améliorant rencontré
    while(d<nbDecks - 1){
        while(c<deckSize){
            while(d2<nbDecks){
                while(c2<deckSize){
                    currentSolution = new Solution(*bestSolution); //On crée une solution alternative
                    currentSolution->swapCards(d, d2, c, c2); //en échangeant 2 cartes

                    currentValue = getSolutionValue(currentSolution);

                    if(currentValue > bestValue){ //Si la solution obtenue est meilleure que la solution courante
                        bestValue = currentValue;
                        bestSolution = new Solution(*currentSolution); //On met à jour la meilleure solution

                        cout << bestValue << endl;

                        d = 0; //On réinitialise les compteurs pour reprendre la recherche
                        c = 0;
                        d2 = 1;
                        c2 = -1;
                    }

                    c2++;
                }
                d2++;
                c2 = 0;
            }
            c++;
        }
        d++;
        c = 0;
    }
}

//Share search
void Problem::solveShareSearch(){
  double duree = 0;
  time_t start = time(NULL);
  time_t step;
  double seuil=60;
  Solution *currentSolution = new Solution(*bestSolution);
  currentSolution->setValue(values,synergies);
  int bestValue = currentSolution->getMinValue();
  int randomCard1 = 0;
  int randomCard2 = 0;
  while(duree<seuil){
    randomCard1 = ceil(rand()%(deckSize));
    randomCard2 = ceil(rand()%(deckSize));
    currentSolution->swapCards(currentSolution->getWorstDeck(), currentSolution->getBestDeck(),randomCard1,randomCard2);
    currentSolution->setValue(values,synergies);
    if(currentSolution->getMinValue() > bestValue){ //Si la solution obtenue est meilleure que la solution courante
        bestValue = currentSolution->getMinValue();
        bestSolution = new Solution(*currentSolution); //On met à jour la meilleure solution
        solveLocalSearch();//On l'améliore si ce n'est pas un optimum local
        bestValue=getBestValue();
        cout << bestValue << endl;
    }
    step = time(NULL);
    duree = (step-start);
  }
  cout << "local search" << endl;
  solveLocalSearch();
}

//Ecrit la meilleure solution dans un fichier texte
void Problem::writeOutput(string filename){
    bestSolution->writeOutput(filename);
}
