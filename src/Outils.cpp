/*
 * Outils.cpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */
#include "Outils.hpp"

/**
 * cette fonction génère un état grâce à un Sokoban donné.
 */
Etat Outils::creer_Etat(Sokoban& s) {
	Etat e;
	for (int i = 0; i < s.HAUTMAX; i++) {
		for (int j = 0; j < s.LONGMAX; j++) {
			if (s.cadre[i][j] != 8 + '0' && s.cadre[i][j] != 0 + '0'
					&& s.cadre[i][j] != 4 + '0') {
				Position p;
				p.cordX = j;
				p.cordY = i;
				p.valeurCase = s.cadre[i][j] - '0'; //pour convertir le char en int
				e.positions[e.DERNIERE_POSITION] = p;
				e.DERNIERE_POSITION++;
			}
		}
	}
	//printf("e address %p\n", e);
	return e;
}

/**
 *
 * @param e : etat transféré par adresse
 * Cette fonction a pour but de trouver les états possibles suivants.
 * à partir d'un état donné.
 * cases 1 : les caisses à déplacer
 * cases 2 : le joueur
 * cases 4 : les cibles ou mettre les caisses
 */
std::list<Etat> Outils::etats_possibles(Etat& e, Sokoban& s) {
	std::list<Etat> etats_temp;
	Position position_joueur;
	for (int i = 0; i < e.DERNIERE_POSITION; i++) {
		if (e.positions[i].valeurCase == 2) {
			position_joueur = e.positions[i];
		}
	}
	/*	char cordX = position_joueur.cordX;
	 position_joueur.cordX = position_joueur.cordY;
	 position_joueur.cordY = cordX;*/

	if (e.etat_sans_position_joueur() == Outils::generer_solution(s)) {
		cout << "On a un etat solution" << endl;
		return etats_temp;
	}
	//si au dessus c'est une caisse vide
	Etat nouvel_etat;

	//si la case du dessus est une cible ou une case vide ou une case à déplacer
	if (s.cadre[position_joueur.cordY - 1][position_joueur.cordX] - '0' != 8
			&& s.cadre[position_joueur.cordY - 1][position_joueur.cordX] - '0'
					!= 5) {

		cout << "char concerne : "
				<< s.cadre[position_joueur.cordY - 1][position_joueur.cordX]
				<< endl;
		//si au dessus c'est une case à déplacer et qu'il est possible de la déplacer
		if (position_joueur.cordY >= 2
				&& (s.cadre[position_joueur.cordY - 1][position_joueur.cordX]
						- '0' == 1
						|| s.cadre[position_joueur.cordY - 1][position_joueur.cordX]
								- '0' == 0)
				|| s.cadre[position_joueur.cordY - 1][position_joueur.cordX]
						- '0' == 4
						&& s.cadre[position_joueur.cordY - 2][position_joueur.cordX]
								- '0' != 8
						&& s.cadre[position_joueur.cordY - 2][position_joueur.cordX]
								- '0' != 1) {
			for (int i = 0; i < e.DERNIERE_POSITION; i++) {
				nouvel_etat.positions[i] = e.positions[i];
				nouvel_etat.DERNIERE_POSITION++;
				if (e.positions[i].valeurCase == position_joueur.valeurCase) {
					nouvel_etat.positions[i].cordY = position_joueur.cordY - 1;
				}
				if (e.positions[i].cordX == position_joueur.cordX
						&& e.positions[i].cordY == position_joueur.cordY - 1
						&& s.cadre[e.positions[i].cordY-1][e.positions[i].cordX] - '0' != 8
						&& s.cadre[e.positions[i].cordY-1][e.positions[i].cordX] - '0' != 5
						&& s.cadre[e.positions[i].cordY-1][e.positions[i].cordX] - '0' != 1) {
					nouvel_etat.positions[i].cordY =
							nouvel_etat.positions[i].cordY - 1;
					if (s.cadre[position_joueur.cordX][position_joueur.cordY - 2]
							- '0' == 4)
						nouvel_etat.positions[i].valeurCase = 5;
				}
			}
			etats_temp.push_back(nouvel_etat);
			nouvel_etat.DERNIERE_POSITION = 0;
		}
	}

	if (s.cadre[position_joueur.cordY][position_joueur.cordX + 1] - '0' != 8
			&& s.cadre[position_joueur.cordY][position_joueur.cordX + 1] - '0'
					!= 5) {

		//si au dessus c'est une case à déplacer et qu'il est possible de la déplacer
		cout << "char concerne : "
				<< s.cadre[position_joueur.cordX][position_joueur.cordY]
				<< endl;

		if (position_joueur.cordX <= s.LONGMAX - 2
				&& s.cadre[position_joueur.cordY][position_joueur.cordX + 1]
						- '0' == 1
				|| s.cadre[position_joueur.cordY][position_joueur.cordX + 1]
						- '0' == 0
				|| s.cadre[position_joueur.cordY][position_joueur.cordX + 1]
						- '0' == 4
						&& s.cadre[position_joueur.cordY][position_joueur.cordX
								+ 2] - '0' != 8
						&& s.cadre[position_joueur.cordY][position_joueur.cordX
								+ 2] - '0' != 1) {
			for (int i = 0; i < e.DERNIERE_POSITION; i++) {
				nouvel_etat.positions[i] = e.positions[i];
				nouvel_etat.DERNIERE_POSITION++;
				if (e.positions[i].valeurCase == position_joueur.valeurCase) {
					nouvel_etat.positions[i].cordX = position_joueur.cordX + 1;
				}
				cout << "s.cadre[position_joueur.cordX + 2][position_joueur.cordY] : " << s.cadre[position_joueur.cordY][position_joueur.cordX+2] << endl;
				if (e.positions[i].cordY == position_joueur.cordY
						&& e.positions[i].cordX == position_joueur.cordX + 1
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX + 1] - '0'!= 8
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX + 1] - '0'!= 5
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX + 1] - '0'!= 1) {
					if (e.positions[i].valeurCase == 1)
						nouvel_etat.positions[i].cordX = nouvel_etat.positions[i].cordX + 1;
					if (s.cadre[position_joueur.cordY][position_joueur.cordX+2]
							- '0' == 4)
						nouvel_etat.positions[i].valeurCase = 5;
				}
			}
			etats_temp.push_back(nouvel_etat);
			nouvel_etat.DERNIERE_POSITION = 0;
		}


	}

	if (s.cadre[position_joueur.cordY+1][position_joueur.cordX] - '0' != 8
			&& s.cadre[position_joueur.cordY+1][position_joueur.cordX] - '0'
					!= 5) {

		//si au dessus c'est une case à déplacer et qu'il est possible de la déplacer
		if (position_joueur.cordY <= s.HAUTMAX - 2
				&& s.cadre[position_joueur.cordY + 1][position_joueur.cordX]
						- '0' == 1
				|| s.cadre[position_joueur.cordY + 1][position_joueur.cordX]
						- '0' == 0
				|| s.cadre[position_joueur.cordY + 1][position_joueur.cordX]
						- '0' == 4
						&& s.cadre[position_joueur.cordY + 2][position_joueur.cordX]
								- '0' != 8
						&& s.cadre[position_joueur.cordY + 2][position_joueur.cordX]
								- '0' != 1) {
			for (int i = 0; i < e.DERNIERE_POSITION; i++) {
				nouvel_etat.positions[i] = e.positions[i];
				nouvel_etat.DERNIERE_POSITION++;
				if (e.positions[i].valeurCase == position_joueur.valeurCase) {
					nouvel_etat.positions[i].cordY = position_joueur.cordY + 1;
				}
				if (e.positions[i].cordX == position_joueur.cordX
						&& e.positions[i].cordY == position_joueur.cordY + 1
						&& s.cadre[e.positions[i].cordY+1][e.positions[i].cordX] - '0' != 8
						&& s.cadre[e.positions[i].cordY+1][e.positions[i].cordX] - '0' != 5
						&& s.cadre[e.positions[i].cordY+1][e.positions[i].cordX] - '0' != 1) {
					if (e.positions[i].valeurCase == 1)
						nouvel_etat.positions[i].cordY = nouvel_etat.positions[i].cordY + 1;
					if (s.cadre[position_joueur.cordX][position_joueur.cordY + 2]
							- '0' == 4)
						nouvel_etat.positions[i].valeurCase = 5;
				}
			}
			etats_temp.push_back(nouvel_etat);
			nouvel_etat.DERNIERE_POSITION = 0;
		}


	}

	if (s.cadre[position_joueur.cordY][position_joueur.cordX-1] - '0' != 8
			&& s.cadre[position_joueur.cordY][position_joueur.cordX-1] - '0'
					!= 5) {

		//si au dessus c'est une case à déplacer et qu'il est possible de la déplacer
		if (position_joueur.cordX <= 2
				&& s.cadre[position_joueur.cordY][position_joueur.cordX - 1]
						- '0' == 1
				|| s.cadre[position_joueur.cordY][position_joueur.cordX - 1]
						- '0' == 1
				|| s.cadre[position_joueur.cordY][position_joueur.cordX - 1]
						- '0' == 4
						&& s.cadre[position_joueur.cordY][position_joueur.cordX
								- 2] - '0' != 8
						&& s.cadre[position_joueur.cordY][position_joueur.cordX
								- 2] - '0' != 1) {
			for (int i = 0; i < e.DERNIERE_POSITION; i++) {
				nouvel_etat.positions[i] = e.positions[i];
				nouvel_etat.DERNIERE_POSITION++;
				if (e.positions[i].valeurCase == position_joueur.valeurCase) {
					nouvel_etat.positions[i].cordX = position_joueur.cordX - 1;
				}
				if (e.positions[i].cordY == position_joueur.cordY
						&& e.positions[i].cordX == position_joueur.cordX - 1
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX-1] - '0' != 8
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX-1] - '0' != 5
						&& s.cadre[e.positions[i].cordY][e.positions[i].cordX-1] - '0' != 1) {
					if (e.positions[i].valeurCase == 1)
						nouvel_etat.positions[i].cordX = nouvel_etat.positions[i].cordX - 1;
					if (s.cadre[position_joueur.cordX - 2][position_joueur.cordY]
							- '0' == 4)
						nouvel_etat.positions[i].valeurCase = 5;
				}
			}
			etats_temp.push_back(nouvel_etat);
			nouvel_etat.DERNIERE_POSITION = 0;
		}


	}

	return etats_temp;
}

