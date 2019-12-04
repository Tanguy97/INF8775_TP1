#include "Problem.h"

using namespace std;


int main(int argc, char** argv) {
    
    //Chargement d'un exemplaire
    Problem problem = Problem();
    problem.loadExample("./exemplaires/MTG_10_10");

    int deckSize = problem.getDeckSize();
    int nbDecks = problem.getNbDecks() ;
    

    /*
    Construction d'une première solution pour cet exemplaire
    */
    
    //Initialisation aléatoire
    //problem.initRandom();
    
    //Initialisation gloutonne
    
    int N = 100;
    
    Solution *bestSolution = new Solution(); //Meilleure solution trouvée jusqu'à présent
    int bestValue = numeric_limits<int>::min(); //Valeur de la meilleure solution trouvée jusqu'à présent
    int currentValue = numeric_limits<int>::min();
    
    for(int k=0; k<N; k++){
        problem.initGreedy(); //On répète l'initialisation gloutonne
        currentValue = problem.getBestValue();
        if(currentValue > bestValue){ //Si la valeur obtenue est la meilleure, on stocke la solution
            cout << currentValue << endl;
            bestValue = currentValue;
            bestSolution = problem.saveBestSolution();
        }
    }
    
    problem.initCopy(bestSolution); //On part de la meilleure solution trouvée
    cout << "\nMeilleure solution après glouton : " << problem.getBestValue() << endl;
    problem.printBestDeckValues();
    cout << endl;
    
    /*
     Amélioration de la solution
     */
    cout << "2-swap : " << endl;
    problem.improveWorstDeck();
    cout << "\n3-swap : " << endl;
    problem.improveWorstDeck3();
    //problem.solveShareSearch();
    //cout << "Recherche locale" << endl;
    //problem.solveLocalSearch();

    
    
    //Ecriture de la solution dans un fichier texte
    string outputFilename = "sol_" + to_string(deckSize) + "_" + to_string(nbDecks);
    problem.writeOutput(outputFilename);


    //Affichage de la valeur de la solution
    cout << "\n" << deckSize << " cartes par deck , " << nbDecks << " decks :" << problem.getBestValue()  << endl;
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
