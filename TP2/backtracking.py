import numpy as np
import time

def backtrack_rec(tab, currentDepth):
    n = len(tab[0])
    if(n == 0): #Si on a atteint une feuille du graphe
        return 0, []
    else:
        if(currentDepth > 0): #Si la profondeur maximale autorisée a été atteinte
            maxProfit = 0
            bestSolution = []
            for i in range(1, n+1): #On cherche récursivement la meilleure coupe parmi toutes celles possibles
                newTab = [tab[0][0: n - i], tab[1][0: n - i]]

                profitFils, solutionFils = backtrack_rec(newTab, currentDepth - 1)

                profit = profitFils + int(tab[1][i-1])
                solution = solutionFils + [i]
                if(profit > maxProfit):
                    maxProfit = profit
                    bestSolution = solution
            return maxProfit, bestSolution #On renvoie le profit total et la suite de coupes associées
        else:
            return int(tab[1][n-1]), [n-1]


def backtrack(filename):
    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(filename, skiprows = 1)

    #Mesure de la durée d'exécution
    start = time.time()

    #Choix de la profondeur de recherche maximale
    profit, solution = backtrack_rec(data, 2)

    end = time.time()
    runtime = end - start

    return profit, runtime, solution


exSize = 4000
exNum = 3

#Exemplaire à lire
filename = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

profit, runtime, solution = backtrack(filename)

print("\n\n\n\nTAILLE " + str(exSize) + " : profit = " + str(profit) + " ; temps = " + str(runtime))
print(solution)