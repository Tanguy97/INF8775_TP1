import numpy as np
import time

depthLimit = 2

def backtrack(tab, currentDepth):
    n = len(tab[0])
    if(n == 0):
        return 0
    else:
        if(currentDepth < depthLimit):
            maxProfit = 0
            for i in range(1, n+1):
                newTab = [tab[0][0: n - i], tab[1][0: n - i]]
                profit = backtrack(newTab, currentDepth + 1) + int(tab[1][i-1])
                if(profit > maxProfit):
                    maxProfit = profit
            return maxProfit
        else:
            return int(tab[1][n-1])


exSize = 4000
exNum = 3

#Exemplaire à lire
fileName = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

#Conversion des données dans un tableau à 2 lignes
data = np.loadtxt(fileName, skiprows = 1)

print(backtrack(data, 0))

# a = [1, 2, 3, 4, 5, 6]
# print(a[0:4])