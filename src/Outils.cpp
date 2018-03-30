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
	for (int i = 0; i < s.HAUTMAX ; i++) {
		for (int j = 0; j < s.LONGMAX ; j++) {
			if (s.cadre[i][j] != 8+'0' && s.cadre[i][j] != 0+'0' && s.cadre[i][j] != 4+'0') {
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
	printf("address de e %p\n", e);

	std::list<Etat> etats_temp;
	Position position_joueur;
	for (int i = 0; i<e.DERNIERE_POSITION; i++) {
		if (e.positions[i].valeurCase == 2) {
			position_joueur = e.positions[i];
		}
	}

	//si au dessus c'est une caisse vide
	cout <<"Valeur visée : " << s.cadre[position_joueur.cordX][position_joueur.cordY-1] << endl;
	Etat nouvel_etat;

	printf("valeur du dessus : %d\n", s.cadre[position_joueur.cordX][position_joueur.cordY-1] - '0');
	if (s.cadre[position_joueur.cordX][position_joueur.cordY-1]-'0' == 4 || s.cadre[position_joueur.cordX][position_joueur.cordY-1]-'0' == 0) {
		for (int i = 0; i<e.DERNIERE_POSITION; i++) {
			nouvel_etat.positions[i] = e.positions[i];
			if (e.positions[i].valeurCase == position_joueur.valeurCase) {
				nouvel_etat.positions[i].cordY = position_joueur.cordY - 1;
			}
			nouvel_etat.DERNIERE_POSITION++;
		}
	}
	etats_temp.push_back(nouvel_etat);
	return etats_temp;
}

