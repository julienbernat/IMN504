//*******************************************************************
//*																	*
//* Programme: main.cpp		  										*
//*																	*
//*******************************************************************
//*																	*
//* Simulation d'un drapeau											*
//*																	*
//*******************************************************************

#include "stdafx.h"
#include "reseau.h"


const reel deltat = 0.005; // pas de temps

const reel mas = 0.3; // masse des masses

const reel Kas = 2000.0; // Pour les ressorts primaires qui forment des carrés
const reel Kac = 1.0; // Pour les ressorts secondaires
const reel Kad = 1.0; // Pour les ressorts diagonaux

const reel ConstFrictionAirMasses = 0.01;  // constante de friction des masses avec l'air
const reel ConstFrictionAirTriangles = 5.5; // constante de friction des triangles avec l'air






// *******      CHRIS     ****************
// commenté pour tester avec 2 masses dont une fixe et une  non fixe
//const int nbmasseLargeur = 10;  // nbre de masses en Largeur du drapeau 
//const int nbmasseHauteur = 8;  // nbre de masses en Hauteur du drapeau 
const int nbmasseLargeur = 1;  // nbre de masses en Largeur du drapeau 
const int nbmasseHauteur = 2; // nbre de masses en Hauteur du drapeau 










const point CoinHautGauche((nbmasseHauteur/2.0)-1.0,(nbmasseLargeur/2.0)-5.0,0.0); 

//nbre total de masses
int nbtotalMass = nbmasseLargeur*nbmasseHauteur;



// *******      CHRIS     ****************
// commenté pour tester avec 1 ressort entre 2 masses
//nbre total de ressorts générés
//int nbtotalRessort = (nbmasseHauteur-1)*nbmasseLargeur  
//                   + (nbmasseHauteur*(nbmasseLargeur-1))
//				   + (nbmasseHauteur-2)*nbmasseLargeur  
//                   + (nbmasseHauteur*(nbmasseLargeur-2))
//				   + (nbmasseHauteur-1)*(nbmasseLargeur-1)  
//				   + (nbmasseHauteur-1)*(nbmasseLargeur-1);
int nbtotalRessort = nbmasseLargeur;




//nbre total de triangles générés
int nbtotalTriangle = 2*((nbmasseHauteur-1)*(nbmasseLargeur-1));


int Massindex1D(int i,int j) 
// Fonction qui fait la correspondance entre un tableau 2D et un tableau 1D
//  i ---> pour la largeur, 
//  j ---> pour la hauteur,
{
	int index = i+(j*nbmasseLargeur);
	return index;
}

// Uitiliser pour déssiner la tige
GLUquadricObj *quadratic;
	
// Declaration  du reseau de masses-ressorts
 reseau ReseauMassesRessorts(nbtotalMass,nbtotalRessort,nbtotalTriangle);


