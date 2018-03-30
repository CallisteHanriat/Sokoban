/*
 * Source.hpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#ifndef OUTILS_HPP_
#define OUTILS_HPP_
#include "Sokoban.hpp"
class Outils{
public:
	static Etat creer_Etat(Sokoban& s);
	static std::list<Etat> etats_possibles(Etat& e, Sokoban& s);
};

#endif /* OUTILS_HPP_ */
