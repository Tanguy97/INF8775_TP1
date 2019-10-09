import numpy as np
import time


def glouton(exSize, exNum):
    #print("\n\n\n\n____", exSize, "____")

    #Exemplaire à lire
    fileName = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(fileName, skiprows = 1)

    #Initialisation de la boucle While
    currentSize = exSize
    value = 0

    #Mesure de la durée d'exécution
    start = time.time()

    while(currentSize > 0):
        #Calcul des rentabilités
        rentabilites = [(data[1][i-1] / i) for i in range(1, currentSize + 1)]
        #On récupère la position du maximum
        id = rentabilites.index(max(rentabilites))

        #On effectue la coupe de rentabilité maximale
        cut = id + 1
        #On récupère le profit associé
        profit = int(data[1][id])

        #print("\nCurrent size : ", currentSize)
        #print(rentabilites)
        #print("Cut : ", cut, "  (profit : " + str(profit) + ")")

        #On actualise la taille de l'exemplaire
        currentSize = currentSize - cut
        #Calcul du profit cumulé
        value = value + profit

    end = time.time()
    delta = end - start

    #print("\n\nTotal value : ", value)
    #print("Computed in : ", delta, " seconds.")

    return value, delta


#Tailles d'exemplaires considérées
exSizes = [10, 100, 400, 1000, 4000, 10000, 20000, 30000, 40000]
#Nombre d'exemplaires de chaque taille
N = 10

#Traitement de tous les exemplaires
for exSize in exSizes:
    meanProfit = 0
    meanTime = 0.0
    for exNum in range(1, N + 1):
        profit, runtime = glouton(exSize, exNum)
        meanProfit = meanProfit + profit
        meanTime = meanTime + runtime
    meanProfit = meanProfit / N
    meanTime = meanTime / N

    print("\n\n\n\nTAILLE " + str(exSize) + " : profit moyen = " + str(meanProfit) + " ; temps moyen = " + str(meanTime))

