#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "plateau.h"

/*----------- Plateau = Grille : liste doublement chainee imbriquee dans liste doublement chainee -----------*/

/*  @requires : c est une carte valide
    @assigns  : nothing
    @ensures  : retourne le plateau contenant la carte c au centre */
plateau init_grille(carte c);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne 1 si la case (x,y) n'est pas occupée, 0 sinon */
int est_libre(plateau g, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide, c est une carte valide
    @assigns  : *pg
    @ensures  : place la carte c sur la case (x,y) de la plateau si la case n'est pas occupée, retourne 1 le cas échéant. retourne 0 sinon */
int placer_carte(carte c, int x, int y, plateau* pg);

/*  @requires : g est un plateau valide
    @assigns  : nothing
    @ensures  : retourne la carte située aux coordonnées (x,y) du plateau g ; s'il n'y a pas de carte, renvoie la carte nulle*/
carte get_carte(plateau g, int x, int y);

/*  @requires : pg est un pointeur valide vers un plateau valide
    @assigns  : *pg
    @ensures  : supprime la carte du plateau située aux coordonnées (x,y) du plateau *pg (remplacée par la carte nulle), retourne 1 le cas échéant. retourne 0 sinon (pas de carte ou carte déjà supprimée) */
int supp_carte_plateau(plateau* pg, int x, int y);

/*--------------------------------- Liste chainee de cartes ---------------------------------*/
typedef struct bucket *liste;
typedef carte elt; /*valeur des éléments de la liste*/
/*Structures héritant de la structure de liste*/
typedef liste pioche;
typedef liste carteEnMain;

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