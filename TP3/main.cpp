#include <cstdlib>
#include "Problem.h"

using namespace std;


int main(int argc, char** argv) {

    //Chargement d'un exemplaire
    Problem problem = Problem();
    problem.loadExample("./exemplaires/MTG_10_10");

    int deckSize = problem.getDeckSize();
    int nbDecks = problem.getNbDecks() ;

    Solution *bestSolution = new Solution(deckSize, nbDecks);
    cout << problem.getSolutionValue(bestSolution) << endl;
    
    //Construction d'une solution aléatoire pour cet exemplaire
    //problem.initRandom();
    int N = 100;
    int bestValue = numeric_limits<int>::min();
    int currentValue = numeric_limits<int>::min();
    for(int k=0; k<N; k++){
        problem.initGreedy();
        currentValue = problem.getBestValue();
        if(currentValue > bestValue){
            cout << currentValue << endl;
            bestValue = currentValue;
            bestSolution = problem.saveBestSolution();
        }
    }
    
    cout << problem.getSolutionValue(bestSolution) << endl;

    //Résolution
    //problem.solveShareSearch();
    //problem.solveLocalSearch();

    //Ecriture de la solution dans un fichier texte
    string outputFilename = "sol_" + to_string(deckSize) + "_" + to_string(nbDecks);
    problem.writeOutput(outputFilename);


    //Affichage de la valeur de la solution
    cout << deckSize << " cartes par deck , " << nbDecks << " decks :" << endl;
    cout << problem.getBestValue() << "\n" << endl;
    problem.printBestDeckValues();



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
