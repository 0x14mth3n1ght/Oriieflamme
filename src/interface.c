#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

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
        printf("|%7i",j);
    }
    putchar('|');
    printf("\n");

    for(i=max_north; i<=max_south; i+=1){
        print_ligne((max_east-max_west+1)*8+3);
        printf("\n");
        printf("%2i",i);
        for(j=max_west;j<=max_east;j+=1) {
            putchar('|');
            
            switch ( cachee_visible_existe(&p,i,j)) {

                case 0: {
                    cell cell_to_print= get_cell(g,i,j);
                    int num_faction= get_faction_id(get_faction(cell_to_print));
                    if(num_faction==1){
                        printf("\033[0;31m");
                        printf("   X   ");
                        printf("\033[00m");
                    }
                    else {
                        printf("\033[0;34m");
                        printf("   X   ");
                        printf("\033[00m");
                    }
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
                        printf("%7s",name_card);
                        printf("\033[00m"); 
                    }
                    else{
                        printf("\033[0;34m");
                        printf("%7s",name_card);
                        printf("\033[00m"); 
                    }
                }
                break;
                default: {
                    printf("%7s","");

                }
            }
        
        }
        printf("|\n");
    }
    printf("\n\033[0;31m La faction 1 %s possède %i points ddrs.\033[00m  ",get_faction_nom(faction1),get_ddrs(faction1));
    printf("\n\033[0;34m La faction 2 %s possède %i points ddrs.\033[00m\n",get_faction_nom(faction2),get_ddrs(faction2));

    printf(" Rappel: Les cartes posées par la faction 1 sont affichées en\033[0;31m rouge\033[00m.\n         Les cartes posées par la faction 2 sont affichées en\033[0;34m bleu\033[00m.\n");
    printf("         Les cartes non retournées sont affichées par un \"X\"");


      if (SDL_Init(SDL_INIT_VIDEO) == 0) {
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Event event;
        if (SDL_CreateWindowAndRenderer(640, 480, 0, &window, &renderer) == 0) {
            SDL_bool done = SDL_FALSE;

            while (!done) {

                SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
                SDL_RenderClear(renderer);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                
            for(int i=max_north; i<=max_south+1; i+=1){
                int droite_hori =(480/(max_south -max_north  + 1)) *(i-max_north);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                SDL_RenderDrawLine(renderer, 0,droite_hori,640,droite_hori);

            }
            for(int j=max_west;j<=max_east+1;j+=1) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

                int droite_vert=(640/(max_east-max_west + 1))*(j-max_west);
                SDL_RenderDrawLine(renderer, droite_vert,0,droite_vert, 480);


            
            }
            for(i=max_north; i<=max_south; i+=1){
            
                for(j=max_west;j<=max_east;j+=1) {
            
                    switch ( cachee_visible_existe(&p,i,j)) {

                        case 0: {
                            cell cell_to_print= get_cell(g,i,j);
                            int num_faction= get_faction_id(get_faction(cell_to_print));
                                if(num_faction==1){
                                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
                                    int x1 =(640/(max_east-max_west + 1)) *(j-max_west);
                                    int y1= (480/(max_south -max_north  + 1))*(i-max_north);
                                    int x2 =(640/(max_east-max_west + 1)) *(j+1-max_west);
                                    int y2= (480/(max_south -max_north  + 1))*(i+1-max_north);
                                    
                                    SDL_RenderDrawLine(renderer, x1,y1,x2,y2);
                                    SDL_RenderDrawLine(renderer, x1,y2,x2,y1);


                                }       
                                else {
                                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
                                    int x1 =(640/(max_east-max_west + 1)) *(j-max_west);
                                    int y1= (480/(max_south -max_north  + 1))*(i-max_north);
                                    int x2 =(640/(max_east-max_west + 1)) *(j+1-max_west);
                                    int y2= (480/(max_south -max_north  + 1))*(i+1-max_north);
                                    
                                    SDL_RenderDrawLine(renderer, x1,y1,x2,y2);
                                    SDL_RenderDrawLine(renderer, x1,y2,x2,y1);

                                }
                        }
                break;
                case 1:
                case 2:{
                    cell cell_to_print= get_cell(g,i,j);
                    carte card_to_print= get_card(cell_to_print);
                    int num_faction= get_faction_id(get_faction(cell_to_print));
                    if(num_faction==1) {
                        SDL_Rect srcrect;

                        int x1 =(640/(max_east-max_west + 1)) *(j-max_west);
                        int y1= (480/(max_south -max_north  + 1))*(i-max_north);
                        int x2 =(640/(max_east-max_west + 1)) *(j+1-max_west);
                        int y2= (480/(max_south -max_north  + 1))*(i+1-max_north);
                        srcrect.x=x1;
                        srcrect.y=y1;
                        srcrect.h=480/(max_south -max_north  + 1);
                        srcrect.w=640/(max_east-max_west + 1);
                        SDL_SetRenderDrawColor( renderer, 255, 0,0,255);
                        SDL_RenderFillRect( renderer, &srcrect);

                      /*   printf("\033[0;31m");
                        printf("%7s",name_card);
                        printf("\033[00m");  */
                    }
                    else{
                        SDL_Rect srcrect;

                        int x1 =(640/(max_east-max_west + 1)) *(j-max_west);
                        int y1= (480/(max_south -max_north  + 1))*(i-max_north);
                        int x2 =(640/(max_east-max_west + 1)) *(j+1-max_west);
                        int y2= (480/(max_south -max_north  + 1))*(i+1-max_north);
                        srcrect.x=x1;
                        srcrect.y=y1;
                        srcrect.h=480/(max_south -max_north  + 1);
                        srcrect.w=640/(max_east-max_west + 1);
                        SDL_SetRenderDrawColor( renderer, 0, 0,255,255);
                        SDL_RenderFillRect( renderer, &srcrect);
                        /* printf("\033[0;34m");
                        printf("%7s",name_card);
                        printf("\033[00m");  */
                    }
                }
                break;
                default: {

                }
            }
        
        }
    }
              SDL_RenderPresent(renderer);
        while( SDL_PollEvent( &event ) ){
            if(event.type==SDL_KEYDOWN){
                SDL_Quit();
                done=SDL_TRUE;
            }
            /* Look for a keypress */

            }
        }}

        if (renderer) {
            SDL_DestroyRenderer(renderer);
        }
        if (window) {
            SDL_DestroyWindow(window);
        }
    }
    SDL_Quit();
}



