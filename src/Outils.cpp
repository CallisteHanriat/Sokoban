/*
 * Outils.cpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */
#include "Outils.hpp"


/**
 *
 */
bool Outils::mouvement_possible_haut(Position& origine, Position& direction, Sokoban& s) {

	if ((direction.cordX < 0 || direction.cordY < 0)
			|| (direction.cordY > s.HAUTMAX || direction.cordX > s.LONGMAX)) {
		return false;
	}

	char valeurCaseDirection = s.cadre[direction.cordY][direction.cordX]-'0';

	if (valeurCaseDirection == 8) {
		return false;
	} else if (valeurCaseDirection == 5 && direction.cordY -1 < 0){
		return false;
	} else if((valeurCaseDirection == 5 || valeurCaseDirection == 1)
			&& s.cadre[direction.cordY-1][direction.cordX]-'0' != 1
			&& s.cadre[direction.cordY-1][direction.cordX]-'0' != 4
			&& s.cadre[direction.cordY-1][direction.cordX]-'0' != 0
			&& direction.cordY - 1 >= 0) {
		return false;
	} else if (valeurCaseDirection == 5) {
		return false;
	}else if (valeurCaseDirection == 1
			&& s.cadre[direction.cordY-1][direction.cordX]-'0' == 1) {
		return false;
	}
	return true;
}


bool Outils::mouvement_possible_droit(Position& origine, Position& direction, Sokoban& s) {

	if ((direction.cordX < 0 || direction.cordY < 0)
			|| (direction.cordY > s.HAUTMAX || direction.cordX > s.LONGMAX)) {
		return false;
	}

	char valeurCaseDirection = s.cadre[direction.cordY][direction.cordX]-'0';

	if (valeurCaseDirection == 8) {
		return false;
	} else if (direction.cordX + 1 >= s.LONGMAX) {
		return false;
	}else if((valeurCaseDirection == 5 || valeurCaseDirection == 1)
			&& s.cadre[direction.cordY][direction.cordX+1]-'0' != 1
			&& s.cadre[direction.cordY][direction.cordX+1]-'0' != 4
			&& s.cadre[direction.cordY][direction.cordX+1]-'0' != 0) {
		return false;
	} else if (valeurCaseDirection == 5) {
		return false;
	} else if (valeurCaseDirection == 1
			&& s.cadre[direction.cordY][direction.cordX+1]-'0' == 1) {
		return false;
	}
	return true;
}

bool Outils::mouvement_possible_bas(Position& origine, Position& direction, Sokoban& s) {
	if ((direction.cordX < 0 || direction.cordY < 0)
			|| (direction.cordY > s.HAUTMAX || direction.cordX > s.LONGMAX)) {
		return false;
	}

	char valeurCaseDirection = s.cadre[direction.cordY][direction.cordX]-'0';

	if (valeurCaseDirection == 8) {
		return false;
	} else if((valeurCaseDirection == 5 || valeurCaseDirection == 1)
			&& s.cadre[direction.cordY+1][direction.cordX]-'0' != 1
			&& s.cadre[direction.cordY+1][direction.cordX]-'0' != 4
			&& s.cadre[direction.cordY+1][direction.cordX]-'0' != 0) {
		return false;
	} else if (valeurCaseDirection == 5) {
		return false;
	}else if (valeurCaseDirection == 1
			&& s.cadre[direction.cordY+1][direction.cordX]-'0' == 1) {
		return false;
	}
	return true;
}

bool Outils::mouvement_possible_gauche(Position& origine, Position& direction, Sokoban& s) {
	if ((direction.cordX < 0 || direction.cordY < 0)
			|| (direction.cordY > s.HAUTMAX || direction.cordX > s.LONGMAX)) {
		return false;
	}

	char valeurCaseDirection = s.cadre[direction.cordY][direction.cordX]-'0';

	if (valeurCaseDirection == 8) {
		return false;
	} else if((valeurCaseDirection == 5 || valeurCaseDirection == 1)
			&& s.cadre[direction.cordY][direction.cordX-1]-'0' != 1
			&& s.cadre[direction.cordY][direction.cordX-1]-'0' != 4
			&& s.cadre[direction.cordY][direction.cordX-1]-'0' != 0
			&& direction.cordX -1 >= 0) {
		return false;
	} else if (valeurCaseDirection == 5) {
		return false;
	}else if (valeurCaseDirection == 1
			&& s.cadre[direction.cordY][direction.cordX-1]-'0' == 1) {
		return false;
	}
	return true;
}

/**
 * cette fonction génère un état grâce à un Sokoban donné.
 */
