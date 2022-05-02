#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
/*Obtention des types carte, faction et plateau*/
#include "../header/carte.h"
#include "../header/faction.h"
#include "../header/plateau.h"
#include "../header/structure.h"
#include "../header/interface.h"

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

void affiche_plateau(plateau p) {
    grid g= get_grid(p);
    int max_north= taille_grille(north,g)-1;
    int max_south =taille_grille(south,g)+1;
    int max_west = taille_grille(west,g)-1;
    int max_east = taille_grille(east,g)+1;
    int i,j;
    faction faction1;
    faction faction2;
    retourne_factions(p,&faction1, &faction2);
    printf("  ");
    for(j=max_west;j<=max_east;j+=1) {
        printf("|%6i",j);
    }
    putchar('|');
    printf("\n");

    for(i=max_north; i<=max_south; i+=1){
        print_ligne((max_east-max_west+1)*7+3);
        printf("\n");
        printf("%2i",i);
        for(j=max_west;j<=max_east;j+=1) {
            putchar('|');
            
            switch ( cachee_visible_existe(&p,i,j)) {

                case 0: {
                   /*  cell cell_to_print= get_cell(g,i,j);
                    int num_faction= get_faction_id(get_faction(cell_to_print));
                    if(num_faction==1){
                        printf("\033[0;31m");
                        printf("%4s","X");
                        printf("\033[00m");
                    }
                    else {
                        printf("%4s","X");
                    } */
                    //A SUPRR
                    cell cell_to_print= get_cell(g,i,j);
                    carte card_to_print= get_card(cell_to_print);
                    int num_faction= get_faction_id(get_faction(cell_to_print));

                    char * name_card= get_nom_court(card_to_print);
                    if(num_faction==1) {
                        printf("\033[0;33m");
                        printf("%6s",name_card);
                        printf("\033[00m"); 
                    }
                    else{
                        printf("\033[0;32m");
                        printf("%6s",name_card);
                        printf("\033[00m"); 

                    }
                    // A SUPPR
                }
                break;
                case 1:
                case 2:{
                    cell cell_to_print= get_cell(g,i,j);
                    carte card_to_print= get_card(cell_to_print);
                    int num_faction= get_faction_id(get_faction(cell_to_print));

                    char * name_card= get_nom_court(card_to_print);
                    if(num_faction==1) {
                        printf("\033[0;31m");
                        printf("%6s",name_card);
                        printf("\033[00m"); 
                    }
                    else{
                        printf("%6s",name_card);
                    }
                }
                break;
                default: {
                    printf("%6s","");

                }
            }
        
        }
        printf("|\n");
    }
    printf("\n La faction 1 %s possède %i points ddrs. ",get_faction_nom(faction1),get_ddrs(faction1));
    printf("\n La faction 2 %s possède %i points ddrs. \n",get_faction_nom(faction2),get_ddrs(faction2));
}


void affiche_main(faction f) {
    printf("\n Faction %i Voici votre main: \n",get_faction_id(f));
    liste main_f= get_main(f);
    int cpt; // Compteur pour la taille de la main (pour afficher en dessous l'indice de la carte)
    cpt=0;
    while (test_vide(main_f)==0) {
        printf("|");
        cpt+=1;
        carte card_to_print= pop(&main_f);
        char * name_card= get_nom_court(card_to_print);
        printf("%4s",name_card);
    }
    printf("| \n");
    int i;
    for(i=1;i<=cpt; i+=1) {
        printf("|");
        printf("%6i",i);
    }
    printf("| \n");
}


int mulligan_main(faction f, int already){
    if (1==already){
        return 0;
    }
    printf("\nFaction %i: %s vous pouvez, si vous le souhaitez vider votre main, mélanger la pioche et repiocher une nouvelle main. \n",get_faction_id(f),get_faction_nom(f));
    printf("Pour rappel, voux ne pouvez utiliser cette option qu'une seule fois dans toute la partie\n");
    printf("Souhaitez vous utiliser cette option? (y/n)\n");
    char answer;
    scanf("%s",&answer);
    getchar();

    while(!(answer=='y'|| answer=='n')){
        printf("Souhaitez vous utiliser cette option? (y/n) \n");
        scanf("%c",&answer);
        getchar();
    }
    if (answer=='n'){
        return 0;
    }
    return(1);
}

carte choix_carte(faction f){
    liste main_f= get_main(f);
    int length_main= len_liste(main_f);
    printf("\n Quelle carte voulez vous poser?[1,...,%i]\n",length_main);
    int answer;
    scanf("%d",&answer);
    getchar();
     while(answer<1||answer>length_main){
        printf("\n Quelle carte voulez vous poser? Veuillez choisir un entier entre 1 et %i.\n",length_main);
        scanf("%d",&answer);
        getchar();
    }
    int i;
    carte result;
    for(i=1;i<=answer;i+=1) {
        result= pop(&main_f);
    } 
    return result;
}
void position_carte(faction f, int* x,int* y,int called,int premier){
        int answer_y;
        int answer_x;
        do{
            if(premier==0){
                printf("\n Faction %i: %s comme vous posez la première carte de la manche il n'y a pas besoin d'entrer de coordonées.",get_faction_id(f),get_faction_nom(f));
                *x=1;
                *y=1;
            }
            else {
            if(called==0) {
                printf("\n Faction %i: %s où voulez vous poser votre carte? \n Rappel: la carte doit être adjacente à un autre carte déjà posée",get_faction_id(f),get_faction_nom(f));
            }     
            else{
                printf("\n Faction %i: %s où voulez vous poser votre carte? \n",get_faction_id(f),get_faction_nom(f));
                printf("\033[0;31m");
                printf("Rappel: la carte doit être adjacente à un autre carte déjà posée");
                printf("\033[00m");        
            }
            printf("\n Entrez la coordonée x:\n");
            scanf("%d",&answer_y);
            getchar();
            printf("\n Entrez la coordonée y:\n");
            scanf(" %d",&answer_x);
            getchar();
            *x=answer_x;
            *y=answer_y;
            called+=1;
            }
            }
        while (answer_x<0 || answer_x>46 || answer_y<0 || answer_y>46);
        
}

void affiche_effet(carte c){
    sleep(5);
    printf("\nLa carte %s vient d'être retournée.\n",get_carte_nom(c));
    printf("Voici la description de cette carte:\n%s\n",get_carte_description(c));
}

int affiche_gagnant_manche(faction f1, faction f2){
    int ddrs1,ddrs2;
    ddrs1=get_ddrs(f1);
    ddrs2=get_ddrs(f2);
    if (ddrs1 > ddrs2 ) {
        printf("\n Le vainqueur de cette manche est la faction: %s avec %i points ddrs contre %i.", get_faction_nom(f1),ddrs1,ddrs2);
        return 1;
    }
    else{
        printf("\n Le vainqueur de cette manche est la faction: %s avec %i points ddrs contre %i.", get_faction_nom(f2),ddrs2,ddrs1);
        return 2;
    }
}

int affiche_gagnant(faction f1, faction f2){
    int nb_vict1,nb_vict2;
    nb_vict1=get_nb_victoires(f1);
    nb_vict2=get_nb_victoires(f2);
    if (nb_vict1 > nb_vict2 ) {
        printf("\n Le vainqueur du jeu est la faction: %s avec %i manches gagnées contre %i.", get_faction_nom(f1),nb_vict1,nb_vict2);
        return 1;
    }
    else{
        printf("\n Le vainqueur du jeu est la faction: %s avec %i manches gagnées contre %i.", get_faction_nom(f2),nb_vict2,nb_vict1);
        return 2;
    }
}