#ifndef INTERFACE_H
#define INTERFACE_H

/*Obtention des types carte, faction et plateau*/
#include "carte.h"
#include "faction.h"
#include "plateau.h"

/*@requires : p est un plateau valide
@assigns    : nothing
@ensures    : affiche p*/
void affiche_plateau(plateau p);

/*@requires : f est valide
@assigns    : nothing
@ensures    : affiche la main de f*/
void affiche_main(faction f);

/*@requires : f est valide, les cartes de f ont été piochées, already = O ou 1 (1 si la faction a déjà utilisé l'option)
@assigns    : nothing
@ensures    : si already==1, alors renvoie 0, sinon si already == 0, demande à f une des actions suivantes, et renvoie la valeur associée :
    0. conserve sa main
    1. vide sa main, mélange la pioche, repioche sa nouvelle main*/
int mulligan_main(faction f, int already);

/*@requires : f est valide
@assigns    : nothing
@ensures    : demande à f la carte qu'elle souhaite poser sur le plateau*/
carte choix_carte(faction f);

/*@requires : f est valide, pos est un tableau de taille 2, pos est un tableau d'entiers positifs de taille 2
@assigns    : pos
@ensures    : demande à f les coordonnées (x,y) de l'endroit où elle souhaite poser la carte. Les coordonnées seront stockées dans le tableau pos = [x,y]*/
void position_carte(faction f, int* pos);

/*@requires : c est valide
@assigns    : nothing
@ensures    : affiche les effets d'une carte c (qui vient d'être retournée sur le plateau)*/
void affiche_effet(carte c);

/*@requires : won_rounds est le tableau de int représentant le nombre de manche gagnées par chaque faction, de taille size
@assigns    : nothing
@ensures    : affiche le vainqueur de la partie (et retourne l'indice du vainqueur dans won_rounds)*/
int affiche_gagnant(int* won_rounds, int size);

#endif