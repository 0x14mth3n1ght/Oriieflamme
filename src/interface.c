
#ifndef INTERFACE_H
#define INTERFACE_H

/*Obtention des types carte, faction et plateau*/
#include "../header/carte.h"
#include "../header/faction.h"
#include "../header/plateau.h"
#include "../header/structure.h"

/*@requires : p est un plateau valide
@assigns    : nothing
@ensures    : affiche p*/
void print_ligne(int line_length) {
    char c = '_';
    int count = line_length;
    for (int i = 0; i < count; i ++) {
        putchar(c);
        }
}

/*@requires : p est un plateau valide
@assigns    : nothing
@ensures    : affiche p*/
void affiche_plateau(plateau p) {
    int max_north = taille_north(p);
    int max_south =taille_south(p);
    int max_west = taille_west(p);
    int max_east = taille_east(p);
    int i,j;

    for(i=max_north; i>=max_south; i-=1){
        print_ligne(max_east-max_west);
        print("\n");
        for(j=max_west;j<=max_east;j+=1) {
            putchar('|');
            cell cell_to_print= get_cell(p,i,j);
            /*
            recup card
            card card_to_print= get_card(cell);
            if (card==null)
                printf("%4s","");

            recup retourné ou nn: Si retourné:
            et a qui appartient
            int num_faction= get_card_faction(cell_to_print)
            (if (get_retourné(cell)) {

                if(num_faction==1){
                    printf("\033[0;31m");
                    printf("%4s","X");
                    printf("\033");
                }
                else {
                    printf("%4s","X");
                }
            }
            else {
                char * name_card= get_card_name(cell)
                if(num_faction==1) {
                    printf("\033[0;31m");
                    printf("%4s",name_card);
                    printf("\033"); 
                }
                else{
                    printf("%4s",name_card);

                }
            }
            printf("|\n") */

        }
        putchar("|");
    }

}

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

/*@requires : f est valide, pos est un tableau d'entiers positifs de taille 2
@assigns    : pos
@ensures    : demande à f les coordonnées (x,y) de l'endroit où elle souhaite poser la carte. Les coordonnées seront stockées dans le tableau pos = [x,y]*/
void position_carte(faction f, int* pos);

/*@requires : c est valide
@assigns    : nothing
@ensures    : affiche les effets d'une carte c (qui vient d'être retournée sur le plateau)*/
void affiche_effet(carte c);

/*@requires : f1 et f2 valides
@assigns    : nothing
@ensures    : affiche le vainqueur de la partie et retourne 1 ou 2 le numéro de la faction gagnante*/
int affiche_gagnant(faction f1, faction f2);

#endif