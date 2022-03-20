#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "carte.h"
#include "faction.h"
#include "plateau.h"
#include "interface.h"

void print_title() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    char* str_dash_title= malloc(sizeof(char*));
    
    for (int i=0;i<w.ws_col;i++) {
        printf("---");
        if ((i%2==0) && (i<(w.ws_col-84)) ) {
            strcat(str_dash_title,"-");
        }
    }
    printf("%s",str_dash_title);
    printf("Bienvenue dans le meilleur jeu vidéoludique:    Oriieflamme: La Grande Guerre DDRS");
    printf("%s\n",str_dash_title);
    for (int i=0;i<w.ws_col;i++) {
    printf("---");
    }
    free(str_dash_title);
}

int main ()
{
    srand(time(NULL)); // Utilisé pour pour générer le rand()
    print_title();
    char* new_game= "y";
    while(new_game=="y") {
            int manche =0;
            int starting_faction;
            plateau partie;
            partie=creer_plateau();
        
            faction faction1;
            faction faction2;
            retourne_factions(&faction1,&faction2);
        while(reinitialisation(&partie)) { //réinitialisation renvoie un int
            manche+=1;
            repiocher(&faction1);
            repiocher(&faction2);
            affiche_main(faction1);
            if (mulligan_main(faction1,a_remelanger_main(faction1))) {
                remelanger_main(&faction1);
            }
            if (mulligan_main(faction2,a_remelanger_main(faction2))) {
                remelanger_main(&faction2);
            }
            /*On choisie aléatoirement une deux des factions */
            if (manche !=2) {
                starting_faction=rand()%2;
            }
            else{
            starting_faction= (starting_faction + 1)%2;
            }
            carte new_card;
            int new_pos[2];
            int possible;
            for (int j=0; j<18; j+=1){
                if ((j+starting_faction)%2== 1) {
                    //FACTION 1
                    possible=0;
                    while(!possible){
                        affiche_main(faction1);
                        new_card=choix_carte(faction1);
                        position_carte(faction1,&new_pos);
                        possible=carte_faction(&faction1,new_pos,new_card);
                    }

                }
                else {
                    //FACTION 2
                    possible=0;
                    while(!possible){
                        affiche_main(faction2);
                        new_card=choix_carte(faction2);
                        position_carte(faction2,&new_pos);
                        possible=carte_faction(&faction2,new_pos,new_card);
                    }
                }
            }
        }

        }
        // fin partie


        detruire_plateau(&partie);
        }
        

        /*en commentaire pcq plateau.h
        
        faction faction2;
        faction faction1;
        Première Partie:
        
        For  i de 1 à 3 max: 
        début manche i

        MISE EN PLACE:
        pioche(*faction1);
        affiche_main(faction1);
        mulligan_main(faction1,a_remelanger_main(faction1));

        pioche(*faction2);
        affiche_main(faction2);
        mulligan_main(faction2,a_remelanger_main(faction2));

        DEBUT JEU:
        SI STARTING_FACTION == 1 -> FACTION1 DEBUTE

        if(i!=2) {
            starting_faction=rand() %2; 
        }
        else{
            starting_faction= (starting_faction + 1)%2;
        }
        int new_pos[2];
        for (int j=0; j<18; j+=1){
            if ((j+starting_faction)%2== 1) {
                //FACTION 1 
                affiche_main(faction1);
                position card = choix_carte(faction1);
                
                position_carte(faction1,new_pos)
            }
            else {
                //FACTION 2

            }
        }

        
        
        
        
        */
    }