import numpy as np
import time

def backtrack_rec(tab, currentDepth):
    n = len(tab[0])
    if(n == 0):
        return 0
    else:
        if(currentDepth > 0):
            maxProfit = 0
            for i in range(1, n+1):
                newTab = [tab[0][0: n - i], tab[1][0: n - i]]
                profit = backtrack_rec(newTab, currentDepth - 1) + int(tab[1][i-1])
                if(profit > maxProfit):
                    maxProfit = profit
            return maxProfit
        else:
            return int(tab[1][n-1])


def backtrack(filename):
    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(filename, skiprows = 1)

    #Mesure de la durée d'exécution
    start = time.time()

    #Choix de la profondeur de recherche maximale
    profit = backtrack_rec(data, 2)

    end = time.time()
    runtime = end - start

    return profit, runtime


exSize = 4000
exNum = 3

#Exemplaire à lire
filename = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

profit, runtime = backtrack(filename)

print("\n\n\n\nTAILLE " + str(exSize) + " : profit = " + str(profit) + " ; temps = " + str(runtime))
#print(solutions)