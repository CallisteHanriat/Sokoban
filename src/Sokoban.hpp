/*
 * sokoban.hpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#ifndef SOKOBAN_HPP_
#define SOKOBAN_HPP_
#include <iostream>
#include "Etat.hpp"

class Sokoban {
public:
	int LONGMAX;
	int HAUTMAX;
	char** cadre;
	Etat etat_initial;
	Sokoban(int Longmax, int Hautmax, char** cadre);
	Sokoban& appliquer_etat(Etat& e);
	Etat creer_etat();
	void affiche();
	Sokoban() {};
	~Sokoban(){};
};

#endif /* SOKOBAN_HPP_ */
