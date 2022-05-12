// TD1question 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


struct item {
    string quantite;
    string nom;
    string type;
    string prix;
};

int main()
{
    fstream newfile;
    newfile.open("inventaire.txt", ios::in);
    string ligne;
    int nLignes = 0;
    while (getline(newfile, ligne)) {
        nLignes++;
    }
    cout << nLignes << "asdsa";
    item* tableau = new item[nLignes];
    int j = 0;
    while (getline(newfile, ligne)) {
        cout << "q";
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
        /*
        tableau[j].nom = characteristiquesProduit[0];
        tableau[j].type = characteristiquesProduit[1];
        tableau[j].quantite = characteristiquesProduit[2];
        tableau[j].prix = characteristiquesProduit[3];
        j++;
        */
    }
    for (int i = 0; i < nLignes; i++){
        std::cout << tableau[i].nom;
    }
}