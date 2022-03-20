#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "carte.h"
#include "faction.h"
#include "plateau.h"
#include "interface.h"
#include <time.h>

/*
@requires: La largeur du terminal doit être supérireur à 84 caractères pour afficher
        Correctement le titre
@assigns: nothing
@ensures: Affiche le titre de Oriieflame 
*/
void print_title()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    char *str_dash_title = malloc(sizeof(char *));

    for (int i = 0; i < w.ws_col; i++)
    {
        printf("---");
        if ((i % 2 == 0) && (i < (w.ws_col - 84)))
        {
            strcat(str_dash_title, "-");
        }
    }
    printf("%s", str_dash_title);
    printf("Bienvenue dans le meilleur jeu vidéoludique:    Oriieflamme: La Grande Guerre DDRS");
    printf("%s\n", str_dash_title);
    for (int i = 0; i < w.ws_col; i++)
    {
        printf("---");
    }
    free(str_dash_title);
}

/*
@requires: *fact pointeur vers une faction valide, *partie pointeur vers un plateau valide
@assigns: fact, partie
@ensures: Effectue un tour de jeu pour la faction *fact présente sur le plateau *partie
*/

void tour_de_jeu(faction *fact, plateau *partie)
{
    int *new_pos;
    carte new_card;
    int possible = 0;
    new_pos=malloc(2*sizeof(int));
    while (!possible)
    {
        affiche_main(*fact);
        new_card = choix_carte(*fact);
        affiche_plateau(*partie);
        position_carte(*fact, new_pos);
        possible = pose_carte(partie, fact, &new_card, new_pos);
    }
}

int main()
{
    srand(time(NULL)); // Utilisé pour pour générer le rand()
    print_title();
    /* manche est le compteur de manche afin de savoir comment sélectionner la faction qui commence
    *
    * starting_faction est la faction qui commence:
    *   Si starting_faction==0 -> la faction2 commence
    *   Si starting_faction==1 -> la faction1 commence
    *
    *  On initialise le plateau et on créer deux factions qui vont prendre la valeur 
    * des deux faction du plateau partie.
    */
    int manche = 0;
    int starting_faction;
    plateau partie = creer_plateau();
    faction faction1;
    faction faction2;
    retourne_factions(&faction1, &faction2);
    /*
    * reinitilisation retourne 1 lorsque le jeu est terminé et 0 sinon.
    * Hors le jeu se termine lorsqu'une faction a gagné 2 manches. 
    * Cela assure la terminaison de la boucle while.
    * 
    */
    while (!reinitialisation(&partie))
    { // réinitialisation renvoie un int
    manche += 1;
    repiocher(&faction1);
    repiocher(&faction2);
    affiche_main(faction1);
    if (mulligan_main(faction1, a_remelanger_main(faction1)))
    {
        remelanger_main(&faction1);
    }
    if (mulligan_main(faction2, a_remelanger_main(faction2)))
    {
        remelanger_main(&faction2);
    }
    /*On choisie aléatoirement une deux des factions */
    if (manche != 2)
    {
        starting_faction = rand() % 2;
    }
    else
    {
        starting_faction = (starting_faction + 1) % 2;
    }
    for (int j = 0; j < 16; j += 1)
    {
        if ((j + starting_faction) % 2 == 1)
        {
            // FACTION 1
            tour_de_jeu(&faction1, &partie);
        }
        else
        {
            // FACTION 2
            tour_de_jeu(&faction2, &partie);
        }
    }
    int reste_cartes = 1;
    affiche_plateau(partie);
    /*
    * reste_cartes est un compteur des cartes qu'il reste à retourner
    * Hors par passage dans la boucle while on retourne au moins une carte.
    * Ainsi le reste_cartes diminue strictement vers 0
    * la boucle se termine lorsque reste_cartes atteint 0.
    * Cela assure la terminaison de la boucle while
    * 
    */
    while (reste_cartes){
        affiche_effet(active_carte(&partie, &reste_cartes));
        affiche_plateau(partie);
    }
    }
    affiche_gagnant(faction1,faction2);
    detruire_plateau(&partie);
}
