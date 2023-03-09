//*******************************************************************
//*																	*
//* Programme: ressort.cpp		  									*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'un ressort pour le réseau de masses-ressorts	*
//*                                                                 *
//*******************************************************************

#include "StdAfx.h"
#include "ressort.h"
#include "glut.h"
#include <math.h>


ressort::ressort(void)
{
	idmasse1 = 0;
	idmasse2 = 0;
	ConstRaideur = 0.0;
	LongueurRepos = 0.0;
}


ressort::~ressort(void)
{
}


void ressort::setidmasse1(const int &masseid)
{
	idmasse1 = masseid;
}

int ressort::Getmasse1id()
{
	return idmasse1;
}

void ressort::setidmasse2(const int &masseid)
{
	idmasse2 = masseid;
}

int ressort::Getmasse2id()
{
	return idmasse2;
}

void ressort::setconstRaideur(const reel& kra)
{
	ConstRaideur = kra;
}

reel ressort::GetconstRaideur()
{
	return ConstRaideur;
}

void ressort::setLongueurRepos(const reel &l0)
{
	LongueurRepos = l0;
}

reel ressort::GetLongueurRepos()
{
	return LongueurRepos;
}
