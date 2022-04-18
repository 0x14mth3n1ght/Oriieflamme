#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "plateau.h"

//TEMPORAIRE
typedef carte elt; /*valeur des éléments de la liste*/

/*----------- Grille : liste doublement chainee imbriquee dans liste doublement chainee d'éléments de type cell -----------*/
//Type abstrait des cases de la grille
typedef struct grid_base * grid;
typedef struct cell_base * cell;


/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne la grille vide */
grid init_grille();

/*  @requires : c est une cellule valide, pg est un pointeur valide vers une grille valide (vide au centre)
    @assigns  : *pg
    @ensures  : ajoute à *pg la cellule c au centre (aux coordonnées (0,0)) */
void premiere_cellule(cell c, grid* pg);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne 1 si la case (x,y) n'est pas occupée, 0 sinon */
int est_libre(grid g, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : libère la mémoire associée à la grille *pg */
void free_grille(grid* pg);

//PLACEMENTS

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c à l'ouest de la cellule (non-nulle) en (x,y) de la grille *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_west(cell c, grid* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c à l'est de la cellule (non-nulle) en (x,y) de la grille *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_east(cell c, grid* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c au nord de la cellule (non-nulle) en (x,y) de la grille *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_north(cell c, grid* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c au sud de la cellule (non-nulle) en (x,y) de la grille *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_south(cell c, grid* pg, int x, int y);

//INFO SUR LA CELLULE

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la cellule nulle*/
cell get_cell(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située à l'ouest de celle située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la cellule nulle */
cell get_cell_west(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située à l'est de celle située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la cellule nulle */
cell get_cell_east(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située au nord de celle située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la cellule nulle */
cell get_cell_north(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située au sud de celle située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la cellule nulle */
cell get_cell_south(grid g, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : supprime la cellule de la grille située aux coordonnées (x,y) de la grille *pg (remplacée par la cellule nulle), retourne 1 le cas échéant. retourne 0 sinon (pas de cellule ou cellule déjà supprimée) */
int supp_cell_grille(grid* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : déplace la cellule située aux coordonnées (x1,y1) de la grille *pg (remplacée par la cellule nulle) vers les coordonnées (x2, y2),
    retourne 0 le cas échéant.
    retourne -1 si problème sur la case de départ (x1, y1)
    retourne 1 si problème sur la case d'arrivée (x2, y2)*/
int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au nord de la grille*/
int taille_north(grid g);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au sud de la grille*/
int taille_south(grid g);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest de la grille*/
int taille_west(grid g);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la grille*/
int taille_east(grid g);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest de la ligne i de la grille*/
int taille_ligne_west(grid g, int i);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la ligne i de la grille*/
int taille_ligne_east(grid g, int i);

/*--------------------------------- Liste chainée ---------------------------------*/
typedef struct bucket *liste;

/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne une liste vide */
liste cree_liste_vide();

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne 1 si l est vide et 0 sinon */
int test_vide(liste l);

/*  @requires : pl est un pointeur valide vers une liste valide
    @assigns  : *pl
    @ensures  : ajoute e au dessus de la liste *pl */
void push(elt e, liste* pl);

/*  @requires : pl est un pointeur valide vers une liste valide non-vide
    @assigns  : *pl
    @ensures  : retourne l'élément en haut de la liste et le retire de la liste*/
elt pop(liste* pl); // = tirer une carte;

/*  @requires : l est une liste valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément en haut de la liste */
elt peek(liste l);

/*  @requires : l est une liste valide, e est un élément valide
    @assigns  : nothing
    @ensures  : teste si e est dans la liste l et retourne son indice de première occurence (de 0 à len_liste(l)-1) dans la liste le cas échéant, -1 sinon */
int indice(elt e, liste l);

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne le nombre d'éléments dans la liste */
int len_liste(liste l);

/*  @requires : pl est un pointeur valide vers une liste valide non-vide
    @assigns  : *pl
    @ensures  : supprime la première occurence de l'élément e de la liste, retourne 1 le cas échéant, 0 sinon*/
int enlever(elt e, liste* pl);

/*  @requires : l est une liste valide, 0 <= pos < len_liste(l)
    @assigns  : nothing
    @ensures  : renvoie l'élement de la liste l situé à la position pos, l est indexé de 0 à len_liste(l)-1 */
elt get_at(int pos, liste l);

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne une liste qui contient les éléments de l mais mélangées */
liste melanger(liste l);


#endif