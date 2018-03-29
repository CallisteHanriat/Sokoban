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

void afficher_liste() {
	for (std::list<Etat>::iterator it = etats.begin(); it != etats.end(); it++) {
		cout << *it << endl;
	}
}

void affiche(Sokoban d) {
	printf("first line : %c\n", d.cadre[0][2]);
	for (int i = 0; i < d.HAUTMAX; i++) {
		printf("%s\n", d.cadre[i]);
	}
}

Sokoban creer_damier(FILE* f) {
	Sokoban d;
	fscanf(f, "%d,%d", &(d.LONGMAX), &(d.HAUTMAX));
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
	std::list<Etat> nouveaux_etats_possibles = Outils::etats_possibles(&etat_depart, d);

	Etat e = nouveaux_etats_possibles.front();
	cout << "etat de depart : \n" << etat_depart;
	cout << "nouvel etat possible : \n" << e;


	//afficher_liste();
	fclose(f);
	return 0;
}
