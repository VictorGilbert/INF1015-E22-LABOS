#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
using namespace std;
#define MINIMUM 0
#define MAXIMUM 1000


int entrerValeurValide(string& text, int min, int max) {
	bool pasLaBonneValeure = true;
	int reponse;
		while (pasLaBonneValeure) {
			cout << text;
			cin >> reponse;
			if (min <= reponse and reponse <= max) {
				//pasLaBonneValeure = false;
				return reponse;
			}
	}
}



int main() {
	//miaw
	int nombreSecret = rand() % MAXIMUM + MINIMUM;
	srand(time(NULL));
	for (int i = 0; i < 500; i++) {
		nombreSecret = rand() % MAXIMUM + MINIMUM;
	}

	bool nombreNonTrouve = true;
	string text = "Donne un nombre entier ";
	int nombrePropose;
	int compteur = 0;
	while (nombreNonTrouve) {
		compteur += 1;
		nombrePropose = entrerValeurValide(text, MINIMUM, MAXIMUM);
		if (nombrePropose == nombreSecret) {
			nombreNonTrouve = false;
			cout << "bravo tu as trouve en " << compteur << " essai(s).";

		}
		else if (nombrePropose < nombreSecret) {
			cout << "tu es trop bas \n";
		}
		else {
			cout << "tu es trop haut\n";
		}
	}	
}