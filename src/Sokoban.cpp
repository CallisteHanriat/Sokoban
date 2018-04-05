/*
 * Socoban.cpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#include "Sokoban.hpp"

void Sokoban::affiche() {
	for (int i = 0; i < this->HAUTMAX; i++) {
			printf("%s\n", this->cadre[i]);
		}
}

Sokoban::Sokoban(int Longmax, int Hautmax, char** cadre) {
	this->HAUTMAX = Hautmax;
	this->LONGMAX = Longmax;
	this->cadre = cadre;
}

Sokoban& Sokoban::appliquer_etat(Etat& e) {
	this->affiche();
	int i = 0;
	int j = 0;
	while (i < this->HAUTMAX
			&& j < this->LONGMAX
			&& this->cadre[i][j] - '0' != 2) {
		j++;
		if (j == this->LONGMAX) {
			j = 0;
			i++;
		}
	}
	this->cadre[i][j] = '0';
	/*for (int i = 0; i < this->etat_initial.DERNIERE_POSITION; i++) {
		if (this->cadre[this->etat_initial.positions[i].cordY][this->etat_initial.positions[i].cordX] - '0'
				== 2) {
			this->cadre[this->etat_initial.positions[i].cordY][this->etat_initial.positions[i].cordX] =
					'0';
		}
	}*/
	for (int i = 0; i<e.DERNIERE_POSITION ; i++) {
		this->cadre[e.positions[i].cordY][e.positions[i].cordX] = e.positions[i].valeurCase + '0';
	}

	return *this;
}

Etat Sokoban::creer_etat() {
	Etat e;
	for (int i = 0; i<this->HAUTMAX ; i++) {
		for (int j = 0; j<this->LONGMAX; j++) {
			char val = this->cadre[i][j];
			if (val == 2 || val == 1 || val == 5){
				e.positions[e.DERNIERE_POSITION].cordY = i;
				e.positions[e.DERNIERE_POSITION].cordX = j;
				e.positions[e.DERNIERE_POSITION].valeurCase = val;
				if (val == 5) {
					this->cadre[i][j] = 4;
				} else {
					this->cadre[i][j] = 0;
				}
				e.DERNIERE_POSITION++;
			}
		}
	}

	return e;
}

