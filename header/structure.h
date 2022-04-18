#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "plateau.h"

/*----------- Grille : liste doublement chainee imbriquee dans liste doublement chainee d'éléments de type cell -----------*/
typedef struct grid_base * grid;
//Type abstrait des cases de la grille
typedef struct cell_base * cell;

//Directions
enum direction {west, north, east, south};
typedef enum direction direction;

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

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide
    @assigns  : *pg
    @ensures  : place la cellule c sur la case (x,y) de la grille si la case n'est pas occupée, retourne 1 le cas échéant. retourne 0 sinon */
int placer_cell(cell c, grid* pg, int x, int y);

//INFO SUR LA CELLULE

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la NULL*/
cell get_cell(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case le plus éloignée dans la direction d de la grille g*/
int taille_direction(direction d, grid g);

/*  @requires : g est une grille valide, d = west ou east
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case sle plus éloignée dans la direction d de la ligne i de la grille*/
int taille_ligne_direction(direction d, grid g, int i);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : déplace la cellule située aux coordonnées (x1,y1) de la grille *pg (remplacée par la cellule nulle) vers les coordonnées (x2, y2),
    retourne 0 le cas échéant.
    retourne -1 si problème sur la case de départ (x1, y1)
    retourne 1 si problème sur la case d'arrivée (x2, y2)*/
int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : supprime la cellule de la grille située aux coordonnées (x,y) de la grille *pg (remplacée par la cellule nulle), retourne 1 le cas échéant. retourne 0 sinon (pas de cellule ou cellule déjà supprimée) */
int supp_cell_grille(grid* pg, int x, int y);

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
int find(elt e, liste l);

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