//============================================================================
// Name        : sokoban_cpp.cpp
// Author      : CallisteHANRIAT
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Outils.hpp"
using namespace std;

std::list<Etat> etats;
std::deque<Etat> etats_non_traites;

void remplir_queue(std::list<Etat>& l_etats) {
	for (std::list<Etat>::iterator it = l_etats.begin(); it != l_etats.end(); it++) {
		etats_non_traites.push_front(*it);
	}
}

void afficher_liste(std::list<Etat>& l_etats) {
	for (std::list<Etat>::iterator it = l_etats.begin(); it != l_etats.end(); it++) {
		cout << *it << endl;
	}
}

void afficher_liste() {
	for (std::list<Etat>::iterator it = etats.begin(); it != etats.end(); it++) {
		cout << *it << endl;
	}
}

void affiche(Sokoban& d) {
	printf("first line : %c\n", d.cadre[0][2]);
	for (int i = 0; i < d.HAUTMAX; i++) {
		printf("%s\n", d.cadre[i]);
	}
}

Sokoban creer_damier(FILE* f) {
	Sokoban d;
	fscanf(f, "%d,%d", &(d.HAUTMAX), &(d.LONGMAX));
	int val;
	d.cadre = (char**) malloc(sizeof(char*) * d.HAUTMAX);

	for (int i = 0; i < d.HAUTMAX; i++) {
		d.cadre[i] = (char*) malloc(sizeof(char) * d.LONGMAX);
		for (int j = 0; j < d.LONGMAX; j++) {
			if (fscanf(f, "%d,", &val) == 1) {
				d.cadre[i][j] = val + '0';
			}
		}
	}

	affiche(d);

	return d;
}

int main() {
	FILE *f;
	f = fopen("res/soko52.txt", "r");

	if (f == NULL) {
		printf("File not created okay, errno = %d\n", errno);
		return 1;
	}

	Sokoban d = creer_damier(f); // d est à la même adresse que le d retourné par creer_damier

	Etat etat_depart = Outils::creer_Etat(d);
	Etat etat2 = Outils::creer_Etat(d);
	bool test_egal = etat_depart == etat2;
	cout << "Test de l'egalite : " << test_egal << endl;
	//on met le premier état dans la liste d'états.
	etats.push_back(etat_depart);

	printf("address de l'etat de depart %p\n", etat_depart);
	std::list<Etat> nouveaux_etats_possibles = Outils::etats_possibles(etat_depart, d);

	afficher_liste(nouveaux_etats_possibles);
	Etat nouvel_etat = nouveaux_etats_possibles.front();

	nouveaux_etats_possibles = Outils::etats_possibles(nouvel_etat, d);

	cout << "nouvelle liste : " << endl;

	afficher_liste(nouveaux_etats_possibles);

	Etat etat_courant;
	//tant qu'il reste des états à traiter
	while (!etats_non_traites.empty()) {
		etat_courant = etats_non_traites.back();
		etats_non_traites.pop_back();

		nouveaux_etats_possibles = Outils::etats_possibles(etat_courant, d);
		remplir_queue(nouveaux_etats_possibles);

		cout << "sizeof queue node restant : " << etats_non_traites.size()<< endl;
	}






/*	Etat e = nouveaux_etats_possibles.front();
	cout << "etat de depart : \n" << etat_depart;
	cout << "nouvel etat possible : \n" << e;

	test_egal = e == etat_depart;
	cout << "les deux etats egaux ? " << test_egal << endl;*/


	//afficher_liste();
	fclose(f);
	return 0;
}
