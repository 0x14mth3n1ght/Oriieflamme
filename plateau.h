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
@requires: plateau
@assigns: nothing
@ensures: libère la mémoire associée au plateau*/
void detruire_plateau(plateau);

/*
@requires: plateau* est un pointeur valide
@assigns: plateau
@ensures: réinitialise le jeu ou indique s'il est terminé en renvoyant 1
*/
int reinitialisation(plateau);

/*
@requires: f1 et f2 sont des pointeurs vers des factions valides
@assigns: nothing
@ensures: affiche l'état du jeu en renvoyant la liste des factions
*/
void retourne_factions(faction *f1,faction *f2);

/*
@requires: faction* est pointeur vers une faction valide
@assigns: faction*
@ensures: pioche une carte à jouer (cachée)
*/
void carte_faction(faction*);

/*
@requires: carte valide
@assigns: carte
@ensures: retourne une carte face visible et activer son effet
*/

carte_base active_carte(faction);

#endif
