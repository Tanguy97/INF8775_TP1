#include "Utils.h"

//Choisit et retire un élément aléatoire d'un vecteur d'entiers
int popRandomElement(vector<int>& v)
{
    int n = v.size();

    //Récupération d'un élément aléatoire de v
    srand(time(NULL));
    int index = rand() % n;
    int elem = v[index];

    //Suppression de l'élément choisi
    swap(v[index], v[n - 1]);
    v.pop_back();

    return elem;
}


//Génère un mélange aléatoire de n cartes (numérotées de 0 à n-1)
vector<int> generateRandomShuffle(int n)
{
    vector<int> v(n);
    vector<int> permutation;

    //Ordre initial : 0, 1, 2, ... , n-1
    for (int i = 0; i < n; i++)
        v[i] = i;

   //On extrait aléatoirement un élément de v
    while (v.size()) { 
        permutation.push_back(popRandomElement(v));
    }

    return permutation;
}