// Construction du reseau de masses-ressorts (drapeau)
void ConstructionReseau()
{
	masse Lesmasses[nbmasseLargeur][nbmasseHauteur];
	int i,j;
	int nbm = 0;

	// Pour la tige
	quadratic=gluNewQuadric();

	//----- Création des masses -----//
	for(j=0;j<nbmasseHauteur;j++)
	{
		for(i=0;i<nbmasseLargeur;i++)
		{
			point ptemp(i-CoinHautGauche.x(),j-CoinHautGauche.y(),CoinHautGauche.z());
			Lesmasses[i][j].setPosition(ptemp);
			Lesmasses[i][j].setmasse(mas);
		}
	}

	//--- Quatres masses sont fixées aux 2 coins pour fixer le reseau à la tige ---//
	Lesmasses[0][nbmasseHauteur-1].setFixe(true);
	Lesmasses[0][nbmasseHauteur-2].setFixe(true);
	Lesmasses[0][0].setFixe(true);
	Lesmasses[0][1].setFixe(true);

	for(j=0;j<nbmasseHauteur;j++)
	{
		for(i=0;i<nbmasseLargeur;i++)
		{
			ReseauMassesRessorts.AjoutMasse(Lesmasses[i][j]); 
			nbm++;
		}
	}


	//----- Création des ressorts -----//
 
	int nbr = 0;
	ressort rtemp;

	// Ressort primaire selon la largeur
	for(j=0;j<nbmasseHauteur;j++)
	{
		for(i=0;i<(nbmasseLargeur-1);i++)
		{
			 rtemp.setidmasse1(Massindex1D(i,j));
			 rtemp.setidmasse2(Massindex1D(i+1,j));
			 rtemp.setconstRaideur(Kas);
			 rtemp.setLongueurRepos(1.0);
			 ReseauMassesRessorts.AjoutRessort(rtemp); 
			 nbr++;
		}
	}

	// Ressort secondaire selon la largeur
	for(j=0;j<nbmasseHauteur;j++)
	{
		for(i=0;i<(nbmasseLargeur-2);i++)
		{
			 rtemp.setidmasse1(Massindex1D(i,j));
			 rtemp.setidmasse2(Massindex1D(i+2,j));
			 rtemp.setconstRaideur(Kac);
			 rtemp.setLongueurRepos(2.0);
			 ReseauMassesRessorts.AjoutRessort(rtemp); 
			 nbr++;
		}
	}
	
	// Ressort primaire selon la hauteur
	for(j=0;j<(nbmasseHauteur-1);j++)
	{
		for(i=0;i<nbmasseLargeur;i++)
		{
		/*	if (i==0)
			{ // Ceci pour que le tissus soit bien droit au niveau de la tige
				rtemp.setidmasse1(Massindex1D(i,j));
				rtemp.setidmasse2(Massindex1D(i,j+1));
				rtemp.setconstRaideur(Kas);
				rtemp.setLongueurRepos(0.7); // On reduit la longueur au repos des ressorts touchant la tige
				ReseauMassesRessorts.AjoutRessort(rtemp); 
				nbr++;
			}
			else*/
			{
				rtemp.setidmasse1(Massindex1D(i,j));
				rtemp.setidmasse2(Massindex1D(i,j+1));
				rtemp.setconstRaideur(Kas);
				rtemp.setLongueurRepos(1.0);
				ReseauMassesRessorts.AjoutRessort(rtemp); 
				nbr++;
			}
		}
	}


	// Ressort secondaire selon la hauteur
	for(j=0;j<(nbmasseHauteur-2);j++)
	{
		for(i=0;i<nbmasseLargeur;i++)
		{
			 rtemp.setidmasse1(Massindex1D(i,j));
			 rtemp.setidmasse2(Massindex1D(i,j+2));
			 rtemp.setconstRaideur(Kac);
			 rtemp.setLongueurRepos(2.0);
			 ReseauMassesRessorts.AjoutRessort(rtemp); 
			 nbr++;
		}
	}

	// Ressort primaire selon la diagonale
	for(j=0;j<(nbmasseHauteur-1);j++)
	{
		for(i=0;i<(nbmasseLargeur-1);i++)
		{
			 rtemp.setidmasse1(Massindex1D(i,j));
			 rtemp.setidmasse2(Massindex1D(i+1,j+1));
			 rtemp.setconstRaideur(Kad);
			 rtemp.setLongueurRepos(1.4142);
			 ReseauMassesRessorts.AjoutRessort(rtemp); 
			 nbr++;
		}
	}


	// Ressort secondaire selon la diagonale
	for(j=0;j<(nbmasseHauteur-1);j++)
	{
		for(i=0;i<(nbmasseLargeur-1);i++)
		{
			 rtemp.setidmasse1(Massindex1D(i,j+1));
			 rtemp.setidmasse2(Massindex1D(i+1,j));
			 rtemp.setconstRaideur(Kad);
			 rtemp.setLongueurRepos(1.4142);
			 ReseauMassesRessorts.AjoutRessort(rtemp); 
			 nbr++;
		}
	}
	

	//----- Création des triangles -----//
	triangle t1temp, t2temp;
	for(j=0;j<(nbmasseHauteur-1);j++)
	{
		for(i=0;i<(nbmasseLargeur-1);i++)
		{
			t1temp.setmasse1id(Massindex1D(i,j));
			t1temp.setmasse2id(Massindex1D(i+1,j));
			t1temp.setmasse3id(Massindex1D(i+1,j+1));

			t2temp.setmasse1id(Massindex1D(i,j));
			t2temp.setmasse2id(Massindex1D(i+1,j+1));
			t2temp.setmasse3id(Massindex1D(i,j+1));

			ReseauMassesRessorts.AjoutTriangle(t1temp);
			ReseauMassesRessorts.AjoutTriangle(t2temp);
		}
	}

	ReseauMassesRessorts.setConstFricAirMasses(ConstFrictionAirMasses);
	ReseauMassesRessorts.setConstFricAirTriangles(ConstFrictionAirTriangles);

}

// Affiche la tige ou est accroché le drapeau
void AfficherTige()
{
	glEnable(GL_LIGHTING);
	glColor3f(0.2,0.2,0.2);
	glPushMatrix();
	glTranslated(-CoinHautGauche.x(),nbmasseHauteur-(CoinHautGauche.y()+1.0),0.0);
	glRotatef( 90.0f,1.0f,0.0f,0.0f);
	gluCylinder(quadratic,0.1f,0.1f,(nbmasseHauteur + 2.0),20,20);
	glPopMatrix();
}


	int mode;
	double beginx = 0.0;
	double beginy = 0.0;
	double dis = 20.0, azim = 0.0, elev = 0.0;
	double ddis = 0.0, dazim = 0.0, delev = 0.0;

	double Time = 0.0;

	bool animate = true;
	bool affichermasse = false;
	bool afficherressort = true;
	bool affichertriangle = true;
	bool affichernormal = true;

	GLfloat Specular[] = { 0.2f, 0.2f, 0.2f, 1.0f };   
	GLfloat SpecularExp[] = { 50 }; 

	GLfloat LightColorAmb[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat LightColorDif[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	GLfloat LightColorSpe[] = { 0.2f, 0.2f, 0.2f, 1.0f };


void
InitViewerWindow()
{
	ConstructionReseau();  

	glEnable(GL_COLOR_MATERIAL);

	glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, SpecularExp);
	glMaterialfv(GL_BACK, GL_SPECULAR, Specular);
	glMaterialfv(GL_BACK, GL_SHININESS, SpecularExp);

	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE); 
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, LightColorAmb);  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightColorDif); 
	glLightfv(GL_LIGHT0, GL_SPECULAR, LightColorSpe);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightColorDif); 
	glLightfv(GL_LIGHT1, GL_SPECULAR, LightColorSpe);
	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

  	glClearColor(0.0f,0.3f, 0.5f, 1.0f );
	glEnable(GL_NORMALIZE);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
  
	glFrustum(-0.4,0.4,-0.4,0.4,1,100.0);
	glMatrixMode(GL_MODELVIEW);
}

