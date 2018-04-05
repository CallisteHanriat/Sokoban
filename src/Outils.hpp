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
	static std::list<Etat> etats_possibles(Etat& e, Sokoban& s, Etat& eSol);
	static Etat generer_solution(Sokoban& s);
	static Sokoban creer_damier(FILE* f);
	static bool mouvement_possible_haut(Position& p1, Position& p2, Sokoban& s);
	static bool mouvement_possible_droit(Position& p1, Position& p2, Sokoban& s);
	static bool mouvement_possible_bas(Position& p1, Position& p2, Sokoban& s);
	static bool mouvement_possible_gauche(Position& p1, Position& p2, Sokoban& s);
};

#endif /* OUTILS_HPP_ */
