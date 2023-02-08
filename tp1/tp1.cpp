
/* Gabarit pour le tp1 de imn504 Richard Egli */
/* Mouvement de la camera le long d'une trajectoire */ 

/**********************  TP1 *************************************************/
/*                                                                           */
/*  NOM 1 :  Julien Bernat                                                   */
/*  MATRICULE 1: 19096032	     					     */
/*                                                                           */
/*  NOM 2 :                                                                  */
/*  MATRICULE 2:                                                             */
/*                                                                           */
/*****************************************************************************/

#include <iostream>
using namespace std;
#include <vector>  // template "vector" pour les points de controle
using namespace std;

#include "glut.h"
#include "utilalg.h"

#include "configuration.h" 

const int TEXDIM = 256;

vector<point> PointsControle;


GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};  /*  lumiere diffuse blanche. */
GLfloat light_spec[] = {1.0f, 1.0f, 1.0f, 1.0f};     /*  lumiere speculaire blanche. */
GLfloat light_ambient[] = {0.1f, 0.1f, 0.1f, 1.0f};  /*  lumiere ambiante blanche. */
GLfloat light_position[] =
  {5.0, 5.0, 10.0, 1.0};

enum enummode {
  CAM_FIXE, SAUT, INTER_LIN, INTER_CAT_ROM, INTER_CAT_ROM_T}; // differents modes de la camera


  enummode mode =CAM_FIXE;

/* Create a single component texture map */
GLfloat *
make_texture(int maxs, int maxt)
{
  int s, t;
  static GLfloat *texture;

  texture = (GLfloat *) malloc(maxs * maxt * sizeof(GLfloat));
  for (t = 0; t < maxt; t++) {
    for (s = 0; s < maxs; s++) {
      texture[s + maxs * t] = ((s >> 4) & 0x1) ^ ((t >> 4) & 0x1);
    }
  }
  return texture;
}

enum {
  SPHERE = 1, CONE
};


void timer(int value)
{
	t+=dt; // le temps s'ecoule...

	if (t >= t_cycle)  // le temps est remis a zero lorqu'il atteint la fin du cycle
		t=0;

	t_norm = double(t) / double(t_cycle); // temps normalisé (voir la declaration de t_norm)

	glutPostRedisplay(); // la procedure d'affichage "display" est appelée
	cout << " t = " << t << "       t_norm = " << t_norm << endl;
	glutTimerFunc(dt, timer, 0); // rappeler la procedure timer dans dt millisecondes
}

bool LirePointsControle(char *filename)
{
	FILE *fp;
	int i,NbpointsControl;
	float x,y,z;

	fp = fopen(filename,"r");

	if (fp==NULL)
		return false;

	PointsControle.clear();

	fscanf(fp,"%d\n",&NbpointsControl);

	for (i=0;i<NbpointsControl;i++)
	{
		fscanf(fp,"%f %f %f\n",&x,&y,&z);
		PointsControle.push_back(point(x,y,z));
	}

	fclose(fp);

	
	return true;
}

void InitTable() // initialiser votre table G(u)
{
}

void saut(reel t, point& PO)
{
	int i = t*PointsControle.size();
	PO=PointsControle[i];
}

void inter_lin(reel t_norm, point&  PO, vecteur& VN) // à compléter
{
	//Nombre de segment dans la courbe
	int nbSeg = (PointsControle.size() - 1);
	//Numero du segment actuel
	int i = t_norm * nbSeg;
	//Le temps ajuste de 0 a 1 pour chaque segment
	reel t = (t_norm - (reel(i) / reel(nbSeg))) * nbSeg;

	if (t == 1) {
		return;
	}

	point PC0 = PointsControle[i];
	point PC1 = PointsControle[i+1];

	vecteur V = PC1 - PC0;

	PO = PC0 + t * V;
	VN = V;
}