void 
KeyboardCB(unsigned char key, int x, int y) 
{
  switch(key) 
  {
	    case 'a':
        case 'A':
            animate = !animate;
            break;
		case 'm':
        case 'M':
             affichermasse = !affichermasse;
            break;
		case 'r':
        case 'R':
             afficherressort = !afficherressort;
            break;
        case 't':
        case 'T':
            affichertriangle = !affichertriangle;
            break;
		case 'n':
        case 'N':
            affichernormal = !affichernormal;
            break;
        case '\033':
        case 'q':
        case 'Q':
            exit(0);
        case ' ':
        default:
            break;
  }

  glutPostRedisplay();
}

void
MouseCB(int _b, int _s, int _x, int _y)
{
	if (_s == GLUT_UP)
	{
		dis += ddis;
		azim += dazim;
		elev += delev;
		ddis = 0.0;
		dazim = 0.0;
		delev = 0.0;
		return;
	}

	if (_b == GLUT_RIGHT_BUTTON)
	{
		mode = 0;
		beginy = _y;
		return;
	}
	else
	{
		mode = 1;
		beginx = _x;
		beginy = _y;
	}
}

void
MotionCB(int _x, int _y)
{
	if (mode == 0)
	{
		ddis = dis * (_y - beginy)/200.0;
	}
	else
	{
		dazim = (_x - beginx)/5.0;
		delev = (_y - beginy)/5.0;      
	}
	glutPostRedisplay();
}

inline void glVertex3v(float V[3]) { glVertex3fv(V); }
inline void glVertex3v(double V[3]) { glVertex3dv(V); }

void
TransformationCamera()
{
	glLoadIdentity();  
	glTranslatef(0.0, 0.0, -(dis+ddis));
	glRotated(elev+delev, 1.0, 0.0, 0.0);
	glRotated(azim+dazim, 0.0, 1.0, 0.0);
}


void
IdleCB() 
{
	glutPostRedisplay();
}

void
DisplayCB()
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	TransformationCamera();

	GLfloat light_position1[] = { 1.0, 1.0, 5.0, 0.0 };
	GLfloat light_position2[] = { 1.0, 1.0, -5.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);  
	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);  

	if (animate) 
	{
		Time += deltat;
		ReseauMassesRessorts.Miseajour(deltat);
	}

	// ---- Début Affichage des objets (la tige et le tissu)




	// *******      CHRIS     ****************
	// commenté pour tester et enlever la tige
	// 
	//AfficherTige();







	ReseauMassesRessorts.Afficher(affichermasse, afficherressort, affichertriangle, affichernormal);


	glutSwapBuffers();
}

void Help()
{

	cout<< " ***---------------------------------***"<<endl;
	cout<< " ***              Menu               ***"<<endl;
	cout<< " ***---------------------------------***"<<endl;
	cout<<endl;
	cout<< "  a ou A --> Play ou Pause de l'animation"<<endl;
	cout<< "  m ou M --> afficher les masses         "<<endl;
	cout<< "  r ou R --> afficher les ressorts       "<<endl;
	cout<< "  t ou T --> afficher les triangles      "<<endl;
	cout<< "  n ou N --> afficher les normales       "<<endl;
	cout<<endl;
	cout<< " ***---------------------------------***"<<endl;
	cout<< " ***---------------------------------***"<<endl;
	cout<<endl;
}


//-------------------------- Fonction Principale ----------------------------//
//---------------------------------------------------------------------------//
int main(int argc, _TCHAR* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(512,512);

  // create the window
	glutCreateWindow("Reseau de masses-ressorts");

  // set OpenGL graphics state -- material props, perspective, etc.
	InitViewerWindow();
	Help();

  // set the callbacks
	glutDisplayFunc(DisplayCB);
	glutIdleFunc(IdleCB);
	glutMouseFunc(MouseCB);
	glutMotionFunc(MotionCB);  
	glutKeyboardFunc(KeyboardCB);

  // Enter the main loop.
	glutMainLoop();
}
//---------------------------------------------------------------------------//
//---------------------------------------------------------------------------//