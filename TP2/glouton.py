import numpy as np
import time


def glouton(filename):
    #Lecture de la taille de l'exemplaire
    file = open(filename,"r")
    exSize = int(file.readline())

    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(filename, skiprows = 1)

    #Initialisation de la boucle While
    currentSize = exSize
    value = 0 #Profit total
    solution = [] #Coupes successives

    #Mesure de la durée d'exécution
    start = time.time()

    #Calcul des rentabilités
    rentabilites = [(data[1][i-1] / i) for i in range(1, exSize + 1)]

    while(currentSize > 0):
        #On récupère la position du maximum parmi les rentabilités encore disponibles
        id = rentabilites.index(max(rentabilites[0:currentSize]))

        #On effectue la coupe de rentabilité maximale
        cut = id + 1
        solution.append(cut)
        #On récupère le profit associé
        profit = int(data[1][id])

        #On actualise la taille de l'exemplaire
        currentSize = currentSize - cut
        #Calcul du profit cumulé
        value = value + profit

    end = time.time()
    delta = end - start

    return value, delta, solution


#Tailles d'exemplaires considérées
exSizes = [10, 100, 400, 1000, 4000, 10000, 20000, 30000, 40000]
#Nombre d'exemplaires de chaque taille
N = 10

#Traitement de tous les exemplaires
for exSize in exSizes:
    meanProfit = 0
    meanTime = 0.0
    solutions = []
    for exNum in range(1, N + 1):
        #Exemplaire à lire
        filename = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"
        profit, runtime, solution = glouton(filename)
        meanProfit = meanProfit + profit
        meanTime = meanTime + runtime
        solutions.append(solution)
    meanProfit = meanProfit / N
    meanTime = meanTime / N

    print("\n\n\n\nTAILLE " + str(exSize) + " : profit moyen = " + str(meanProfit) + " ; temps moyen = " + str(meanTime))
    print(solutions)
