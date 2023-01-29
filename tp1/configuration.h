
/* Le temps est mesuré en millisecondes. */
static	long t = 0;  // la variable de temps (en millisecondes).
const	long dt = 16.6666666666666; // la différence de temps entre deux images (en millisecondes).
const	long t_cycle = 10000; // le temps d'un cycle d'animation (en millisecondes)
static	double t_norm; // le temps normalisé : au debut du cycle =0 et a la fin, = 1.0 - epsilon

const int GrandeurTable = 100; // Grandeur de la table pour la fonction u=U(s)