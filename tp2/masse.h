//*******************************************************************
//*																	*
//* Programme: masse.h 				 								*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'une masse pour le réseau de masses-ressorts	*
//*                                                                 *
//*******************************************************************

#pragma once
#include "alg.h"
#include "utilalg.h"

const vecteur vecteurnul(0.0,0.0,0.0);


class masse
{	
private:
	reel m;  // la valeur de la masse. Valeur toujours positive.
	point position; 
	vecteur vitesse;
	vecteur TotalForce; // total des forces	
	bool masse_fixe; // fixée (vrai ou faux) 
public:
	masse(void);
    ~masse(void);
	void setmasse(const reel& mmasse);
	reel Getmasse();
	void setPosition(const point& newposition);
	point GetPosition();
	void setVitesse(const vecteur& newVelocity);
	vecteur GetVitesse();
	void setForce(const vecteur& newForce);
	vecteur GetForce();
	void setFixe(const bool& m_act); // Changer l'etat de fixation de la masse (vrai ou faux). l'etat par defaut est faux
	bool GetFixe();
};
