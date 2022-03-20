#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "carte.h"
#include "faction.h"

/* Type abstrait d'un plateau de jeu (tableau 2D) */
typedef struct plateau_base *plateau;

/*
@requires: nothing
@assigns: nothing
@ensures: Initialise un plateau vide
*/
plateau creer_plateau();

/*
@requires: *p pointeur vers plateau valide
@assigns: nothing
@ensures: libère la mémoire associée au plateau*/
void detruire_plateau(plateau *p);

/*
@requires: *p pointeur vers plateau valide
@assigns: plateau
@ensures: réinitialise le jeu en renvoyant 0 ou indique s'il est terminé en renvoyant 1
*/
int reinitialisation(plateau *p);

/*
@requires: f1 et f2 sont des pointeurs vers des factions valides
@assigns: nothing
@ensures: affiche l'état du jeu en renvoyant la liste des factions
*/
void retourne_factions(faction *f1,faction *f2);

/*
@requires: *p pointeur vers plateau valide *f est pointeur vers une faction valide , *carte et *position pointeurs valides vers tableaux d'entiers de taille 2
@assigns: faction
@ensures: place sur le plateau une carte à jouer (cachée) et renvoie 1 si le placement est effectué, 0 sinon
*/
int pose_carte(plateau *p,faction *f,carte *c,int *position);

/*
@requires: *p pointeur vers plateau valide, *reste pointeur vers entier
@assigns: plateau
@ensures: retourne une carte face visible , active son effet et indique le nombre de cartes restances en actualisant reste
*/

carte active_carte(plateau *p,int *reste);

#endif
