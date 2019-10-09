import numpy as np
import time


def dynamique(exSize, exNum):
    #print("\n\n\n\n____", exSize, "____")

    #Exemplaire à lire
    fileName = "./exemplaires/" + str(exSize) + "-" + str(exNum) + ".txt"

    #Conversion des données dans un tableau à 2 lignes
    data = np.loadtxt(fileName, skiprows = 1)

    r = [0]

    for j in range(1, exSize + 1):
        r_aux = [data[1][i-1] + r[j - i] for i in range(1, j + 1)]
        r.append(max(r_aux))

    return r[exSize]

print(dynamique(30000, 1))