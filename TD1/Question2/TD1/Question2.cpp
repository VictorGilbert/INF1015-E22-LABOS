#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#define MINIMUM 0
#define MAXIMUM 1000

using namespace std;

int entrerValeurValide(string& text, int min, int max) {
	int reponse;
	while (true) {
		cout << text;
		cin >> reponse;
		if (min <= reponse and reponse <= max) {
			return reponse;
		}
	}
}



int main() {
	srand(time(NULL));//permet de générer un nombre aléatoire différent a chaque execution.
	int nSecret = rand() % (MAXIMUM-MINIMUM) + MINIMUM;

	bool nTrouve = false;
	string text = "Donne un nombre entier ";
	int nPropose;
	int compteur = 0;
	while (!nTrouve) {
		compteur += 1;
		nPropose = entrerValeurValide(text, MINIMUM, MAXIMUM);
		if (nPropose == nSecret) {
			nTrouve = true;
			cout << "bravo tu as trouve en " << compteur << " essai(s).";
		}
		else if (nPropose < nSecret) {
			cout << "tu es trop bas \n";
		}
		else {
			cout << "tu es trop haut\n";
		}
	}	
}