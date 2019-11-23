#include <cstdlib>

#include "Problem.h"

using namespace std;


int main(int argc, char** argv) {

    //Chargement d'un exemplaire
    Problem problem = Problem();
    problem.loadExample("./exemplaires/MTG_5_100");
    
    int deckSize = problem.getDeckSize();
    int nbDecks = problem.getNbDecks() ;

  
    //Construction d'une solution aléatoire pour cet exemplaire
    problem.initRandom();
    
    
    //Résolution par recherche locale
    problem.solveLocalSearch();
   
    
    //Ecriture de la solution dans un fichier texte
    string outputFilename = "sol_" + to_string(deckSize) + "_" + to_string(nbDecks);
    problem.writeOutput(outputFilename);
    
    
    //Affichage de la valeur de la solution
    cout << deckSize << " cartes par deck , " << nbDecks << " decks :" << endl;
    cout << problem.getBestValue() << "\n" << endl;
    
    
    
    /* TEST : copie d'une solution par référence
    Solution *solution = new Solution(deckSize, nbDecks);
    Solution *newSol = new Solution(*solution);
    
    cout << problem.getSolutionValue(solution) << endl;
    cout << problem.getSolutionValue(newSol) << endl;
    
    for(int i=0; i<nbDecks/2; i++){
        newSol->swapCards(i, nbDecks-1-i, 1, 4);
    }
    
    cout << problem.getSolutionValue(solution) << endl;
    cout << problem.getSolutionValue(newSol) << endl;
     */
    
    /* TEST : copie d'une solution par valeur
    Solution solution = Solution(deckSize, nbDecks);
    
    //Solution newSol(solution);
    Solution newSol = solution;
    
    cout << problem.getSolutionValue(&solution) << endl;
    cout << problem.getSolutionValue(&newSol) << endl;
    for(int i=0; i<nbDecks/2; i++){
        newSol.swapCards(i, nbDecks-1-i, 1, 4);
    }
    cout << problem.getSolutionValue(&solution)<< endl;
    cout << problem.getSolutionValue(&newSol) << endl;
     */
    
    return 0;
}

