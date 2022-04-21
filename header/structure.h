#ifndef STRUCTURE_H
#define STRUCTURE_H
/**
 * @file structure.h
 * @brief Mise en place de structures de grille infinie et de liste chaînée.
 * 
 */


/*Obtention des types*/
#include "carte.h"
#include "plateau.h"

/*----------- Grille : liste doublement chainee imbriquee dans liste doublement chainee d'éléments de type cell -----------*/
/**
 * @typedef grid
 * @brief Pointeur vers la structure de liste chaînée mère, chaque maillon représentant une ligne de la grille
 */
typedef struct grid_base * grid;

/**
 * @typedef cell
 * @brief Type abstrait des cases de la grille
 * 
 */
typedef struct cell_base * cell;

//Directions

/**
 * @typedef direction
 * @brief Direction.
 * Permet de choisir une direction sur des fonctions les nécéssitant.
 */
enum direction {west, north, east, south};
typedef enum direction direction;

/**
 * @brief Permet la création et l'allocation mémoire d'une grille vide.
 * 
 * @return une grille vide.
 */
grid init_grille();

/*  @requires : c est une cellule valide, pg est un pointeur valide vers une grille valide (vide au centre)
    @assigns  : *pg
    @ensures  : ajoute à *pg la cellule c au centre (aux coordonnées (0,0)) */
/**
 * @brief Modifie *pg en ajoutant la cellule c au centre (aux coordonnées (0,0)).
 * 
 * @param c une cellule valide
 * @param pg un pointeur vers une grille valide
 * @attention Il faut que la grille *pg soit vide au centre.
 */
void premiere_cellule(cell c, grid* pg);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne 1 si la case (x,y) n'est pas occupée, 0 sinon */
/**
 * @brief Teste si la case (x,y) de la grille est occupée ou non.
 * 
 * @param g une grille valide
 * @param x
 * @param y 
 * @return 1 si la case (x,y) n'est pas occupée,
 *         0 sinon.
 */
int est_libre(grid g, int x, int y);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : libère la mémoire associée à la grille *pg */
/**
 * @brief Libère la mémoire associée à la grille *pg.
 * 
 * @param pg est un pointeur valide vers une grille valide.
 */
void free_grille(grid* pg);

/*  @requires : pg est un pointeur valide vers une grille valide, c est une cellule valide
    @assigns  : *pg
    @ensures  : place la cellule c sur la case (x,y) de la grille si la case n'est pas occupée, retourne 1 le cas échéant. retourne 0 sinon */
/**
 * @brief Modifie *pg en plaçant la cellule c sur la case (x,y) de la grille si la case n'est pas occupée.
 * 
 * @param c est une cellule valide
 * @param pg est un pointeur valide vers une grille valide
 * @param x 
 * @param y 
 * @return 1 en cas de succès,
 *         0 en cas d'échec.
 */
int placer_cell(cell c, grid* pg, int x, int y);

//INFO SUR LA CELLULE

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la cellule située aux coordonnées (x,y) de la grille g ; s'il n'y a pas de cellule, renvoie la NULL*/
/**
 * @brief Obtention de la cellule aux coordonnées (x,y) de la grille g.
 * 
 * @param g une grille valide
 * @param x abscisse de la cellule à obtenir
 * @param y ordonnée de la cellule à obtenir
 * @return la cellule située aux coordonnées (x,y) de la grille g,
 *         s'il n'y a pas de cellule, renvoie la NULL
 */
cell get_cell(grid g, int x, int y);

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case le plus éloignée du centre dans la direction d de la grille g*/
/**
 * @brief Permet de connaître la taille de la grille.
 * 
 * @param d une direction
 * @param g une grille valide
 * @return la coordonnée de la case la plus éloignée du centre dans une direction @b d de la grille @b g.
 */
int taille_direction(direction d, grid g);

/*  @requires : g est une grille valide, d = west ou east
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case la plus éloignée du centre dans la direction d de la ligne i de la grille g */
/**
 * @brief Permet de connaître les coordonnées les plus extrêmes d'une ligne de la grille
 * 
 * @param d west ou east
 * @param g une grille valide
 * @param i l'indice de la ligne
 * @return la coordonnée de la case la plus éloignée du centre dans la direction @b d de la ligne @b i de la grille @b g.
 */
int taille_ligne_direction(direction d, grid g, int i);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : déplace la cellule située aux coordonnées (x1,y1) de la grille *pg (remplacée par la cellule nulle) vers les coordonnées (x2, y2),
    retourne 0 le cas échéant.
    retourne -1 si problème sur la case de départ (x1, y1)
    retourne 1 si problème sur la case d'arrivée (x2, y2)*/
/**
 * @brief Modifie @b *pg en déplaçant la cellule de @b (x1,y1) en @b (x2, y2).
 * 
 * @param pg pointeur valide vers une grille valide
 * @param x1 abscisse de la cellule de départ
 * @param y1 ordonnée de la cellule de départ
 * @param x2 abscisse de la cellule d'arrivée
 * @param y2 ordonnée de la cellule d'arrivée
 * @return 0 en cas de succès,
 *         -1 s'il y a un problème sur la case de départ,
 *         1 s'il y a un problème sur la case d'arrivée.
 */
