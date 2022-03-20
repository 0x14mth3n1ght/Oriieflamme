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

void tour_de_jeu(faction *fact, plateau *partie)
{
    int new_pos[2];
    carte new_card;
    int possible = 0;
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
    char new_game = 'y';
    while (new_game == 'y')
    {
        int manche = 0;
        int starting_faction;
        plateau partie = creer_plateau();
        faction faction1;
        faction faction2;
        retourne_factions(&faction1, &faction2);
        while (reinitialisation(&partie))
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
            for (int j = 0; j < 18; j += 1)
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
            while (reste_cartes)
            {
                affiche_effet(active_carte(&partie, reste_cartes));
                affiche_plateau(partie);
            }
        }
        affiche_gagnant(faction1,faction2);
        detruire_plateau(&partie);
    }
    // fin partie
}
