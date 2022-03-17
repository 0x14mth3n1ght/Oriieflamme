#ifndef PLATEAU_H
#define PLATEAU_H

#include "carte.h"

/* Pile pour définir le tableau*/

typedef int valeur;

typedef struct pile pile;

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne une pile vide
*/
pile pile_vide();

/*
@requires: nothing
@assigns: nothing
@ensures: Retourne vrai ssi la pile est vide
*/
int est_vide(pile);

/*
@requires: nothing
@assigns: pile
@ensures: Ajoute la valeur sur le dessus de la pile
*/
void empiler(pile*, valeur);

/*
@requires: pile non vide
@assigns: pile
@ensures: Supprime et retourne l'élément au sommet de la pile
*/
int depiler(pile*);

/*
@requires: pile non vide
@assigns: nothing
@ensures: Retourne l'élément au sommet de la pile
*/
int retourner_sommet(pile);

/*
@requires: nothing
@assigns: nothing
@ensures: Affiche la pile
*/
void afficher_pile(pile);

/*
Interface à proprement parler :

un type plateau (possiblement abstrait)
une fonction pour créer un nouveau plateau (et les deux factions qui joueront dessus)
une fonction pour libérer la mémoire associée à un plateau (et ses deux factions)
une fonction pour initialiser une nouvelle manche du jeu, ou, le cas échéant, indiquer que le jeu est terminé
une fonction qui renvoie la liste des deux factions du jeu
une fonction pour permettre à une faction de poser une carte face cachée sur le plateau
une fonction pour retourner une carte face visible et activer son effet
*/

/* Type abstrait d'un plateau de jeu (pile pour la grille et taille ) */
typedef struct plateau plateau;

typedef int faction;

/*
@requires: nothing
@assigns: nothing
@ensures: Initialise un plateau vide
*/
plateau creer_plateau(int taille);

/*
@requires: mat has size m
@assigns: nothing
@ensures: libère la mémoire associée au plateau*/
void detruire_plateau(plateau);

/*
@requires: nothing
@assigns: plateau
@ensures: réinitialise le jeu ou indique s'il est terminé
*/
void reinitialisation(plateau*);

/*
@requires: nothing
@assigns: nothing
@ensures: choisit le coup du joueur et place ses coordonnées dans ligne, colonne
*/
void affiche_factions(faction f1,faction f2);

/*
@requires: ligne et colonne adresses valides
@assigns: ligne, colonne
@ensures: choisit la carte du joueur et place ses coordonnées dans ligne, colonne
*/
void coup_faction(int* ligne, int* colonne);

/*
@requires: carte valide
@assigns: carte
@ensures: retourne une carte face visible et activer son effet
*/

carte_base active_carte(faction);

#endif
