#ifndef STRUCTURE_H
#define STRUCTURE_H
/**
 * @file structure.h
 * @brief Mise en place de structures de grille et de liste chaînée.
 * 
 */

/*Obtention des types*/
#include "carte.h"

/*----------- Grille du plateau -----------*/
/**
 * @typedef cell
 * @brief Type abstrait des cases de la grille
 * 
 */
typedef struct cell_base * cell;

/**
 * @typedef grid
 * @brief Pointeur vers la structure de grille
 */
typedef cell** grid;

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
 * @return une grille vide (toutes les cellules sont nulles).
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
 * @return l'indice d'une case remplie, celle située la plus loin dans la direction @b d de la grille @b g.
 */
int taille_grille(direction d, grid g);

/**
 * @brief Permet de connaître les coordonnées les plus extrêmes d'une ligne de la grille
 * 
 * @param d direction
 * @param g une grille valide
 * @param j l'indice de la ligne
 * @return l'indice d'une case remplie, celle située la plus loin dans la direction @b d de la ligne (si @a d = west ou east) ou colonne (si @a d = north ou south) @b n de la grille @b g.
 */
int taille_ligne_direction(direction d, grid g, int n);

/**
 * @brief Modifie @b *pg en déplaçant la cellule de @b (x1,y1) en @b (x2,y2).
 * 
 * @param pg pointeur valide vers une grille valide
 * @param x1 abscisse de la cellule de départ
 * @param y1 ordonnée de la cellule de départ
 * @param x2 abscisse de la cellule d'arrivée
 * @param y2 ordonnée de la cellule d'arrivée
 * @return @b 0 en cas de succès,
 *         @b -1 si la case de départ est vide,
 *         @b 1 si la case d'arrivée est non-vide,
 *         @b 2 si la case de départ est vide et la case d'arrivée est non-vide.
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

/**
 * @brief Met dans @b *p_out la sous-grille de g,
 * où le bord haut-gauche était de coordonnée @b [x1,y1] dans @b g
 * et le bord bas-droit était de coordonnée @b [x2,y2] dans @b g
 * 
 * @param g grille valide, celle qu'on cherche à extraire
 * @param x1 abscisse de la cellule supérieure gauche de la sous-grille
 * @param y1 ordonnée de la cellule supérieure gauche de la sous-grille
 * @param x2 abscisse de la cellule inférieure droite de la sous-grille, x2 > x1
 * @param y2 ordonnée de la cellule inférieure droite de la sous-grille, y2 > y1
 * @return sous-grille bordé par le point (inclus) supérieur gauche @b (x1,y1) et le point (inclus) inférieur droit @b (x2,y2)
 * @attention la sous-grille ne peut pas utiliser les autres fonctions de structure et n'est qu'à but démonstratif
 */
grid sous_grille(grid g, int x1, int y1, int x2, int y2);

/**
 * @return le nombre de lignes de la grille
 */
int get_sizeX();

/**
 * @return le nombre de colonnes de la grille
 */
int get_sizeY();

/*--------------------------------- Liste chainée ---------------------------------*/

//Type des éléments des listes chaînées
typedef void* elt;

/**
 * @typedef liste 
 * @brief Structure de liste chaînée. Pointeur vers la structure de maillons. Ses éléments sont de type abstrait @b elt 
 */
typedef struct bucket* liste;

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
 * @brief Modifie @b *pl en lui ajoutant un élément @b e ssi @b e n'est déjà pas présent dans @b *pl.
 * 
 * @param e la cellule à ajouter
 * @param pl pointeur valide vers une liste valide, celle dont on veut ajouter l'élément.
 */
void push_unique_cell(cell e, liste* pl);

/**
 * @brief Modifie @b *pl en retirant l'élément en haut de la liste.
 * 
 * @param pl pointeur valide vers une liste valide non vide.
 * @attention plante si @b *pl est vide.
 * @return l'élément au dessus de la liste.
 */
elt pop(liste* pl);

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
 * @brief Recherche de cellule dans une liste
 * 
 * @param c la cellule à rechercher
 * @param l liste valide
 * @return l'indice de première occurence de @b c dans @b l (indexé de @a 0 à @a len_liste(l)-1 ),
 *         @b -1 si @b c n'est pas dans @b l .
 */
int find_cell(cell c, liste l);

/**
 * @brief Comparateur de cellule (sans prendre en compte l'état de la carte)
 * @note Sera implémentée dans le fichier implétant concrètement le type cell
 * 
 * @param c1 cellule valide
 * @param c2 cellule valide
 * @return 1 si @b c1 et @b c2 possèdent la même carte, posée par la même faction, aux mêmes coordonnées
 */
int cell_equals(cell c1, cell c2);

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
 *         termine avec une erreur si la valeur @b pos est trop grande.
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

/**
 * @brief Copie de liste
 * 
 * @param l liste valide, celle dont on veut copier
 * @return une copie de la liste (à l'envers)
 */
liste deepcopy(liste l);

/**
 * @brief Comparateur du contenu de liste.
 * 
 * @param l1 liste valide
 * @param l2 liste valide
 * @return @b 1 si @b l1 et @b l2 contiennent les mêmes éléments dans le bon ordre et sont de même taille,
 *         @b 0 sinon.
 */
int liste_equals(liste l1, liste l2);

/**
 * @brief Concaténation de listes
 * 
 * @param l1 liste valide
 * @param l2 liste valide
 * @return liste ayant d'abord les éléments dans l'ordre de @b l1 , puis de @b l2
 */
liste concat(liste l1, liste l2);

void print_liste(liste l);

#endif