/*
 * etat.hpp
 *
 *  Created on: 26 mars 2018
 *      Author: calliste
 */

#ifndef ETAT_HPP_
#define ETAT_HPP_

#include <iostream>
#include <list>
#include <queue>
using namespace std;

class Position{
public:
	unsigned char cordX, cordY, valeurCase;
	Position(){};
	~Position(){};
};

class Etat {
public:
	Position positions[8];
	char DERNIERE_POSITION = 0;
	void afficher(ostream& flux) const;
	Etat(){};
	~Etat(){};

	friend ostream& operator<<(ostream& os, const Etat& state);
	friend bool operator==(Etat const& a, Etat const& b);
};

#endif /* ETAT_HPP_ */