void cat_rom(reel t_norm, point&  PO, vecteur& VN) // à compléter
{
	//Points
	point prev;
	point PC0;
	point PC1;
	point PC2;
	//Tangeantes
	vecteur M0;
	vecteur M1;

	//Nombre de segment dans la courbe
	int nbSeg = (PointsControle.size() - 1);
	//Numero du segment actuel
	int i = t_norm * nbSeg;
	//Le temps ajuste de 0 a 1 pour chaque segment
	reel t = (t_norm - (reel(i) / reel(nbSeg))) * reel(nbSeg);
	if (t == 1) {
		return;
	}

	if (i == 0) {
		//Premier segment de la courbe
		PC0 = PointsControle[i];
		PC1 = PointsControle[i + 1];
		PC2 = PointsControle[i + 2];

		M0 = 0.5 * ((PC1 - (PC2 - PC1)) - PC0);
		M1 = 0.5 * (PC2 - PC0);
	}
	else if (i == PointsControle.size() - 2) {
		//Dernier segment de la courbe 
		//Si le t est 1 on ne fait pas le calcul pour ne pas repeter le dernier/premier frame
		if (t < 1) {
			prev = PointsControle[i - 1];
			PC0 = PointsControle[i];
			PC1 = PointsControle[i + 1];
			M0 = 0.5 * (PC1 - prev);
			//Calcul de la derniere tangeante
			M1 = 0.5 * (PC1 - (PC0 - (prev - PC0)));
		}
		
	}
	else if(i != PointsControle.size()) {
		//Cas normal
		prev = PointsControle[i-1];
		PC0 = PointsControle[i];
		PC1 = PointsControle[i + 1];
		PC2 = PointsControle[i + 2];
		
		M0 = 0.5 * (PC1 - prev);
		M1 = 0.5 * (PC2 - PC0);
	}

	reel t3 = pow(t, 3);
	reel t2 = pow(t, 2);

	//Calcul du point voir page wiki Cubic Hermit spline 
	PO = (2 * t3 - 3 * t2 + 1) * PC0 + (t3 - 2 * t2 + t) * M0 + (-2 * t3 + 3 * t2) * PC1 + (t3 - t2) * M1;

	//Calcul des derive pour la direction de regard de la camera
	reel x = (6 * t2 - 6 * t) * PC0.x() + (3 * t2 - 4 * t + 1) * M0.x() + (-6 * t2 + 6 * t) * PC1.x() + (3 * t2 - 2 * t) * M1.x();
	reel y = (6 * t2 - 6 * t) * PC0.y() + (3 * t2 - 4 * t + 1) * M0.y() + (-6 * t2 + 6 * t) * PC1.y() + (3 * t2 - 2 * t) * M1.y();
	reel z = (6 * t2 - 6 * t) * PC0.z() + (3 * t2 - 4 * t + 1) * M0.z() + (-6 * t2 + 6 * t) * PC1.z() + (3 * t2 - 2 * t) * M1.z();

	VN = vecteur(x, y, z);

}


void cat_rom_t(reel t_norm, point&  PO, vecteur& VN) // à compléter
{
}

void display(void)
{
	point PO(0,0,42);
	vecteur VN(0,0,-1);

    glLoadIdentity(); // // La matrice modelview est initialisee a identite.

	switch (mode) {
		case CAM_FIXE:
			break;
		case SAUT:
			saut(t_norm, PO);
			break;
		case INTER_LIN :
			inter_lin(t_norm, PO,VN);
			break;
		case INTER_CAT_ROM:
			cat_rom(t_norm, PO,VN);
			break;
		case INTER_CAT_ROM_T :
			cat_rom_t(t_norm, PO,VN);
			break;
	}

	gluLookAt(PO.x(), PO.y(), PO.z(),  //             // PO point de l'oeil 
    PO.x()+VN.x(), PO.y()+VN.y(), PO.z()+VN.z(),      // VN est le vecteur de direction de regard
    0.0, 1.0, 0.);                                    // le haut de la scene est dans la direction Y 
	 /* Une seule source lumineuse (GL_LIGHT0) */
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_spec);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHT0); // indique a OpenGL que la lumiere 0 est active 
    glEnable(GL_LIGHTING); // indique a OpenGL d'utiliser les lumieres pour le calcul d'illumination.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // On efface les buffers de l'image courante
 

	/* Scene du fichier accumaa.c - par Tom McReynolds, SGI, dans un exemple de glut */

	/* material properties for objects in scene */
    static GLfloat wall_mat[] =
    {1.f, 1.f, 1.f, 1.f};

  /* Note: wall verticies are ordered so they are all front facing this lets
     me do back face culling to speed things up.  */

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wall_mat);

	/* floor */
	/* make the floor textured */
	glEnable(GL_TEXTURE_2D);

  /* Since we want to turn texturing on for floor only, we have to make floor 
     a separate glBegin()/glEnd() sequence. You can't turn texturing on and
     off between begin and end calls */
	glTranslatef(0.0, 0.0, 42.0); 
	glBegin(GL_QUADS);
	glNormal3f(0.f, 1.f, 0.f);
	glTexCoord2i(0, 0);
	glVertex3f(-10.f, -10.f, -32.f);
	glTexCoord2i(1, 0);
	glVertex3f(10.f, -10.f, -32.f);
	glTexCoord2i(1, 1);
	glVertex3f(10.f, -10.f, -52.f);
	glTexCoord2i(0, 1);
	glVertex3f(-10.f, -10.f, -52.f);
	glEnd();

	glDisable(GL_TEXTURE_2D);

	/* walls */

	glBegin(GL_QUADS);
	/* left wall */
	glNormal3f(1.f, 0.f, 0.f);
	glVertex3f(-10.f, -10.f, -32.f);
	glVertex3f(-10.f, -10.f, -52.f);
	glVertex3f(-10.f, 10.f, -52.f);
	glVertex3f(-10.f, 10.f, -32.f);

	/* right wall */
	glNormal3f(-1.f, 0.f, 0.f);
	glVertex3f(10.f, -10.f, -32.f);
	glVertex3f(10.f, 10.f, -32.f);
	glVertex3f(10.f, 10.f, -52.f);
	glVertex3f(10.f, -10.f, -52.f);

	/* ceiling */
	glNormal3f(0.f, -1.f, 0.f);
	glVertex3f(-10.f, 10.f, -32.f);
	glVertex3f(-10.f, 10.f, -52.f);
	glVertex3f(10.f, 10.f, -52.f);
	glVertex3f(10.f, 10.f, -32.f);

	/* back wall */
	glNormal3f(0.f, 0.f, 1.f);
	glVertex3f(-10.f, -10.f, -52.f);
	glVertex3f(10.f, -10.f, -52.f);
	glVertex3f(10.f, 10.f, -52.f);
	glVertex3f(-10.f, 10.f, -52.f);
	glEnd();

	glPushMatrix();
	glTranslatef(-8.f, -6.f, -42.f);
	glCallList(SPHERE);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.f, -8.f, -50.f);
	glCallList(CONE);
	glPopMatrix();

	glutSwapBuffers(); // affiche et interchange le buffer dans lequel on a ecrit avec celui qui est affiche.

}

