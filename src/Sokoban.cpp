/*
 * Socoban.cpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#include "Sokoban.hpp"
#include "string.h"
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

void Sokoban::test(Sokoban& s) {
	this->cadre[0][0] = '7';
}

void Sokoban::appliquer_etat(Etat& e,  Sokoban& s_init) {
	this->affiche();
	Sokoban s_temp;
	int i = 0;
	int j = 0;
	this->cadre = (char**)malloc (sizeof(char*)*this->HAUTMAX);
	for (int i = 0; i< this->HAUTMAX ; i++) {
		this->cadre[i] = (char*) malloc(sizeof(char)*(this->LONGMAX+1));
		strcpy(this->cadre[i], s_init.cadre[i]);
	}
	cout << "etat du s_init : " << endl;
	cout << s_init.etat_initial << endl;
	while (i < s_init.etat_initial.DERNIERE_POSITION &&
			s_init.etat_initial.positions[i].valeurCase != '2') {
		i++;
	}

	Position p = s_init.etat_initial.positions[i];
	this->cadre[p.cordY][p.cordX] = '0';


	cout << "addr cadre this : " << &this->cadre << endl;
	cout << "addr cadre s_init : " << &(s_init.cadre) << endl;

	cout << "deuxieme affichage" << endl;
	for (int i = 0; i<e.DERNIERE_POSITION ; i++) {
		this->cadre[e.positions[i].cordY][e.positions[i].cordX] = e.positions[i].valeurCase + '0';
	}
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

