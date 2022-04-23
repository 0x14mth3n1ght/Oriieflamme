#ifndef _PLATEAU_H
#define _PLATEAU_H

#include "carte.h"
#include "faction.h"

/* Type abstrait d'un plateau de jeu */
typedef struct plateau_base *plateau;

/* Type concret d'une case du plateau */
struct cell_base{
   carte c;
   faction f;
   /* indique si la carte est retournee */
   int visible;
   /* indique si l'effet de la carte est active */
   int activee;
};

/*
@requires: nothing
@assigns: nothing
@ensures: Initialise un plateau vide
*/
plateau cree_plateau();

/*
@requires: *p pointeur vers plateau valide
@assigns: nothing
@ensures: libère la mémoire associée au plateau*/
void detruire_plateau(plateau *p);

/*
@requires: *p pointeur vers plateau valide
@assigns: plateau *p
@ensures: réinitialise le jeu en vidant le plateau et la main des deux factions. Mélange la pioche des deux factions et fait repiocher les deux factions
*/
int reinitialisation(plateau *p);

/*
@requires: f1 et f2 sont des pointeurs vers des factions valides
@assigns: nothing
@ensures: affiche l'état du jeu en renvoyant la liste des factions
*/
void retourne_factions(faction *f1,faction *f2);

/*
@requires: *p pointeur vers plateau valide *f est pointeur vers une faction valide , c carte valide et *position pointeur valide vers tableau d'entier de taille 2
@assigns: *p et *f
@ensures: place sur le plateau une carte à jouer (cachée) et renvoie 1 si le placement est effectué, 0 sinon
*/
int pose_carte(plateau *p, faction *f, carte c, int *position);

/*
@requires: *p pointeur vers plateau valide
@assigns: *p
@ensures: retourne une carte face visible , active son effet
*/
carte active_carte(plateau *p);

/*
@requires: *p pointeur vers plateau valide, x et y deux entiers réprésentant les coordonnées.
@assigns: rien
@ensures retourne 0 si la carte posee aux cooroonnees de position est face cachee, 1 si elle est face visible
et enfin 2 s'il n'y a pas de carte a cet endroit
*/
int cachee_visible_existe(plateau *p, int x, int y);

/*
@requires une cellule de type struct cell_base
@assigns rien
@ensures retourne le nom de la carte posée à cette cellule, s'il n'y en n'a pas une exception est levée */
char* get_name(struct cell_base cellule);

/*
@requires une cellule de type struct cell_base
@assings rien
@ensures retourne un int qui correspond à la faction à laquelle appartient la carte sur la cellule,
s'il n'y a pas de carte sur la cellule une exception est renvoyée.*/
int get_faction_int(struct cell_base cellule);

/*
@requires une cellule de type struct cell_base
@assings rien
@ensures retourne la faction à laquelle appartient la carte sur la cellule,
s'il n'y a pas de carte sur la cellule une exception est renvoyée.*/
faction get_faction(struct cell_base cellule);

/*
@requires une cellule de type struct cell_base
@assings rien
@ensures retourne 1 si la carte sur cette cellule est face visible, 0 si face cachée, et renvoie une 
exception s'il n'y a pas de carte sur cette cellule */
int get_retournee(struct cell_base cellule);

/*
@requires une cellule de type struct cell_base
@assings rien
@ensures retourne 1 si la carte sur cette cellule est activee, 0 sinon, et renvoie une 
exception s'il n'y a pas de carte sur cette cellule */
int get_activee(struct cell_base cellule);

/*
@requires une cellule de type struct cell_base
@assings rien
@ensures retourne la carte posee sur cette cellule et une exception 
s'il n'y a pas de carte sur cette cellule */
carte get_card(struct cell_base cellule);

/*
@requires un plateau p
@assings rien
@ensures retourne la grille correspondant au plateau
*/
grid get_grid(plateau p);

#endif