void init(void)
{
  GLfloat *tex;
  static GLfloat sphere_mat[] =
  {1.f, .5f, 0.f, 1.f};
  static GLfloat cone_mat[] =
  {0.f, .5f, 1.f, 1.f};
  GLUquadricObj *sphere, *cone, *base;

  /* Utiliser un tampon-z pour eliminer les surfaces cachees. */
  glEnable(GL_DEPTH_TEST);


  glMatrixMode(GL_PROJECTION); 
  glLoadIdentity(); // La matrice de projection est initialisee a identite.
  gluPerspective( /* angle de vision */ 75.0,
    /* aspect ratio (image carree ici) */ 1.0,
    /* plan de decoupage avant */ 0.1, /* plan de decoupage arriere */ 200.0);

  glMatrixMode(GL_MODELVIEW);

  glEnable(GL_NORMALIZE); // Les vecteurs normaux sont normalises pour le calcul de l'illumination.

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

  glNewList(SPHERE, GL_COMPILE);
  /* make display lists for sphere and cone; for efficiency */
  sphere = gluNewQuadric();
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sphere_mat);
  gluSphere(sphere, 2.f, 20, 20);
  gluDeleteQuadric(sphere);
  glEndList();

  glNewList(CONE, GL_COMPILE);
  cone = gluNewQuadric();
  base = gluNewQuadric();
  glRotatef(-90.f, 1.f, 0.f, 0.f);
  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cone_mat);
  gluDisk(base, 0., 2., 2, 1);
  gluCylinder(cone, 2., 0., 6., 20, 20);
  gluDeleteQuadric(cone);
  gluDeleteQuadric(base);
  glEndList();

  /* load pattern for current 2d texture */
  tex = make_texture(TEXDIM, TEXDIM);
  glTexImage2D(GL_TEXTURE_2D, 0, 1, TEXDIM, TEXDIM, 0, GL_RED, GL_FLOAT, tex);
  free(tex);



}

void menu(int value)
{
	mode = (enummode) value;
	t_norm=0; // recommence l'animation au début
	t=0;
}

int main(int argc, char **argv){
  

  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("tp1 - animation");
  glutDisplayFunc(display);  // la procedure appellee pour l'affichage est 'display'.
  init();
  glutTimerFunc(dt, timer, 0);  // la procedure timer sera appellee dans dt millisecondes

  if (!LirePointsControle(argv[1]))
  {
	  cout << "Erreur pour le fichier de points de controle" << endl;
	  return 0;
  }
  
  InitTable();

  glutCreateMenu(menu);
  glutAddMenuEntry("Camera fixe", CAM_FIXE);
  glutAddMenuEntry("Camera d'un point de controle a l'autre", SAUT);
  glutAddMenuEntry("Interpolation lineaire", INTER_LIN);
  glutAddMenuEntry("Interpolation Catmull-Rom", INTER_CAT_ROM);
  glutAddMenuEntry("Interpolation Catmull-Rom vitesse constante", INTER_CAT_ROM_T);
 
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutMainLoop(); // attendre les evenements
  return 0;
}
