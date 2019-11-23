#pragma once

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>	//Pour la lecture des exemplaires sous forme de fichiers texte

using namespace std;

/*
 Fonctions auxiliaires
 */


//Choisit et retire un élément aléatoire d'un vecteur d'entiers
int popRandomElement(vector<int>& v) ;

//Génère un mélange aléatoire de n cartes
vector<int> generateRandomShuffle(int n) ;