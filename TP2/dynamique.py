import numpy as np
import time


def dynamique(filename):
    #Lecture de la taille de l'exemplaire
    file = open(filename,"r")
    exSize = int(file.readline())

    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(filename, skiprows = 1)

    #Mesure de la durée d'exécution
    start = time.time()

    #r[j] est le profit optimal pour une taille d'exemplaire <= j
    r = [0]
    r_aux = [[]]

    for j in range(1, exSize + 1):
        r_aux.append([int(data[1][i-1]) + r[j - i] for i in range(1, j + 1)])
        #On obtient r[j] en effectuant le choix optimal à partir des r[j-i]
        r.append(max(r_aux[j]))

    #La réponse au problème se trouve donc en r[exSize]
    profit = r[exSize]

    #Récupérons maintenant les choix de coupes successifs
    currentSize = exSize

    choice = 0
    solution = [] #Coupes successives

    while (currentSize > 0):
        choice = (r_aux[currentSize]).index(max(r_aux[currentSize])) + 1
        solution.append(choice)

        currentSize -= choice

    end = time.time()
    runtime = end - start

    return profit, runtime, solution



#Tailles d'exemplaires considérées
exSizes = [10, 100, 400, 1000, 4000, 10000] #, 20000, 30000, 40000]
#Nombre d'exemplaires de chaque taille
N = 3
filename = ""

#Traitement de tous les exemplaires
for exSize in exSizes:
    meanProfit = 0
    meanTime = 0.0
    solutions = []
    for exNum in range(1, N + 1):
        #Exemplaire à lire
        filename = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"
        profit, runtime, solution = dynamique(filename)
        meanProfit = meanProfit + profit
        meanTime = meanTime + runtime
        solutions.append(solution)
    meanProfit = meanProfit / N
    meanTime = meanTime / N

    print("\n\n\n\nTAILLE " + str(exSize) + " : profit moyen = " + str(meanProfit) + " ; temps moyen = " + str(meanTime))
    print(solutions)