#ifndef STRUCTURE_H
#define STRUCTURE_H

/*Obtention des types*/
#include "carte.h"
#include "faction.h"
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
int supprime_carte_plateau(plateau *pg, int x, int y);

/*--------------------------------- Cartes en main ---------------------------------*/
typedef carte* carteEnMain; /*Tableau 1D de cartes ; un emplacement vide sera caractérisé par la carte nulle*/

/*  @requires : cmain tableau de taille size
    @assigns  : cmain
    @ensures  : initialise une main vide composée de size cartes */
void main_vide(carteEnMain cmain, int size);

/*  @requires : cmain tableau de taille size
    @assigns  : cmain
    @ensures  : rajoute la carte c à la main cmain si elle n'est pas pleine, renvoie sa position dans cmain le cas échéant. renvoie 0 si la main était pleine */
int ajout_carte(carte c, carteEnMain cmain, int size);

/*  @requires : cmain tableau de taille size
    @assigns  : nothing
    @ensures  : teste si la carte c est dans la main cmain, renvoie la position de la premiere occurence de la carte le cas échéant. renvoie -1 sinon */
int indice_carte_main(carte c, carteEnMain cmain, int size); //sert de mem

/*  @requires : cmain tableau de taille size
    @assigns  : cmain
    @ensures  : supprime la première occurence de la carte c de la main cmain et décale l'indice des cartes de sorte à ne pas avoir de carte nulle entre deux cartes non-nulles, renvoie 1 le cas échéant. renvoie 0 si la carte n'était pas dans la main */
int supprime_carte_main(carte c, carteEnMain cmain, int size);

/*  @requires : cmain tableau de taille size, 0 <= pos < size
    @assigns  : nothing
    @ensures  : renvoie la carte de la main cmain située à la position pos, renvoie la carte nulle s'il n'y a plus de carte à la position pos */
carte get_carte_at(int pos, carteEnMain cmain, int size);

/*--------------------------------- Pioche : liste chainee ---------------------------------*/
typedef struct bucket *pioche;

/*  @requires : nothing
    @assigns  : nothing
    @ensures  : retourne une pioche vide */
pioche cree_pioche_vide();

/*  @requires : p est une pioche valide
    @assigns  : nothing
    @ensures  : retourne 1 si p est vide et 0 sinon */
int est_vide(pioche p);

/*  @requires : pp est un pointeur valide vers une pioche valide
    @assigns  : *pp
    @ensures  : ajoute c au dessus de la pioche *pp */
void push(carte c, pioche* pp);

/*  @requires : pp est un pointeur valide vers une pioche valide non-vide
    @assigns  : *pp
    @ensures  : retourne la carte en haut de la pioche et la retire de la pioche*/
carte pop(pioche* pp); // = tirer une carte;

/*  @requires : p est une pioche valide
    @assigns  : nothing
    @ensures  : retourne la carte en haut de la pioche */
carte peek(pioche p);

/*  @requires : p est une pioche valide, c est une carte valide
    @assigns  : nothing
    @ensures  : retourne 1 si c est dans la pioche p, 0 sinon */
int mem_pioche(pioche p, carte c);

/*  @requires : p est une pioche valide
    @assigns  : nothing
    @ensures  : retourne le nombre d'éléments dans la pioche */
int pioche_len(pioche p);

#endif