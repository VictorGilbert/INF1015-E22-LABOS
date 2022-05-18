#pragma once
#include <string>
#include <utility>
#include "ListeJeux.hpp"

class Developpeur
{
	//TODO: En faire une classe qui suit les principes OO.
	Developpeur(std::string nom);
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	~Developpeur();
	//TODO: Les méthodes à faire...
	std::string getName();
	int compteJeux();
	int compteJeux(ListeJeux listeJeux);
	void miseAJourListeJeux(ListeJeux listeTousLesJeux);
	void afficherTousLesJeux();

private:
	std::pair<std::string, ListeJeux> paireNomJeux_;
};
