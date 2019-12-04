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


vector<vector<int>> fusion(vector<vector<int>> vectors1, vector<vector<int>> vectors2){
    vector<vector<int>> result = vector<vector<int>>(2);
    while (vectors1[0].size() && vectors2[0].size()) {
        if(vectors1[0][0] > vectors2[0][0]){
            result[0].push_back(vectors1[0][0]);
            result[1].push_back(vectors1[1][0]);
            vectors1[0].erase(vectors1[0].begin());
            vectors1[1].erase(vectors1[1].begin());
        }
        else{
            result[0].push_back(vectors2[0][0]);
            result[1].push_back(vectors2[1][0]);
            vectors2[0].erase(vectors2[0].begin());
            vectors2[1].erase(vectors2[1].begin());
        }
    }
    while (vectors1[0].size()) {
        result[0].push_back(vectors1[0][0]);
        result[1].push_back(vectors1[1][0]);
        vectors1[0].erase(vectors1[0].begin());
        vectors1[1].erase(vectors1[1].begin());
    }
    while (vectors2[0].size()) {
        result[0].push_back(vectors2[0][0]);
        result[1].push_back(vectors2[1][0]);
        vectors2[0].erase(vectors2[0].begin());
        vectors2[1].erase(vectors2[1].begin());
    }
    return result;
}

//Trie parallèlement deux vecteurs d'entiers u et v, par ordre de valeurs décroissantes de u
vector<vector<int>> dualSort(vector<int> u, vector<int> v){
    int n = u.size();
    vector<vector<int>> result = vector<vector<int>>();
    
    vector<int> u1;
    vector<int> u2;
    vector<int> v1;
    vector<int> v2;
    
    if (n <= 1){
        result.push_back(u);
        result.push_back(v);
        return result;
    }
    else{
        u1 = vector<int>(u.begin(), u.begin() + n/2);
        u2 = vector<int>(u.begin() + n/2, u.end());
        v1 = vector<int>(v.begin(), v.begin() + n/2);
        v2 = vector<int>(v.begin() + n/2, v.end());
        
        return fusion(dualSort(u1, v1), dualSort(u2, v2));
    }
}
