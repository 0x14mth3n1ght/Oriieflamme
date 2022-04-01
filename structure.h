#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "faction.h"
#include "plateau.h"

/* LISTE CHAINEE */
/*Type concret des éléments de la pile*/
typedef carte value;

/*Structure de liste chaînée*/
typedef struct bucket* list;

struct bucket {
    value val;
    list next;
};

/*  @requires nothing
    @assigns nothing
    @ensures retourne une liste vide */
list cree_liste_vide();

/*  @requires l est une liste valide
    @assigns nothing
    @ensures retourne 1 si l est vide et 0 sinon    */
int est_vide(list l);

/*  @requires pl est un pointeur valide vers une liste valide
    @assigns *pl
    @ensures ajoute a au dessus de la liste pl       */
void push(value a, list *pl);

/*  @requires pl est un pointeur valide vers une liste valide non-vide
    @assigns *pl
    @ensures retourne la tête de la liste et la retire de la liste */
value pop(list *pl);

/*  @requires l est une liste valide
    @assigns nothing
    @ensures print la liste    */
void print_liste(list l);

/* TABLEAU 2D */
typedef carte** grille;

/*  @requires h>0, w>0
    @assigns nothing
    @ensures retourne une matrice of zeros, de hauteur h and largeur w   */
grille creer_grille(int h, int w);

/*  @requires t de hauteur h et de largeur w;
    @assigns nothing
    @ensures affiche le contenu de la grille g   */
void affiche_grille(grille g, int h, int w);


#endif