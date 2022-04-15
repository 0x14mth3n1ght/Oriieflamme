#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "plateau.h"

/*----------- Plateau = Grille : liste doublement chainee imbriquee dans liste doublement chainee d'éléments de type cell -----------*/
//Temporaire :
typedef carte cell;

/*  @requires : c est une cellule valide
    @assigns  : nothing
    @ensures  : retourne le plateau contenant la cellule c au centre */
plateau init_grille(cell c);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne 1 si la case (x,y) n'est pas occupée, 0 sinon */
int est_libre(plateau g, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide
    @assigns  : *pg
    @ensures  : libère la mémoire associée au plateau *pg */
void free_grille(plateau *pg);

//PLACEMENTS

/*  @requires : pg est un pointeur valide vers un plateau valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c à l'ouest de la cellule (non-nulle) en (x,y) du plateau *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_west(cell c, plateau* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c à l'est de la cellule (non-nulle) en (x,y) du plateau *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_east(cell c, plateau* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c au nord de la cellule (non-nulle) en (x,y) du plateau *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_north(cell c, plateau* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide, c est une cellule valide, (x,y) sont les coordonnées d'une case occupée
    @assigns  : *pg
    @ensures  : place, si la case n'est pas occupée, la cellule c au sud de la cellule (non-nulle) en (x,y) du plateau *pg , retourne 1 le cas échéant. retourne 0 sinon */
int placer_south(cell c, plateau* pg, int x, int y);

//INFO SUR LA CELLULE

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la cellule située aux coordonnées (x,y) du plateau g ; s'il n'y a pas de cellule, renvoie la cellule nulle*/
cell get_cell(plateau g, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide
    @assigns  : *pg
    @ensures  : supprime la cellule du plateau située aux coordonnées (x,y) du plateau *pg (remplacée par la cellule nulle), retourne 1 le cas échéant. retourne 0 sinon (pas de cellule ou cellule déjà supprimée) */
int supp_cell_plateau(plateau* pg, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide
    @assigns  : *pg
    @ensures  : déplace la carte du plateau située aux coordonnées (x1,y1) du plateau *pg (remplacée par la cellule nulle) vers les coordonnées (x2, y2),
    retourne 0 le cas échéant.
    retourne -1 si problème sur la case de départ (x1, y1)
    retourne 1 si problème sur la case d'arrivée (x2, y2)*/
int deplacer_cell(plateau* pg, int x1, int y1, int x2, int y2);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au nord du plateau*/
int taille_north(plateau g);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au sud du plateau*/
int taille_south(plateau g);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest du plateau*/
int taille_west(plateau g);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est du plateau*/
int taille_east(plateau g);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest de la ligne i du plateau*/
int taille_ligne_west(plateau g, int i);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la ligne i du plateau*/
int taille_ligne_east(plateau g, int i);

/*--------------------------------- Liste chainée ---------------------------------*/
typedef struct bucket *liste;
typedef carte elt; /*valeur des éléments de la liste*/

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