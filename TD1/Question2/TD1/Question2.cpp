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
	int nombreSecret = rand() % (MAXIMUM-MINIMUM) + MINIMUM;

	bool nombreTrouve = false;
	string text = "Donne un nombre entier ";
	int nombrePropose;
	int compteur = 0;
	while (!nombreTrouve) {
		compteur += 1;
		nombrePropose = entrerValeurValide(text, MINIMUM, MAXIMUM);
		if (nombrePropose == nombreSecret) {
			nombreTrouve = true;
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