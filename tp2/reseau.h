//*******************************************************************
//*																	*
//* Programme: reseau.h		 										*
//*											 						*
//*******************************************************************
//*																	*
//* Description:													*
//*		Définition d'un reseau pour le réseau de masses-ressorts    *
//*                                                                 *
//*******************************************************************

#pragma once
#include "alg.h"
#include "glut.h"
#include "masse.h"
#include "ressort.h"
#include "triangle.h"


static const vecteur gravit(0.0,-9.8,0.0);
static const vecteur vent(5.0,1.0,2.5);

reel Uniforme(const reel& a, const reel& b);
vecteur generevent();

class reseau
{
private:

	int nbtriangles;  // Nombre total de triangles utilisé par le constructeur
	int nbmasses;   // Nombre total de masses utilisé par le constructeur
	int nbressort; // Nombre total de ressorts utilisé par le constructeur

	int cptmass; 
	int cptressort;
	int cpttri;

	reel ConstFricAirMasses;
	reel ConstFricAirTriangles;

	triangle *m_tri;
	ressort *m_ressort;
	masse *m_masse;
	vecteur *m_normal;

	reel deltat;
	void IntegrationEuler(); // à compléter
	void CalculForces(); // à complété
	
public:

	reseau(   const int massenumber, 
		    const int ressortnumber,
			    const int trinumber ); 
	~reseau();
	void Miseajour(const reel dt);   // Mise à jour des forces, vitesses, positions et des vecteurs normaux, à compléter

	void setConstFricAirMasses(const reel cconstFricAirMasses);     // Constante de friction entre l'air et les masses
	void setConstFricAirTriangles(const reel cconstFricAirTriangles);     // Constante de friction entre l'air et les triangles

	void AjoutMasse (const masse& cmasse);
	void AjoutRessort (const ressort& cressort); 
	void AjoutTriangle (const triangle& ctri);

	void Afficher(  const bool affichermasse, 
					const bool afficherressort,
					const bool affichertriangle,
					const bool affichernormal) ;
};