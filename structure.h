#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "faction.h"
#include "plateau.h"

/*---------------------------------Grille---------------------------------*/
typedef struct cell_base cell;
typedef cell* grille;

/*  @requires : card est valide
    @assigns  : nothing
    @ensures  : retourne une grille vide avec la cellule de coordonnées (0,0) ayant la carte c dessus,*/
grille debut_grille(carte card);

/*  @requires : c cellule de la grille valide, direction entre 1 et 4
    @assigns  : c
    @ensures  : le pointeur c->direction devient la cellule ayant les coordonnées (i,j)
*/
void pointer_to(cell* c, int direction, int i, int j);

/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne la cellule qui a pour coordonnées (i,j) ; error si aucune cellule n'a ces coordonnées
*/
cell find_cell(int i, int j);

/*  @requires : c est une cellule valide, c->direction est libre
    @assigns  : c
    @ensures  : retourne -1 si c->direction n'est pas libre ; 0 si la carte a été placée
*/
int place_card_next_to(cell* c, int direction, carte card);

/*---------------------------------Cartes en main---------------------------------*/
typedef carte* carteEnMain; /*Tableau 1D de cartes*/

/*---------------------------------Pioche---------------------------------*/
typedef struct bucket* pioche;

/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne une pioche vide */
pioche cree_pioche_vide();

/*  @requires : l est une pioche valide
    @assigns  : nothing
    @ensures  : retourne 1 si l est vide et 0 sinon */
int est_vide(pioche l);

/*  @requires : pl est un pointeur valide vers une pioche valide
    @assigns  : *pl
    @ensures  : ajoute c au dessus de la pioche pl */
void push(carte c, pioche *pl);

/*  @requires : pl est un pointeur valide vers une pioche valide non-vide
    @assigns  : *pl
    @ensures  : retourne la tête de la pioche et la retire de la pioche */
carte pop(pioche *pl);
/*pop = tirer une carte*/

/*  @requires : l est une pioche valide
    @assigns  : nothing
    @ensures  : print la pioche */
void print_pioche(pioche l);

#endif