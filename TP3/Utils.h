#pragma once

#include <vector>
#include <ctime>
#include <cmath>
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib>
#include <fstream>	//Pour la lecture des exemplaires sous forme de fichiers texte

using namespace std;

/*
 Fonctions auxiliaires
 */


//Choisit et retire un élément aléatoire d'un vecteur d'entiers
int popRandomElement(vector<int>& v) ;

//Génère un mélange aléatoire de n cartes
vector<int> generateRandomShuffle(int n) ;

//Trie parallèlement deux vecteurs d'entiers u et v, par ordre de valeurs décroissantes de u
vector<vector<int>> dualSort(vector<int> u, vector<int> v);

vector<vector<int>> fusion(vector<vector<int>> vectors1, vector<vector<int>> vectors2);