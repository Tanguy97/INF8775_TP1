import numpy as np
import time


def dynamique(exSize, exNum):
    #print("\n\n\n\n____", exSize, "____")

    #Exemplaire à lire
    fileName = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(fileName, skiprows = 1)

    #Mesure de la durée d'exécution
    start = time.time()

    r = [0]

    for j in range(1, exSize + 1):
        r_aux = [int(data[1][i-1]) + r[j - i] for i in range(1, j + 1)]
        r.append(max(r_aux))

    end = time.time()
    delta = end - start

    return r[exSize], delta



#Tailles d'exemplaires considérées
exSizes = [10, 100, 400, 1000, 4000, 10000] #, 20000, 30000, 40000]
#Nombre d'exemplaires de chaque taille
N = 3

#Traitement de tous les exemplaires
for exSize in exSizes:
    meanProfit = 0
    meanTime = 0.0
    for exNum in range(1, N + 1):
        profit, runtime = dynamique(exSize, exNum)
        meanProfit = meanProfit + profit
        meanTime = meanTime + runtime
    meanProfit = meanProfit / N
    meanTime = meanTime / N

    print("\n\n\n\nTAILLE " + str(exSize) + " : profit moyen = " + str(meanProfit) + " ; temps moyen = " + str(meanTime))