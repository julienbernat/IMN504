//*******************************************************************
//*																	*
//* Programme: masse.cpp											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'une masse pour le réseau de masse-ressorts	    *
//*                                                                 *
//*******************************************************************

#include "StdAfx.h"
#include "masse.h"
#include "glut.h"
#include <math.h>

masse::masse(void)
{ 
	m = 0.0;
	position = O; 
	vitesse = vecteurnul;
	TotalForce = vecteurnul;
	masse_fixe = false;
}


void masse::setmasse(const reel& mmasse)
{
	m = mmasse;
}
reel masse::Getmasse()
{
	return m;
}

masse::~masse(void)
{
}

void masse::setPosition(const point& newposition)
{
	position = newposition;
}

point masse::GetPosition()
{
	return position;
}

void masse::setVitesse(const vecteur& newVelocity)
{
	vitesse = newVelocity;
}

vecteur masse::GetVitesse()
{
	return vitesse;
}

void masse::setForce(const vecteur& newForce)
{
	if(masse_fixe == false)
	{
	TotalForce = newForce;
	}
}

vecteur masse::GetForce()
{
	return TotalForce;
}

void masse::setFixe(const bool& m_act) // Par défaut c'est false
{
	masse_fixe = m_act;
}

bool masse::GetFixe()
{
	return masse_fixe;
}