Sokoban Outils::creer_damier(FILE* f) {
	Sokoban d;
	fscanf(f, "%d,%d", &(d.LONGMAX), &(d.HAUTMAX));
	int val;
	d.cadre = (char**) malloc(sizeof(char*) * d.LONGMAX);

	for (int i = 0; i < d.LONGMAX; i++) {
		d.cadre[i] = (char*) malloc(sizeof(char) * d.HAUTMAX);
		for (int j = 0; j < d.HAUTMAX; j++) {
			if (fscanf(f, "%d,", &val) == 1) {
				d.cadre[i][j] = val + '0';
			}
		}
	}

	return d;
}

/**
 * Cette fonction a pour but de générer l'Etat solution à partir d'un Sokoban donné.
 */
Etat Outils::generer_solution(Sokoban& s) {
	Etat e;
	for (int i = 0; i < s.HAUTMAX; i++) {
		for (int j = 0; j < s.LONGMAX; j++) {
			//si on trouve la case 4
			if (s.cadre[i][j] == 4 + '0') {
				Position p;
				p.cordX = j;
				p.cordY = i;
				p.valeurCase = 5; //pour convertir le char en int
				e.positions[e.DERNIERE_POSITION] = p;
				e.DERNIERE_POSITION++;
			}
		}
	}
	return e;
}

