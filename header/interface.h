#ifndef INTERFACE_H
#define INTERFACE_H

/*Obtention des types carte, faction et plateau*/
#include "carte.h"
#include "faction.h"
#include "plateau.h"
#include "bot.h"

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
@ensures    : demande à f la carte qu'elle souhaite poser sur le plateau et la retourne*/
carte choix_carte(faction f);

/*@requires : f est valide, x et y des pointeurs valide, called indique si l'utilisateur s'est trompé.
            si called!=0 l'utilisateur s'est trompé. premier=0 si on pose la première carte. p est valide.
@assigns    : pos
@ensures    : demande à f les coordonnées (x,y) de l'endroit où elle souhaite poser la carte. Les coordonnées seront stockées dans x et y*/
void position_carte(faction f, int* x,int* y,int called,int premier, plateau p);

/*@requires : c est valide
@assigns    : nothing
@ensures    : affiche les effets d'une carte c (qui vient d'être retournée sur le plateau)*/
void affiche_effet(carte c);

/*@requires : f1 et f2 valides
@assigns    : nothing
@ensures    : affiche le vainqueur de la partie et retourne 1 ou 2 le numéro de la faction gagnante*/
int affiche_gagnant(faction f1, faction f2);

/*@requires : f1 et f2 valides
@assigns    : nothing
@ensures    : affiche le vainqueur de la manche en cours et retourne 1 ou 2 le numéro de la faction gagnante*/

int affiche_gagnant_manche(faction f1, faction f2);

/**
 * @brief Affiche les emplacements disponibles de @b p pour poser une carte
 * 
 * @param p plateau valide
 */
void print_coordonnees_dispo(plateau p);

/**
 * @brief Demande à l'utilisateur le mode de jeu : joueur vs joueur, joueur vs ordinateur, ou ordinateur vs ordinateur. Choisit ensuite les noms des factions. Modifie dans la mémoire les factions.
 * @param pp pointeur vers un plateau valide
 */
void mode_de_jeu(plateau* pp);

#endif