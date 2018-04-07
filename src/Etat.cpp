/*
 * Etat.cpp
 *
 *  Created on: 27 mars 2018
 *      Author: calliste
 */

#include "Etat.hpp"

void Etat::afficher(ostream& flux) const {
	int cp=0;
	for (int i = 0; i < this->DERNIERE_POSITION; i++) {
		if (this->positions[i].valeurCase == 5)
			cp++;
		flux << +this->positions[i].cordY << ',' << +this->positions[i].cordX << " : type " << +this->positions[i].valeurCase << endl;
	}
	flux << "Nombre de 5 : " << cp << endl;
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

	if (a.DERNIERE_POSITION != b.DERNIERE_POSITION) {
		return false;
	}

	for (int i = 0 ; i < a.DERNIERE_POSITION ; i++) {

		Position p = a.positions[i];

		while ((a.positions[i].cordX != b.positions[j].cordX
				|| a.positions[i].cordY != b.positions[j].cordY
				|| a.positions[i].valeurCase != b.positions[j].valeurCase)
				&& j<b.DERNIERE_POSITION) {
			j++;
		}
		if (j == b.DERNIERE_POSITION) {
			return false;
		} else {
			return_val = true;
		}

		j = 0;
	}

	return return_val;
}

Etat Etat::etat_sans_position_joueur() {
	Etat e;
	for (int i = 0; i < this->DERNIERE_POSITION ; i++) {
		if (this->positions[i].valeurCase!=2) {
			Position p;
			p.cordX = this->positions[i].cordX; p.cordY = this->positions[i].cordY; p.valeurCase = this->positions[i].valeurCase;

			e.positions[e.DERNIERE_POSITION] = p;
			e.DERNIERE_POSITION++;
		}
	}

	return e;
}
