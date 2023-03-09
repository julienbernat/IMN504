//*******************************************************************
//*																	*
//* Programme: triangle.h 											*
//*																	*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'un triangle pour le réseau de masses-ressorts	*
//*                                                                 *
//*******************************************************************

#pragma once

#include "alg.h"
#include "utilalg.h"

class triangle
{
private:
	int masse1id; // index 1er point du triangle
	int masse2id; // index 2eme point du triangle
	int masse3id; // index 3eme point du triangle
	
public:
	triangle(void);
	~triangle(void);
	void    setmasse1id(const int &id1);
	int     Getmasse1id();
	void    setmasse2id(const int &id2);
	int     Getmasse2id();
	void    setmasse3id(const int &id3);
	int     Getmasse3id();
};
