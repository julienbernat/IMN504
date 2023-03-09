//*******************************************************************
//*																	*
//* Programme: triangle.cpp		 									*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'un triangle pour le réseau de masses-ressorts	*
//*                                                                 *
//*******************************************************************

#include "StdAfx.h"
#include "triangle.h"
#include "masse.h"

triangle::triangle(void)
{
	masse1id = 0;
	masse2id = 0;
	masse3id = 0;
}

triangle::~triangle(void)
{
}

void triangle::setmasse1id(const int &id1)
{
	masse1id = id1;
}

int triangle::Getmasse1id()
{
	return masse1id;
}

void triangle::setmasse2id(const int &id2)
{
	masse2id = id2;
}

int triangle::Getmasse2id()
{
	return masse2id;
}


void triangle::setmasse3id(const int &id3)
{
	masse3id = id3;
}

int triangle::Getmasse3id()
{
	return masse3id;
}
