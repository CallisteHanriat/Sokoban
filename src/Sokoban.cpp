/*
 * Socoban.cpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#include "Sokoban.hpp"


Sokoban::Sokoban(int Longmax, int Hautmax, char** cadre) {
	this->HAUTMAX = Hautmax;
	this->LONGMAX = Longmax;
	this->cadre = cadre;
}


