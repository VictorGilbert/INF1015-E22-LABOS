// TD1question 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct item {
    int quantite;
    string nom;
    string type;
    double prix;
};

void trouverPlusChere(item* tableau, int tailleTableau) {
    double max = 0.0;
    int indiceDuMax = 0;
    for (int i = 0; i <= tailleTableau; i++) {
        if (max < tableau[i].prix) {
            max = tableau[i].prix;
            indiceDuMax = i;
        }
    }
    cout <<  tableau[indiceDuMax].quantite << " "
         << tableau[indiceDuMax].nom << " "
         << "(" << tableau[indiceDuMax].type << ") "
         << "a " << tableau[indiceDuMax].prix << "$ chacun";
}

int main()
{
    fstream newfile;
    newfile.open("inventaire.txt", ios::in);
    string ligne;
    int nLignes = 0;
    while (getline(newfile, ligne)) {
        nLignes++;
    }
    item* tableau = new item[nLignes];

    int j = 0;
    fstream newfile2;
    newfile2.open("inventaire.txt", ios::in);
    while (getline(newfile2, ligne)) {
        string characteristiquesProduit [4];
        string souscript;
        int i = 0;
        for (char character : ligne) {
            if (character == '\t') {
                characteristiquesProduit[i] = souscript;
                souscript = "";
                i += 1;
            }
            else {
                souscript += character;
            }
        }
        characteristiquesProduit[i] = souscript;
        
        for (string test : characteristiquesProduit) {
        }
        
            tableau[j].nom = characteristiquesProduit[0];
            tableau[j].type = characteristiquesProduit[1];
            tableau[j].quantite = stoi(characteristiquesProduit[2]);
            tableau[j].prix = stod( characteristiquesProduit[3]);
            j++;
        
    }

    trouverPlusChere(tableau, nLignes);
}