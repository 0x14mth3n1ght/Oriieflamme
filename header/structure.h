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


/**
 * @brief Modifie @b *pg en ajoutant la cellule @b c au centre (aux coordonnées @b (0,0) ).
 * 
 * @param c une cellule valide
 * @param pg un pointeur vers une grille valide
 * @attention Il faut que la grille *pg soit vide au centre.
 */
void premiere_cellule(cell c, grid* pg);

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

/**
 * @brief Libère la mémoire associée à la grille @b *pg.
 * 
 * @param pg est un pointeur valide vers une grille valide.
 */
void free_grille(grid* pg);

/**
 * @brief Modifie @b *pg en plaçant la cellule @b c sur la case @b (x,y) de la grille si la case n'est pas occupée.
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

/**
 * @brief Obtention de la cellule aux coordonnées @b (x,y) de la grille @b g.
 * 
 * @param g une grille valide
 * @param x abscisse de la cellule à obtenir
 * @param y ordonnée de la cellule à obtenir
 * @return la cellule située aux coordonnées @b (x,y) de la grille @b g,
 *         s'il n'y a pas de cellule, renvoie @b NULL
 */
cell get_cell(grid g, int x, int y);

/**
 * @brief Permet de connaître la taille de la grille.
 * 
 * @param d une direction
 * @param g une grille valide
 * @return la coordonnée de la case la plus éloignée du centre dans une direction @b d de la grille @b g.
 */
int taille_direction(direction d, grid g);

/**
 * @brief Permet de connaître les coordonnées les plus extrêmes d'une ligne de la grille
 * 
 * @param d direction
 * @param g une grille valide
 * @param j l'indice de la ligne
 * @return la coordonnée de la case la plus éloignée du centre dans la direction @b d de la ligne @b j de la grille @b g.
 */
int taille_ligne_direction(direction d, grid g, int j);

/**
 * @brief Modifie @b *pg en déplaçant la cellule de @b (x1,y1) en @b (x2,y2).
 * 
 * @param pg pointeur valide vers une grille valide
 * @param x1 abscisse de la cellule de départ
 * @param y1 ordonnée de la cellule de départ
 * @param x2 abscisse de la cellule d'arrivée
 * @param y2 ordonnée de la cellule d'arrivée
 * @return @b 0 en cas de succès,
 *         @b -1 s'il y a un problème sur la case de départ,
 *         @b 1 s'il y a un problème sur la case d'arrivée.
 */
int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2);

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

/**
 * @brief Créé une liste vide.
 * @return Liste vide.
 */
liste cree_liste_vide();

/**
 * @brief Teste si la liste est vide.
 * 
 * @param l la liste à tester.
 * @return 1 si @b l est vide,
 *         0 sinon
 */
int test_vide(liste l);

/**
 * @brief Modifie *pl en lui ajoutant un élément @b e .
 * 
 * @param e l'élément à ajouter
 * @param pl pointeur valide vers une liste valide, celle dont on veut ajouter l'élément.
 */
void push(elt e, liste* pl);

/**
 * @brief Modifie @b *pl en retirant l'élément en haut de la liste.
 * 
 * @param pl pointeur valide vers une liste valide non vide.
 * @attention plante si @b *pl est vide.
 * @return l'élément au dessus de la liste.
 */
elt pop(liste* pl); // = tirer une carte;

/**
 * @brief Renvoie l'élément en haut de la liste
 * 
 * @param l liste valide non-vide.
 * @attention plante si @b l est vide.
 * @return l'élément au dessus de la liste.
 */
elt peek(liste l);

/**
 * @brief Recherche d'élément dans une liste
 * 
 * @param e l'élément à rechercher
 * @param l liste valide
 * @return l'indice de première occurence de @b e dans @b l (indexé de @a 0 à @a len_liste(l)-1 ),
 *         @b -1 si @b e n'est pas dans @b l .
 */
int find(elt e, liste l);

/**
 * @brief Longueur de liste
 * 
 * @param l liste valide
 * @return Nombre d'éléments dans la liste @b l .
 */
int len_liste(liste l);

/**
 * @brief Modifie @b *pl en retirant la première occurence de @b e dans @b *pl .
 * 
 * @param e élément à supprimer de @b *pl .
 * @param pl pointeur valide vers une liste valide
 * @return @b 1 en cas de succès,
 *         @b 0 en cas d'échec. 
 */
int enlever(elt e, liste* pl);

/**
 * @brief Obtention de l'élément à la position @b pos de la liste
 * 
 * @param pos position de la valeur voulu dans la liste, compris entre 0 (inclus) et @a len_liste(l) (exclus)
 * @param l liste valide
 * @return l'élement de la liste @b l situé à la position @b pos, (indexé de @a 0 à @a len_liste(l)-1 )
 *         @b NULL si la valeur @b pos est trop grande.
 */
elt get_at(int pos, liste l);

/**
 * @brief Mélange des éléments d'une liste.
 * 
 * @param l liste valide.
 * @return une nouvelle liste qui contient les éléments de @b l mais mélangées.
 */
liste melanger(liste l);

/**
 * @brief Libère la mémoire allouée à la liste.
 * 
 * @param pl pointeur valide vers une liste valide, celle dont on cherche à allouer la mémoire.
 */
void free_liste(liste* pl);

/**
 * @brief Nombre d'occurence de l'élément @b e dans @b l
 * 
 * @param l liste valide.
 * @return le nombre d'occurence de l'élément @b e dans @b l
 */
int nb_elt(elt e, liste l);

#endif