#include "Jeu.hpp"
#include <iostream>
#include <fstream>
#include "cppitertools/range.hpp"
#include "gsl/span"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  //NOTE: Incompatible avec le "placement new", ne pas utiliser cette entête si vous utilisez ce type de "new" dans les lignes qui suivent cette inclusion.

using namespace std;
using namespace iter;
using namespace gsl;

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
gsl::span<Jeu*> spanListeJeux(const ListeJeux& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
gsl::span<Designer*> spanListeDesigners(const ListeDesigners& liste)
{
	return gsl::span(liste.elements, liste.nElements);
}
#pragma endregion

//TODO: Fonction qui cherche un designer par son nom dans une ListeJeux.
// Cette fonction renvoie le pointeur vers le designer si elle le trouve dans
// un des jeux de la ListeJeux. En cas contraire, elle renvoie un pointeur nul.

Designer* chercheDesigner(ListeJeux &listeJeux, const string nomDesigner) {
 // On parcours une liste de jeu, on cherche les jeux, dans les jeux on cherche la liste de designers, et dans cette on cherche un designer en particulier
	span<Jeu*> listeDeJeux = spanListeJeux(listeJeux);
	for (const Jeu* ptrjeu : listeDeJeux) {
		Jeu jeu = *ptrjeu;
		span<Designer*> listeDesigners = spanListeDesigners(jeu.designers);
		for (Designer* ptrDesigner : listeDesigners) {
			Designer designer = *ptrDesigner;
			if (designer.nom == nomDesigner) {
				return ptrDesigner;
			}


		}

	}
	return nullptr;
}


Designer* lireDesigner(istream& fichier, ListeJeux listeJeux)
{
	Designer designer = {}; // On initialise une structure vide de type Designer.
	designer.nom = lireString(fichier);
	designer.anneeNaissance = lireUint16(fichier);
	designer.pays = lireString(fichier);
	if (chercheDesigner(listeJeux,designer.nom)!= nullptr)
	{
		return chercheDesigner(listeJeux, designer.nom);
	}
	cout << designer.nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.

	return &designer;
}

itvoid resize(ListeJeux &liste, int nouvelleCapacite) {
	ListeJeux nouvelleListe =ListeJeux();
	if (liste.capacite != 0) {
		for (int i = 0; i < liste.capacite; i++) {
			nouvelleListe.elements[i] = liste.elements[i];
		}
	}
	liste.capacite = nouvelleCapacite;
	delete(liste.elements);
	liste = nouvelleListe;

}

void ajouterJeu(Jeu &jeu, ListeJeux &listeJeux) {
	if (listeJeux.capacite == 0) {
		listeJeux.capacite = 1;
		resize(listeJeux, 1);
	}
	else if (listeJeux.capacite == listeJeux.nElements)
		resize(listeJeux, listeJeux.capacite * 2);
	auto motoLikesYou = spanListeJeux(listeJeux);
	listeJeux.nElements += 1;
	for (Jeu* ptrJeu : motoLikesYou) {
		if (ptrJeu == nullptr)
			ptrJeu = &jeu;
	}

}



//TODO: Fonction qui enlève un jeu de ListeJeux.
// Attention, ici il n'a pas de désallocation de mémoire. Elle enlève le
// pointeur de la ListeJeux, mais le jeu pointé existe encore en mémoire.
// Puisque l'ordre de la ListeJeux n'a pas être conservé, on peut remplacer le
// jeu à être retiré par celui présent en fin de liste et décrémenter la taille
// de celle-ci.


void enleverJeu(Jeu &jeu, ListeJeux listeJeux) {
	Jeu* ptrDernierJeu = nullptr;
	auto motoLikesYou = spanListeJeux(listeJeux);
	for (Jeu* ptrJeu : motoLikesYou) {
		if (ptrJeu != &jeu or ptrJeu != nullptr)
			ptrDernierJeu = ptrJeu;
	}
	if (ptrDernierJeu == nullptr) {
		Jeu* nouvelleMaison;
		nouvelleMaison = &jeu;
		delete(&jeu);
		resize(listeJeux, listeJeux.capacite - 1);

	}
	else {
		Jeu* nouvelleMaison;
		nouvelleMaison = &jeu;
		for (Jeu* ptrJeu : motoLikesYou) {
			if (ptrJeu == &jeu)
				ptrJeu = ptrDernierJeu;
			resize(listeJeux, listeJeux.capacite - 1);
		}
	}
}

//Jeu* lireJeu(istream& fichier)
Jeu* lireJeu(istream& fichier,ListeJeux listeJeux)
{
	Jeu jeu = {}; // On initialise une structure vide de type Jeu
	jeu.titre = lireString(fichier);
	jeu.anneeSortie = lireUint16(fichier);
	jeu.developpeur = lireString(fichier);
	jeu.designers.nElements = lireUint8(fichier);
	// Rendu ici, les champs précédents de la structure jeu sont remplis avec la
	// bonne information.

	cout << jeu.titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	jeu.designers.elements = new Designer * [jeu.designers.nElements];
	for ([[maybe_unused]] int i : iter::range(jeu.designers.nElements)) {
		Designer* designer = lireDesigner(fichier,listeJeux);
		jeu.designers.elements[i] = designer;
		ajouterJeu(jeu, designer->listeJeuxParticipes);
	}
	return &jeu; //TODO: Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ListeJeux listeJeu;
	listeJeu.capacite = 0;
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	unsigned int nElements = lireUint16(fichier);
	ListeJeux listeJeux = {};
	Jeu **  mangesTesMorts = new Jeu*[nElements];
	for([[maybe_unused]] int n : iter::range(nElements))
	{
		ajouterJeu(*lireJeu(fichier,listeJeux),listeJeu); //TODO: Ajouter le jeu à la ListeJeux.
	}

	return listeJeu; //TODO: Renvoyer la ListeJeux.
}

//TODO: Fonction pour détruire un designer (libération de mémoire allouée).
// Lorsqu'on détruit un designer, on affiche son nom pour fins de débogage.
Designer::~Designer() {
	cout << nom << "\n";
	~ListeJeux(listeJeuxParticipes);
}
//TODO: Fonction qui détermine si un designer participe encore à un jeu.
bool rechercheParticipeJeu(Designer designer, Jeu jeuRecherche) {
	auto motoLikesYou = spanListeJeux(designer.listeJeuxParticipes);
	for (Jeu* ptrJeu : motoLikesYou) {
		Jeu jeuCompare = *ptrJeu;
		if (jeuCompare.titre == jeuRecherche.titre)
			return true;
	}
	return false;
}


//TODO: Fonction pour détruire un jeu (libération de mémoire allouée).
// Attention, ici il faut relâcher toute les cases mémoires occupées par un jeu.
// Par conséquent, il va falloir gérer le cas des designers (un jeu contenant
// une ListeDesigners). On doit commencer par enlever le jeu à détruire des jeux
// qu'un designer a participé (listeJeuxParticipes). Si le designer n'a plus de
// jeux présents dans sa liste de jeux participés, il faut le supprimer.  Pour
// fins de débogage, affichez le nom du jeu lors de sa destruction.
Jeu :: ~Jeu() {
//On parcours tous les designers, on enleve le jeu de tous les desginers ou le jeu se trouve. Si un desginer n'a plus de jeux on le detruit
	cout << "On detruite le jeu: " << titre << ". \n";
	span<Designer*> listeDesigners = spanListeDesigners(designers);
	for (Designer* ptrDesigner : listeDesigners) {
		Designer designer = *ptrDesigner;
		if (designer.listeJeuxParticipes.nElements == 0) {
			designer.~Designer();
		}
		else {
			auto motoLikesYou = spanListeJeux(designer.listeJeuxParticipes);
			for (Jeu* ptrJeu : motoLikesYou) {
				Jeu jeu = *ptrJeu;
				if (jeu.titre == titre) {
					delete ptrJeu;
					ptrJeu = nullptr;
				}
			}
		}

	}
	designers.~ListeDesigners();
}


//TODO: Fonction pour détruire une ListeJeux et tous ses jeux.
ListeJeux :: ~ListeJeux() {
	auto motoLikesYou = spanListeJeux(*this);
	for (Jeu* ptrJeu : motoLikesYou) {
		Jeu jeu = *ptrJeu;
		jeu.~Jeu();
		delete ptrJeu;
		ptrJeu = nullptr;
		}
	delete elements;
	elements = nullptr;
	}



void afficherDesigner(const Designer& d)
{
	cout << "\t" << d.nom << ", " << d.anneeNaissance << ", " << d.pays
			  << endl;
}

//TODO: Fonction pour afficher les infos d'un jeu ainsi que ses designers.
// Servez-vous de la fonction afficherDesigner ci-dessus.
void afficherJeu(Jeu jeu){
	cout << "Titre: " << jeu.titre
		<< "n\Annee de sortie: " << jeu.anneeSortie
		<< "n\Developpe par: " << jeu.developpeur
		<< "Voici la liste des designers: \n";
	span<Designer*> listeDesigners = spanListeDesigners(jeu.designers);
	for (Designer* ptrDesigner : listeDesigners) {
		Designer designer = *ptrDesigner;
		afficherDesigner(designer);
}

//TODO: Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
// Servez-vous de la fonction d'affichage d'un jeu crée ci-dessus. Votre ligne
// de séparation doit être différent de celle utilisée dans le main.


Developpeur :: Developpeur(std::string nom) {
	paireNomJeux_.first = nom;
	Jeu** ptrJeu;
	paireNomJeux_.second = ListeJeux {0, 0, ptrJeu};
}

Developpeur :: ~Developpeur() {
	auto uneSpanListeJeux = spanListeJeux(paireNomJeux_.second);
	for (Jeu* ptrJeu : uneSpanListeJeux) {
		delete ptrJeu;
		ptrJeu = nullptr;
	}
}

int Developpeur::compteJeux(ListeJeux listeJeux) {
	int compteJeux = 0;
	auto uneSpanListeJeux = spanListeJeux(listeJeux);
	for (Jeu* ptrJeu : uneSpanListeJeux) {
		Jeu jeu = *ptrJeu;
		if (jeu.developpeur == paireNomJeux_.first)
			compteJeux += 1;
	}
	return compteJeux;
}

std::string Developpeur::getName() {
	return paireNomJeux_.first;
}

//void Developpeur :: miseAJourListeJeux(ListeJeux listeTousLesJeux) {
//
//}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.

	creerListeJeux("jeux.bin"); //TODO: Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;
	//TODO: Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.

	cout << ligneSeparation << endl;

	//TODO: Appel à votre fonction d'affichage de votre liste de jeux.
	
	//TODO: Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.

	//TODO: Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
}
