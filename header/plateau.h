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
   /* indique si une carte est posee sur cette case */
   int occupee;
   /* indique si la carte est retournee */
   int visible;
   /* indique si l'effet de la carte est active */
   int activee;
};

typedef struct cell_base * cell;

/**
* \brief une fonction sans argument
* \attention alloue de la memoire
* \return retourne un plateau vide
*/
plateau cree_plateau();

/**
* \brief procedure qui detruit un plateau
* \param p un pointeur valide vers le plateau a detruire
* \attention libere la memoire associee au plateau
* \return rien
*/
void detruire_plateau(plateau *p);

/**
* \brief fonction qui réinitialise le jeu en vidant le plateau et la main des deux factions 
* et mélange la pioche des deux factions et fait repiocher les deux factions,
* et donc initialise une nouvelle manche du jeu. Le cas échéant, indique que le jeu est terminé 
* \param p un pointeur valide vers le plateau
* \return retourne l'entier 1 si réinitialisation, 0 si partie terminee
*/
int reinitialisation(plateau *p);

/**
* \brief procedure permettant de connaitre les deux factions du jeu 
* \param p le plateau
* \param pf1 pointeur vers une faction valide
* \param pf2 pointeur vers une faction valide
* \return rien
*/
void retourne_factions(plateau p, faction *pf1, faction *pf2);

/**
* \brief fonction qui place sur le plateau une carte à jouer face cachée et retire cette carte 
* de la main de la faction
* \attention la faction doit posséder au moins un exemplaire de cette carte
* \param p pointeur valide vers le plateau 
* \param fac pointeur valide vers la faction a qui appartient la carte a poser
* \param car la carte a poser
* \param x
* \param y (x et y coordonnes valides de la case sur laquelle on pose la carte)
* \attention la case doit etre inocuppee, la faction doit exister
* \return 1 si le placement a bien ete effectue et 0 sinon
*/
int pose_carte(plateau *p, faction *fac, carte car, int x, int y);

/**
* \brief fonction qui retourne sur le plateau une carte à jouer face visible sans l'activer
* \param p pointeur valide vers le plateau 
* \param x
* \param y (x et y coordonnes valides de la case sur laquelle se situe la carte à retourner)
* \attention la case doit etre occuppee, la faction doit exister, la carte doit etre face cachée avant 
* l'appel de la fonction 
* \return 1 si la carte a bien ete retournee et 0 sinon
*/
int retourne_carte(plateau *p, int x, int y);

/**
* \brief fonction pour retourner la carte la plus en haut à gauche face visible et activer son effet
* \param p un pointeur vers plateau valide
* \attention retourne une carte seulement s'il reste au moins une carte non retournee sur le
* plateau avant l'activation de la fonction
* \return retourne la carte retournee et activee
*/
carte active_carte(plateau *p);

/**
* \brief fonction qui permet de connaitre l'etat d'une carte sur une cellule donnee
* \param p pointeur vers plateau valide
* \param x
* \param y x et y sont les coordonnees
* \return 0 si la carte est face cachee, 1 si face visible seulement,
* 2 si face visible et activee, 3 s'il n'y a pas de carte a cet endroit
*/
int cachee_visible_existe(plateau *p, int x, int y);

/**
* \brief fonction qui retourne la carte posee une certaine cellule
* \param cellule la cellule en question
* \attention ne retourne une carte que s'il existe effectivement une carte sur cette cellule
*/
carte get_card(cell cellule);

/**
* \brief fonction permettant de connaitre la faction a laquelle appartient une carte posee sur une cellule
* \param cellule la cellule
* \return la faction a laquelle appartient la carte posee sur la cellule
*/
faction get_faction(cell cellule);

/**
* \brief fonction qui permet de savoir si une cellule donne est occupee par une carte
* \param cellule la cellule
* \return retourne 1 si la cellule est occupee et 0 sinon
*/
int get_occupee(cell cellule); 

/**
* \brief fonction qui permet de savoir si une carte sur une cellule donnee est face visible
* \param cellule la cellule en question 
* \return 1 si la carte a cet endroit est visible, 0 sinon
*/
int get_visible(cell cellule);

/**
* \brief fonction qui permet de savoir si une carte sur une cellule donnee est face visible et activee
* \param cellule la cellule en question 
* \return 1 si la carte a cet endroit est visible et activee, 0 sinon
*/
int get_activee(cell cellule);

/**
* \brief fonction retournant la grille associee a un plateau
* \param p le plateau
* \return la grille associee
*/
grid get_grid(plateau p);

/**
* \brief fonction permettant de connaitre le nombre de carte posees sur le plateau 
* \param p le plateau 
* \return le nombre de cartes posees sur le plateau
*/
int get_nb_cartes_posees(plateau p);

/**
* \brief fonction permettant de connaitre le nombre de carte visibles sur le plateau 
* \param p le plateau 
* \return le nombre de cartes visibles sur le plateau
*/
int get_nb_cartes_visibles(plateau p);

/**
* \brief fonction permettant de connaitre le nombre de carte activees sur le plateau 
* \param p le plateau 
* \return le nombre de cartes activees sur le plateau
*/
int get_nb_cartes_activees(plateau p);

/**
* \brief procédure initialisant nb_cartes_posees à une certaine valeur
* \param p pointeur valide vers plateau
* \param n la nouvelle valeur positive ou nulle
* \return rien 
*/
void set_nb_cartes_posees(plateau *p, int n);

/**
* \brief procédure initialisant nb_cartes_visibles à une certaine valeur
* \param p pointeur valide vers plateau
* \param n la nouvelle valeur positive ou nulle
* \return rien 
*/
void set_nb_cartes_visibles(plateau *p, int n);

/**
* \brief procédure initialisant nb_cartes_activees à une certaine valeur
* \param p pointeur valide vers plateau
* \param n la nouvelle valeur positive ou nulle
* \return rien 
*/
void set_nb_cartes_activees(plateau *p, int n);

/**
* \brief fonction permettant de récupérer les cartes visibles sur le plateau
* \param p le plateau 
* \return la liste des cartes visibles sur le plateau
*/
liste get_cartes_visibles(plateau p);

/**
* \brief fonction permettant de récupérer les cartes activees sur le plateau
* \param p le plateau 
* \return la liste des cartes activees sur le plateau
*/
liste get_cartes_activees(plateau p);

/**
* \brief fonction permettant de savoir le nombre de fois où la carte ALL a été retournéee
* \param p le plateau 
* \return le nombre de fois où la carte ALL a été retournéee
*/
int get_ALL(plateau p);

/**
* \brief procédure permettant de fixer une certaine valeur pour le nombre 
* de fois où la carte ALL a été retournée 
* \param p un pointeur vers le plateau 
* \param n nombre de fois où la carte ALL a été retournée (positif ou nul)
* \return rien
*/
void set_ALL(plateau *p, int n);

#endif
