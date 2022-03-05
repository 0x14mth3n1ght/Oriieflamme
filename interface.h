#ifndef INTERFACE_H
#define INTERFACE_H

/*@requires : p est un plateau valide
@assigns    : nothing (???)
@ensures    : affiche p (wip)
*/
void show_board(plateau p);

/*@requires : f est valide
@assigns    : nothing (???)
@ensures    : affiche la main de f
*/
void show_hand(faction f);

/*@requires : f est valide, les cartes de f ont été piochées, already = O ou 1 (1 si la faction a déjà utilisé l'option)
@assigns    : nothing (???)
@ensures    : demande à f une des actions suivantes, et si already = 0, renvoie la valeur associée :
    0. conserve sa main
    1. vide sa main, mélange la pioche, repioche sa nouvelle main
*/
int mulligan_hand(faction f, int already);

/*@requires : f est valide
@assigns    : nothing (???)
@ensures    : demande à f la carte qu'elle souhaite poser sur le plateau, retourne la valeur (comprise entre 0 et 7, la position étant fixée au début de la manche)
*/
int choose_card(faction f);

/*@requires : f est valide, pos est un tableau de taille 2, pos est un tableau d'entiers positifs de taille 2
@assigns    : pos
@ensures    : demande à f les coordonnées (x,y) de l'endroit où elle souhaite poser la carte c. Les coordonnées seront stockées dans le tableau pos = [x,y]
*/
void position_card(faction f, carte c, int* pos);

/*@requires : c est valide
@assigns    : nothing (???)
@ensures    : affiche les effets d'une carte c (qui vient d'être retournée sur le plateau)
*/
void show_effect(carte c);

/*@requires : won_games est le tableau de int représentant le nombre de manche gagnées par chaque faction, de taille size
@assigns    : nothing (???)
@ensures    : affiche le vainqueur de la partie (et le retourne)
*/
int show_winner(int* won_games, int size);

#endif