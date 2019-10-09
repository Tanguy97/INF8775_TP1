import random
import math
import sys
import time
import csv
import matplotlib.pyplot as pl
import numpy as np

from brute_force import execute_brute_force
from DpR import execute_DpR
from utils import GRID_SIZE

ALGO= sys.argv[1]
N=[1000,3000,10000,30000,100000,300000]

#Moyenne du temps de calcul

def average(T):
    TM=[]
    tm=0
    i=0;
    for t in T:
        if i<10:
            tm+=t
            i+=1
        else:
            TM.append(tm/10)
            tm=t
            i=1
    TM.append(tm/10)
    return TM

#Tracer de la courbe de puissance
def tracer_puissance(n,T,algo):
    pl.plot(np.log(N),np.log(T))
    pl.xlabel("log(nb points)")
    pl.ylabel("log(temps)")
    pl.title("Puissance" + " (" + algo + ")")
    pl.show()

#Tracer de la courbe de rapport
def tracer_rapport(n,T,algo):
    if(ALGO=="DPR"):
        pl.plot(N,T/(N*np.log(N)))
        pl.xlabel("nb points")
        pl.ylabel("temps/n.log(n)")
    else:
        pl.plot(N,T/N*N)
        pl.xlabel("nb points")
        pl.ylabel("temps/n²")
    pl.title("Rapport" + " (" + algo + ")")
    pl.show()

#Tracer de la courbe de constante
def tracer_constantes(n,T,algo):
    if(ALGO=="DPR"):
        pl.plot(N*np.log(N),T)
        pl.xlabel("n.log(n)")
    else:
        pl.plot(N*N,T)
        pl.xlabel("n²")
    pl.ylabel("temps")
    pl.title("Consante" + " (" + algo + ")")
    pl.show()


'''
--------------------------------------------------------------------
ATTENTION : Dans votre code vous devez utiliser le générateur gen.py
pour générer des points. Vous devez donc modifier ce code pour importer
les points depuis les fichiers générés.
De plus, vous devez faire en sorte que l'interface du tp.sh soit
compatible avec ce code (par exemple l'utilisation de flag -e, -a, (p et -t)).
--------------------------------------------------------------------
 '''

def main(algo):
    T=[]
    for i in N:
        for j in range(1,11):
            print(i)
            F=open("exemplaire/"+str(i)+"-"+str(j)+".txt","r")
            contenu=F.readlines()
            F.close()
            bool=True
            POINTS=[]
            for line in contenu:
                if bool:
                    bool=False
                else:
                    k=0
                    for c in line:
                        if c!=" ":
                            k+=1
                        else:
                            POINTS.append([int(line[0:k]),int(line[k+1:len(line)])])
            sorted_points_x = sorted(POINTS, key=lambda x: x[0])
            sorted_points_y = sorted(POINTS, key=lambda x: x[1])
            if ALGO == "BF":
                # Exécuter l'algorithme force brute
                time_BF = execute_brute_force(sorted_points_x)
                T.append(time_BF)
                print("Temps : ", time_BF)

            elif ALGO == "DPR":
                # Exécuter l'algorithme Diviser pour régner
                SEUIL_DPR = int(sys.argv[2]) #Seuil de récursivité
                time_DPR = execute_DpR(sorted_points_x, sorted_points_y, SEUIL_DPR)
                T.append(time_DPR)
                print("Temps : ", time_DPR)
    T_moy= average(T)
    tracer_puissance(N,T_moy,ALGO)
    tracer_rapport(N,T_moy,ALGO)
    tracer_constantes(N,T_moy,ALGO)



main(ALGO)