void affiche_main(faction f) {
    if (is_bot(f) == 1){//N'affiche pas la main d'un ordinateur
        return;
    }

    printf("\nFaction %i Voici votre main: \n",get_faction_id(f));
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

    if (is_bot(f) == 1){ // Choix automatique pour l'ordinateur
        return choose_mulligan();
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

    if (is_bot(f) == 1){
        int choose = choose_card_index(f);
        return get_at(choose, main_f);
    }

    int length_main= len_liste(main_f);
    printf("\nQuelle carte voulez vous poser?[1,...,%i]\n",length_main);
    int answer;
    scanf("%d",&answer);
    getchar();
     while(answer<1||answer>length_main){
        printf("\nQuelle carte voulez vous poser? Veuillez choisir un entier entre 1 et %i.\n",length_main);
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
void position_carte(faction f, int* x,int* y,int called,int premier, plateau p){
        int answer_y;
        int answer_x;
        do{
            if(premier==0){

                if (is_bot(f) == 0){ // Pas d'affichage si la faction est jouée par un ordinateur. 
                    printf("\n Faction %i: %s comme vous posez la première carte de la manche il n'y a pas besoin d'entrer de coordonées.\n",get_faction_id(f),get_faction_nom(f));
                    #ifndef DEBUG
                    sleep(4);
                    #endif
                } else {
                    printf("\n Faction %i (%s) vient de placer sa carte.\n", get_faction_id(f), get_faction_nom(f));
                }

                *x=1;
                *y=1;
                answer_x=1;
                answer_y=1;
            }
            else {
            
            if (is_bot(f) == 1){ //Choix de la carte pour un ordinateur
                cell c = choose_cell_dispo(p);
                *x = getX(c);
                *y = getY(c);
                called++;
                printf("\n Faction %i (%s) vient de placer sa carte.\n", get_faction_id(f), get_faction_nom(f));
                return;
            }

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
    #ifndef DEBUG
    sleep(5);
    #endif
    if (c==NULL)
        return;
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

void print_coordonnees_dispo(plateau p){
    liste dispo = get_cell_dispo(p);
    printf("\n Emplacements disponibles :");
    while (test_vide(dispo)!=1){
        cell c = pop(&dispo);
        printf("(%d, %d) ", getY(c), getX(c));
    }
    printf("\n");
}

void mode_de_jeu(plateau* pp){

    faction faction1 = get_faction_plateau(*pp, 1);
    faction faction2 = get_faction_plateau(*pp, 2);
    #ifdef DEBUG
    set_name(&faction1, "Ordinateur 1");
    set_is_bot(&faction1, 1);

    set_name(&faction2, "Ordinateur 2");
    set_is_bot(&faction2, 1);
    return;
    #endif

    printf("\n FACTION 1 : \n");
    printf("Choisissez si la faction 1 est un joueur ou un ordinateur :\n Entrer 0 pour joueur\n Entrer 1 pour ordinateur\n >>> ");
    int answer1;
    scanf("%d", &answer1);
    getchar();
    printf("\n");
    while (answer1 != 0 && answer1 != 1){
        printf("Veuillez entrer 0 pour que la faction 1 soit un joueur, 1 pour que ce soit un ordinateur\n >>> ");
        scanf("%d", &answer1);
        getchar();
    }
    if (answer1 == 0){//Joueur
        char* name1 = malloc(100*sizeof(char)); //taille de nom maximale : 100
        printf("Veuillez entrer votre nom :\n >>> ");
        fflush(stdout);
        scanf("%s", name1);
        set_name(&faction1, name1);
    } else {//Ordinateur
        set_name(&faction1, "Ordinateur 1");
        set_is_bot(&faction1, 1);
    }

    printf("\n FACTION 2 : \n");
    printf("Choisissez si la faction 2 est un joueur ou un ordinateur :\n Entrer 0 pour joueur\n Entrer 1 pour ordinateur\n >>> ");
    int answer2;
    scanf("%d", &answer2);
    getchar();
    printf("\n");
    while (answer2 != 0 && answer2 != 1){
        printf("Veuillez entrer 0 pour que la faction 2 soit un joueur, 1 pour que ce soit un ordinateur.\n >>> ");
        scanf("%d", &answer2);
        getchar();
    }
    if (answer2 == 0){//Joueur
        char* name2 = malloc(100*sizeof(char)); //taille de nom maximale : 100
        printf("Veuillez entrer votre nom :\n >>> ");
        fflush(stdout);
        scanf("%s", name2);
        set_name(&faction2, name2);
    } else {//Ordinateur
        set_name(&faction2, "Ordinateur 2");
        set_is_bot(&faction2, 1);
    }

}