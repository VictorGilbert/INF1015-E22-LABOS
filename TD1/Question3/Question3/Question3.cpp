#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <cstdlib>
using namespace std;

#define TEMPS_MIN 1

#define VITESSE_MIN -100
#define VITESSE_MAX 100
//#define INFINITY

int entrerValeurValide(string& text, double min, double max) {
	int reponse;
	while (true) {
		cout << text;
		cin >> reponse;
		if (min <= reponse and reponse <= max) {
			return reponse;
		}
	}
}

int diffPos(int pos1, int pos2) {
	if (pos1 == pos2)
		return 0;
	else if (pos1 > pos2)
		return 1;
	else
		return -1;
}

int posActualise(int pos, int vitesse) {
	return pos + vitesse;
}

int main() {
	int tempsTotal,
		pos1,
		pos2,
		vit1,
		vit2;
	int tempsActuel = 0;
	
	bool pasDeCollision = true;

	
	string tempsTotalTexte = "Entrez le temps total: ";
	string pos1Texte = "Entrez la position initiale du premier train : ";
	string pos2Texte = "Entrez la position initiale du second train : ";
	string vit1Texte = "Entrez la vitesse du premier train : ";
	string vit2Texte = "Entrez la vitesse du premier train : ";


	tempsTotal = entrerValeurValide(tempsTotalTexte, TEMPS_MIN, INFINITY);
	pos1 = entrerValeurValide(pos1Texte, -INFINITY, INFINITY);
	vit1 = entrerValeurValide(vit1Texte, VITESSE_MIN, VITESSE_MAX);
	pos2 = entrerValeurValide(pos2Texte, -INFINITY, INFINITY);
	vit2 = entrerValeurValide(vit2Texte, VITESSE_MIN, VITESSE_MAX);

	int diffPosInitial = diffPos(pos1, pos2);
	while (tempsActuel != tempsTotal and pasDeCollision) {
		pos1 = posActualise(pos1, vit1);
		pos2 = posActualise(pos2, vit2);
		tempsActuel += 1;
	 
		cout << "Apres " << tempsActuel << " seconde(s)\n";
		cout << "Train 1 :" << pos1 << "\n";
		cout << "Train 2 :" << pos2 << "\n";
		if (diffPos(pos1, pos2) != diffPosInitial) {
			pasDeCollision = false;
			cout << "Il y a eu une collision pendant la " << tempsActuel << "e seconde! \n";
		}
	}
}