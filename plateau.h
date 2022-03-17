#ifndef PLATEAU_H
#define PLATEAU_H

#include "carte.h"
#include "faction.h"

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
@ensures: affiche l'état du jeu (factions)
*/
void affiche_factions(faction *f1,faction *f2);

/*
@requires: carte valide
@assigns: faction*
@ensures: pioche une carte à jouer (cachée)
*/
void carte_faction(faction*);

/*
@requires: carte valide
@assigns: carte
@ensures: retourne une carte face visible et activer son effet
*/

carte_base active_carte(faction);

#endif