int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2);

/*  @requires : pg est un pointeur valide vers une grille valide
    @assigns  : *pg
    @ensures  : supprime la cellule de la grille située aux coordonnées (x,y) de la grille *pg (remplacée par la cellule nulle), retourne 1 le cas échéant. retourne 0 sinon (pas de cellule ou cellule déjà supprimée) */
/**
 * @brief Modifie *pg en supprimant la cellule située aux coordonnées @b (x,y)
 * 
 * @param pg pointeur valide vers une grille valide 
 * @param x abscisse de la cellule à supprimer
 * @param y ordonnée de la cellule à supprimer
 * @return 1 en cas de succès,
 *         0 sinon (pas de cellule ou cellule déjà supprimée)
 */
int supp_cell_grille(grid* pg, int x, int y);

/*--------------------------------- Liste chainée ---------------------------------*/
/**
 * @typedef liste 
 * @brief Structure de liste chaînée. Pointeur vers la structure de maillons. Ses éléments sont de type abstrait @b elt , 
 */
typedef struct bucket *liste;

/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne une liste vide */
/**
 * @brief Créé une liste vide.
 * @return Liste vide.
 */
liste cree_liste_vide();

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne 1 si l est vide et 0 sinon */
/**
 * @brief Teste si la liste est vide.
 * 
 * @param l la liste à tester.
 * @return 1 si @b l est vide,
 *         0 sinon
 */
int test_vide(liste l);

/*  @requires : pl est un pointeur valide vers une liste valide
    @assigns  : *pl
    @ensures  : ajoute e au dessus de la liste *pl */
/**
 * @brief Modifie *pl en ajoutant lui un élément @b e .
 * 
 * @param e l'élément à ajouter
 * @param pl pointeur valide vers une liste valide, celle dont on veut ajouter l'élément.
 */
void push(elt e, liste* pl);

/*  @requires : pl est un pointeur valide vers une liste valide non-vide
    @assigns  : *pl
    @ensures  : retourne l'élément en haut de la liste et le retire de la liste*/
/**
 * @brief Modifie @b *pl en retirant l'élément en haut de la liste.
 * 
 * @param pl pointeur valide vers une liste valide non vide.
 * @attention plante si @b *pl est vide.
 * @return l'élément au dessus de la liste.
 */
elt pop(liste* pl); // = tirer une carte;

/*  @requires : l est une liste valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément en haut de la liste */
/**
 * @brief Renvoie l'élément en haut de la liste
 * 
 * @param l liste valide non-vide.
 * @attention plante si @b *pl est vide.
 * @return l'élément au dessus de la liste.
 */
elt peek(liste l);

/*  @requires : l est une liste valide, e est un élément valide
    @assigns  : nothing
    @ensures  : teste si e est dans la liste l et retourne son indice de première occurence (de 0 à len_liste(l)-1) dans la liste le cas échéant, -1 sinon */
/**
 * @brief Recherche d'élément dans une liste
 * 
 * @param e l'élément à rechercher
 * @param l liste valide
 * @return l'indice de première occurence de @b e dans @b l (indexé de @a 0 à @a len_liste(l)-1 )
 *         -1 si @b e n'est pas dans @b l .
 */
int find(elt e, liste l);

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne le nombre d'éléments dans la liste */
/**
 * @brief Longueur de liste
 * 
 * @param l liste valide
 * @return Nombre d'éléments dans la liste @b l .
 */
int len_liste(liste l);

/*  @requires : pl est un pointeur valide vers une liste valide
    @assigns  : *pl
    @ensures  : supprime la première occurence de l'élément e de la liste, retourne 1 le cas échéant, 0 sinon*/
/**
 * @brief Modifie @b *pl en retirant la première occurence de @b e dans @b l .
 * 
 * @param e élément à supprimer de @b *pl .
 * @param pl pointeur valide vers une liste valide
 * @return 1 en cas de succès,
 *         0 en cas d'échec. 
 */
int enlever(elt e, liste* pl);

/*  @requires : l est une liste valide, 0 <= pos < len_liste(l)
    @assigns  : nothing
    @ensures  : renvoie l'élement de la liste l situé à la position pos, l est indexé de 0 à len_liste(l)-1 */
/**
 * @brief Obtention de l'élément à la position @b pos de la liste
 * 
 * @param pos position de la valeur voulu dans la liste, compris entre 0 (inclus) et @a len_liste(l) (exclus)
 * @param l liste valide
 * @return l'élement de la liste l situé à la position pos, (indexé de @a 0 à @a len_liste(l)-1 )
 *         @b NULL si la valeur @b pos est trop grande.
 */
elt get_at(int pos, liste l);

/*  @requires : l est une liste valide
    @assigns  : nothing
    @ensures  : retourne une liste qui contient les éléments de l mais mélangées */
/**
 * @brief Mélange des éléments d'une liste.
 * 
 * @param l liste valide.
 * @return une nouvelle liste qui contient les éléments de l mais mélangées.
 */
liste melanger(liste l);


#endif