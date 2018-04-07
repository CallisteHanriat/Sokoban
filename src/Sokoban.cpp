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
	Sokoban s_tmp;
	//this->affiche();
	s_tmp.HAUTMAX = this->HAUTMAX;
	s_tmp.LONGMAX = this->LONGMAX;
	s_tmp.cadre = (char**)malloc (sizeof(char*)*this->HAUTMAX);
	for (int i = 0; i< this->HAUTMAX ; i++) {
		s_tmp.cadre[i] = (char*) malloc(sizeof(char)*(this->LONGMAX+1));
		for (int j = 0 ; j < this->LONGMAX ; j++) {
			char val = this->cadre[i][j];
			if (val != '2')
				s_tmp.cadre[i][j] = val;
			else
				s_tmp.cadre[i][j] = '0';
		}
	}
	//On récupère les coordonnées du joueur de l'état courant :
/*	cout << "premier affichage" << endl;
	s_tmp.affiche();*/
	int hautJoueurCourant=0;
	int lonJoueurCourant=0;
	bool trouve = false;
	while (hautJoueurCourant < this->HAUTMAX && !trouve) {
		while (lonJoueurCourant < this->LONGMAX && this->cadre[hautJoueurCourant][lonJoueurCourant] - '0'!= 2) {
			lonJoueurCourant++;
		}
		if(lonJoueurCourant < this->LONGMAX)
			trouve = true;

		if (!trouve){
			lonJoueurCourant = 0;
			hautJoueurCourant++;
		}
	}
	char vaCaseInitPosiJActu = s_init.cadre[hautJoueurCourant][lonJoueurCourant] - '0';
	Position posCaseInitJoueurCourant(lonJoueurCourant, hautJoueurCourant, vaCaseInitPosiJActu);

	if (posCaseInitJoueurCourant.valeurCase == 2) {
		s_tmp.cadre[posCaseInitJoueurCourant.cordY][posCaseInitJoueurCourant.cordX] = '0';
	} else if (posCaseInitJoueurCourant.valeurCase == 4) {
		s_tmp.cadre[posCaseInitJoueurCourant.cordY][posCaseInitJoueurCourant.cordX] = '4';
	}

/*	cout << "deuxieme affichage : " << endl;
	s_tmp.affiche();*/
	for (int i = 0; i<e.DERNIERE_POSITION ; i++) {
		s_tmp.cadre[e.positions[i].cordY][e.positions[i].cordX] = e.positions[i].valeurCase + '0';
	}

	bool bon1Trouve = false;
	bool bon5Trouve = false;
	char vCase;
	int p;
	//tous les endroits où il y a un 1 dans le tmp, si c'est pas un 1 de l'état alors on lui met 0
	for (int i = 0; i<s_tmp.HAUTMAX; i++) {
		for (int j = 0 ; j<s_tmp.LONGMAX; j++) {
			vCase = s_tmp.cadre[i][j];
			p = 0;
			bon1Trouve = false;
			if (vCase == '1') {
				while (p<e.DERNIERE_POSITION && !bon1Trouve) {
					if (e.positions[p].cordX == j && e.positions[p].cordY == i)
						bon1Trouve = true;
					p++;
				}
				if (!bon1Trouve)
					s_tmp.cadre[i][j] = '0';
			}else if (vCase == '5') {
				p = 0;
				while (p<e.DERNIERE_POSITION && !bon5Trouve) {
					if(e.positions[p].cordX == j && e.positions[p].cordY == i)
						bon5Trouve = true;
					p++;
				}
				if (!bon5Trouve)
					s_tmp.cadre[i][j] = '4';
			}
		}
	}
/*	cout << "troisieme affichage" << endl;
	s_tmp.affiche();*/
	this->cadre = s_tmp.cadre;
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

