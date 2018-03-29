/*
 * Etat.cpp
 *
 *  Created on: 27 mars 2018
 *      Author: calliste
 */

#include "Etat.hpp"

void Etat::afficher(ostream& flux) const {
	for (int i = 0; i < this->DERNIERE_POSITION; i++) {
		printf("%d,%d : type %d\n", this->positions[i].cordX, this->positions[i].cordY, this->positions[i].valeurCase);
	}
}

ostream& operator<<(ostream& os, const Etat& state) {
	state.afficher(os);
	return os;
}

/**
 * Cette fonction vérifie l'égalité entre deux états
 */
bool operator==(Etat const& a, Etat const& b) {
	bool return_val = false;
	int j = 0;
	for (int i = 0 ; i < a.DERNIERE_POSITION ; i++) {

		Position p = a.positions[i];

		while (a.positions[i].cordX != b.positions[j].cordX
				&& a.positions[i].cordY != b.positions[j].cordY
				&& a.positions[i].valeurCase != b.positions[j].valeurCase
				&& j<b.DERNIERE_POSITION) {
			j++;
		}
		if (j < b.DERNIERE_POSITION) {
			return_val = true;
		} else {
			return_val = false;
		}

		j = 0;
	}

	return return_val;
}