Etat Outils::creer_Etat(Sokoban& s) {
	Etat e;
	for (int i = 0; i < s.HAUTMAX; i++) {
		for (int j = 0; j < s.LONGMAX; j++) {
			cout << "lettre à analyser : " << s.cadre[i][j] << endl;
			if (s.cadre[i][j] != 8 + '0'
					&& s.cadre[i][j] != 0 + '0'
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
	//e.DERNIERE_POSITION;
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
std::list<Etat> Outils::etats_possibles(Etat& e, Sokoban& s, Etat& eSol) {
	std::list<Etat> etats_temp;
	Position position_joueur;
	for (int i = 0; i < e.DERNIERE_POSITION; i++) {
		if (e.positions[i].valeurCase == 2) {
			position_joueur = e.positions[i];
		}
	}

	if (e.etat_sans_position_joueur() == eSol) {
		cout << "On a un etat solution" << endl;
		return etats_temp;
	}

	//si au dessus c'est une caisse vide
	Etat nouvel_etat;

	cout << "Sokoban interprete : " << endl;
	s.affiche();
	//si la case du dessus est une cible ou une case vide ou une case à déplacer
	Position cible;
	cible.cordX = position_joueur.cordX;
	cible.cordY = position_joueur.cordY - 1;
	cible.valeurCase = position_joueur.valeurCase;
	if (Outils::mouvement_possible_haut(position_joueur, cible, s)) {
		for (int i = 0; i<e.DERNIERE_POSITION; i++) {
			nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION] = e.positions[i];
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase == position_joueur.valeurCase) {
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY = nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY -1;
			}
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX == position_joueur.cordX &&
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY == position_joueur.cordY - 1 &&
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase == 1 &&
					position_joueur.cordY > 2) {
				if (s.cadre[position_joueur.cordY - 2][position_joueur.cordX] -'0' == 4){
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase = 5;
				}
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY = nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY - 1;
			}
			nouvel_etat.DERNIERE_POSITION++;
		}

		etats_temp.push_back(nouvel_etat);
		nouvel_etat.DERNIERE_POSITION = 0;
	}

	cible.cordY = position_joueur.cordY;
	cible.cordX = position_joueur.cordX + 1;
	if (Outils::mouvement_possible_droit(position_joueur, cible, s)) {

		for (int i = 0; i < e.DERNIERE_POSITION; i++) {
			nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION] =
					e.positions[i];
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
					== position_joueur.valeurCase) {
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX + 1;
			}
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX
					== position_joueur.cordX + 1
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY
							== position_joueur.cordY
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
							== 1 && position_joueur.cordX < s.LONGMAX-2) {
				if (s.cadre[position_joueur.cordY][position_joueur.cordX+2]
						- '0' == 4) {
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase =
							5;
				}
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX + 1;
			}
			nouvel_etat.DERNIERE_POSITION++;
		}

		etats_temp.push_back(nouvel_etat);
		nouvel_etat.DERNIERE_POSITION = 0;
	}


	cible.cordY = position_joueur.cordY+1;
	cible.cordX = position_joueur.cordX;
	if (Outils::mouvement_possible_bas(position_joueur, cible, s)) {

		for (int i = 0; i < e.DERNIERE_POSITION; i++) {
			nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION] =
					e.positions[i];
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
					== position_joueur.valeurCase) {
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY
								+ 1;
			}
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX
					== position_joueur.cordX
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY
							== position_joueur.cordY + 1
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
							== 1 && position_joueur.cordY < s.HAUTMAX - 2) {
				if (s.cadre[position_joueur.cordY + 2][position_joueur.cordX]
						- '0' == 4) {
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase =
							5;
				}
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY
								+ 1;
			}
			nouvel_etat.DERNIERE_POSITION++;
		}

		etats_temp.push_back(nouvel_etat);
		nouvel_etat.DERNIERE_POSITION = 0;
	}

	cible.cordX = position_joueur.cordX-1;
	cible.cordY = position_joueur.cordY;
	if (Outils::mouvement_possible_gauche(position_joueur, cible, s)) {

		for (int i = 0; i < e.DERNIERE_POSITION; i++) {
			nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION] =
					e.positions[i];
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
					== position_joueur.valeurCase) {
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX
								- 1;
			}
			if (nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX
					== position_joueur.cordX -1
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordY
							== position_joueur.cordY
					&& nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase
							== 1 && position_joueur.cordX > 2) {
				if (s.cadre[position_joueur.cordY][position_joueur.cordX-2]
						- '0' == 4) {
					nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].valeurCase =
							5;
				}
				nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX =
						nouvel_etat.positions[nouvel_etat.DERNIERE_POSITION].cordX
								- 1;
			}
			nouvel_etat.DERNIERE_POSITION++;
		}

		etats_temp.push_back(nouvel_etat);
		nouvel_etat.DERNIERE_POSITION = 0;
	}

	return etats_temp;
}

Sokoban Outils::creer_damier(FILE* f) {
	Sokoban d;
	fscanf(f, "%d,%d", &(d.HAUTMAX), &(d.LONGMAX));
	int val;
	d.cadre = (char**) malloc(sizeof(char*) * d.HAUTMAX);

	for (int i = 0; i < d.HAUTMAX; i++) {
		d.cadre[i] = (char*) malloc(sizeof(char) * d.LONGMAX+1);
		for (int j = 0; j < d.LONGMAX; j++) {
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
	char valCase;
	for (int i = 0; i < s.HAUTMAX; i++) {
		for (int j = 0; j < s.LONGMAX; j++) {
			//si on trouve la case 4
			valCase = s.cadre[i][j]-'0';
			if (valCase == 4) {
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

