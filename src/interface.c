
#ifndef INTERFACE_H
#define INTERFACE_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
/*Obtention des types carte, faction et plateau*/
#include "../header/carte.h"
#include "../header/faction.h"
#include "../header/plateau.h"
#include "../header/structure.h"


/*@requires : line_length >0
@assigns    : nothing
@ensures    : affiches le caractere '_' line_length fois*/
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
    faction faction1;
    faction faction2;
    liste_faction l_fact =retourne_factions(p);
    //TODO PCQ PAS FINI STRUCT LISTE_FACTION
    for(i=max_south; i>=max_north; i+=1){
        print_ligne(max_east-max_west);
        print("\n");
        for(j=max_west;j<=max_east;j+=1) {
            putchar('|');
            
            switch ( cachee_visible_existe(p,i,j)) {

                case 0: {
                    cell cell_to_print= get_cell(p,i,j);
                    int num_faction= get_card_faction(cell_to_print);
                    if(num_faction==1){
                        printf("\033[0;31m");
                        printf("%4s","X");
                        printf("\033");
                    }
                    else {
                        printf("%4s","X");
                    }
                }
                break;
                case 1:
                case 2:{
                    cell cell_to_print= get_cell(p,i,j);
                    carte card_to_print= get_card(*cell_to_print);
                    int num_faction= get_card_faction(cell_to_print);

                    char * name_card= get_carte_nom(card_to_print);
                    if(num_faction==1) {
                        printf("\033[0;31m");
                        printf("%4s",name_card);
                        printf("\033"); 
                    }
                    else{
                        printf("%4s",name_card);
                    }
                }
                break;
                default: {
                    printf("%4s","");

                }
            


/* 
            if (cachee_visible_existe(p,i,j)==3) { //TODO PAS SUR du &card_to_print
                printf("%4s","");
            }
            cell cell_to_print= get_cell(p,i,j);
            carte card_to_print= get_card(*cell_to_print);
            
            int num_faction= get_card_faction(cell_to_print);
            if (get_visible(*cell_to_print) == 0 ) {

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
                char * name_card= get_carte_nom(card_to_print);
                if(num_faction==1) {
                    printf("\033[0;31m");
                    printf("%4s",name_card);
                    printf("\033"); 
                }
                else{
                    printf("%4s",name_card);

                }
            }
 */
            }
        
        }
        printf("|\n");

        putchar("|");
    }

}

/*@requires : f est valide
@assigns    : nothing
@ensures    : affiche la main de f*/
void affiche_main(faction f) {
    printf("\n Voici votre main: \n");
    liste main_f= get_main(f);
    int cpt; // Compteur pour la taille de la main (pour afficher en dessous l'indice de la carte)
    cpt=0;
    while (test_vide(main_f)==0) {
        printf("|");
        cpt+=1;
        carte card_to_print= pop(&main_f); //pas sur d'avoir compris comment fonctionnait la liste chainée
        char * name_card= get_carte_nom(card_to_print);
        printf("%4s",name_card);
    }
    printf("| \n");
    int i;
    for(i=1;i<=cpt; i+=1) {
        printf("|");
        printf("%4i",i);
    }
    printf("| \n");
}

/*@requires : f est valide, les cartes de f ont été piochées, already = O ou 1 (1 si la faction a déjà utilisé l'option)
@assigns    : nothing
@ensures    : si already==1, alors renvoie 0, sinon si already == 0, demande à f une des actions suivantes, et renvoie la valeur associée :
    0. conserve sa main
    1. vide sa main, mélange la pioche, repioche sa nouvelle main*/
int mulligan_main(faction f, int already){
    if (1==already){
        return 0;
    }
    printf("\nVous pouvez, si vous le souhaitez vider votre main, mélanger la pioche et repiocher une nouvelle main. \n");
    printf("Pour rappel, voux ne pouvez utiliser cette option qu'une seule fois dans toute la partie\n");
    printf("Souhaitez vous utiliser cette option? (y/n)");
    char answer;
    scanf("%s",answer);

    while(!(answer=='y'|| answer=='n')){
        printf("Souhaitez vous utiliser cette option? (y/n)");
        scanf("%s",answer);
    }
    if (answer=='n'){
        return 0;
    }
    return(1);
}

/*@requires : f est valide
@assigns    : nothing
@ensures    : demande à f la carte qu'elle souhaite poser sur le plateau et la retourne*/
carte choix_carte(faction f){
    liste main_f= get_main(f);

    printf("\n Quelle carte voulez vous poser?");

}

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