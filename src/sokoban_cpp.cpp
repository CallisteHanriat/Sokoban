//============================================================================
// Name        : sokoban_cpp.cpp
// Author      : CallisteHANRIAT
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "algorithm"
#include "Outils.hpp"
using namespace std;

std::list<Etat> etats;
std::deque<Etat> etats_non_traites;

void afficher_liste();


bool est_dans_la_liste(Etat& e) {
	std::list<Etat>::iterator state = etats.begin();


	//cout << "affichage de la liste " << endl;
	//afficher_liste();
	while(state != etats.end()) {
		//cout << "comparaison : \n" << e <<endl;
		//cout << *state << endl;
		if (e==*state || e.etat_sans_position_joueur() == *state
				|| e==(*state).etat_sans_position_joueur()) {
			cout << "return true" << endl;
			return true;
		}
		state++;
	}
	cout << e << endl << "Pas dans la liste" << endl;
	return false;
}

void remplir_queue(std::list<Etat>& l_etats) {
	Etat e_courant;
	std::list<Etat>::iterator iterator_deque;

	for (std::list<Etat>::iterator it = l_etats.begin(); it != l_etats.end(); it++) {
		e_courant = *it;

		//Si l'element est deja dans la queue
		if (!est_dans_la_liste(e_courant)) {
			etats_non_traites.push_back(*it);
		}
		//cout << "ajout de \n" << *it << endl;
	}
}

void afficher_liste(std::list<Etat>& l_etats) {
	Etat e;
	for (std::list<Etat>::iterator it = l_etats.begin(); it != l_etats.end(); it++) {
		e = *it;
		cout <<"un etat : " << endl<<  e << endl;
	}
}

void afficher_liste() {
	for (std::list<Etat>::iterator it = etats.begin(); it != etats.end(); it++) {
		cout << *it << endl;
	}
}



int main() {
	FILE *f;
	f = fopen("res/soko11.txt", "r");

	if (f == NULL) {
		printf("File not created okay, errno = %d\n", errno);
		return 1;
	}

	Sokoban sokoban_intial = Outils::creer_damier(f);
	Sokoban sokoban_courant = sokoban_intial;
	sokoban_intial.etat_initial = Outils::creer_Etat(sokoban_intial);
	sokoban_courant.affiche();

	Etat etat_depart = Outils::creer_Etat(sokoban_intial);

	//on met le premier état dans la liste d'états.
	cout <<"etat de depart \n"<< etat_depart << endl;
	Etat eSol = Outils::generer_solution(sokoban_intial);
	sokoban_courant.appliquer_etat(etat_depart, sokoban_intial);
	std::list<Etat> nouveaux_etats_possibles = Outils::etats_possibles(etat_depart, sokoban_courant , eSol);

	cout << "sokoban init : " << endl;
	sokoban_intial.affiche();
	Etat etat_courant;


/*	cout << eSol;
	Etat etat_main;
	Position p;
	p.cordX = 3; p.cordY = 1; p.valeurCase = 5;
	etat_main.positions[0] = p;
	p.cordX = 5; p.cordY = 3; p.valeurCase = 5;
	etat_main.positions[1] = p;
	p.cordX = 1; p.cordY = 4; p.valeurCase = 5;
	etat_main.positions[2] = p;
	p.cordX = 1; p.cordY = 5; p.valeurCase = 2;
	etat_main.positions[3] = p;
	etat_main.DERNIERE_POSITION = 4;

	cout << "etat_main\n" << etat_main << endl;
	if (etat_main.etat_sans_position_joueur() == eSol) {
		cout << "true";
	}*/

	etats_non_traites.push_back(etat_depart);

	int cpt = 0;
	//tant qu'il reste des états à traiter
	while (!etats_non_traites.empty() && !(etat_courant.etat_sans_position_joueur() == eSol)) {
		//on dépile le noeud le plus haut puis
		etat_courant = etats_non_traites.back();
		etats_non_traites.pop_back();

		cout << "----------Nouvelle iteration "<< cpt << "-------------" << endl;
		cout << "taille etats_non_traites : " << etats_non_traites.size() << endl;
		cout << "etat coutant \n" << etat_courant << endl;
		//on fabrique de nouveaux fils que nous mettons dans la queue
		if (cpt == 3707) {
			cout << "debug" << endl;
		}
		sokoban_courant.appliquer_etat(etat_courant, sokoban_intial);
		nouveaux_etats_possibles = Outils::etats_possibles(etat_courant, sokoban_courant, eSol);
		//afficher_liste(nouveaux_etats_possibles);
		remplir_queue(nouveaux_etats_possibles);


		etats.push_back(etat_courant);
		cout << "sizeof queue node restant : " << etats_non_traites.size()<< endl;
		cout << "que node restants vide ? " << etats_non_traites.empty()<<endl;
		cpt++;
	}

	cout << "liste des etats : " << endl;
//	afficher_liste(etats);

	cout << "nombre de noeuds : " << etats.size() << endl;

/*	Etat e = nouveaux_etats_possibles.front();
	cout << "etat de depart : \n" << etat_depart;
	cout << "nouvel etat possible : \n" << e;

	test_egal = e == etat_depart;
	cout << "les deux etats egaux ? " << test_egal << endl;*/


	//afficher_liste();
	fclose(f);
	return 0;
}
