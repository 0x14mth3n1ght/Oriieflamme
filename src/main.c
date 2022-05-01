#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../header/carte.h"
#include "../header/faction.h"
#include "../header/plateau.h"
#include "../header/interface.h"
#include <time.h>


/*
@requires: La largeur du terminal doit être supérieur à 84 caractères pour afficher
        Correctement le titre
@assigns: nothing
@ensures: Affiche le titre de Oriieflame 
*/
void print_title()
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    for (int i = 0; i < w.ws_col; i++)
    {
        printf("---");
        if ((i % 2 == 0) && (i < (w.ws_col - 84)))
        {
            printf("-");
        }
    }
    printf("Bienvenue dans le meilleur jeu vidéoludique:    Oriieflamme: La Grande Guerre DDRS");
    for (int i = 0; i < w.ws_col; i++)
    {
        printf("---");
         if ((i % 2 == 0) && (i < (w.ws_col - 84)))
        {
            printf("-");
        }
    }
    printf("\n");
}

/*
@requires: *fact pointeur vers une faction valide, *partie pointeur vers un plateau valide
@assigns: fact, partie
@ensures: Effectue un tour de jeu pour la faction *fact présente sur le plateau *partie
*/

void tour_de_jeu(faction* fact, plateau* partie)
{
    int x,y; //Abscisse et ordonnée de la carte à poser

    carte new_card;
    int possible = 0;
    while (!possible)
    {
        affiche_plateau(*partie);
        affiche_main(*fact);
        new_card = choix_carte(*fact);
        affiche_plateau(*partie);
        position_carte(*fact, &x,&y);
        possible = pose_carte(partie, fact, new_card,x,y);
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
    plateau partie = cree_plateau();

    faction faction1 = get_faction_plateau(partie, 1);
    faction faction2 = get_faction_plateau(partie, 2);
    set_name(&faction1, "Je suis le nouveau nom de la faction");
    print_faction(faction1);
    //retourne_factions(partie,&faction1, &faction2);

    //bon
    /*
    * reinitilisation retourne 1 lorsque le jeu est terminé et 0 sinon.
    * Hors le jeu se termine lorsqu'une faction a gagné 2 manches. 
    * Cela assure la terminaison de la boucle while.
    * 
    */
   
    while (reinitialisation(&partie)==1)
    //PROBLEME REINITIALISATION
    { // réinitialisation renvoie un int
    print_faction(faction1);
    manche += 1;
    affiche_main(faction1);
    if (mulligan_main(faction1, a_remelanger_main(faction1)))
    {
        remelanger_main(&faction1);
    }
    affiche_main(faction2);
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
    affiche_plateau(partie);
    /*
    * reste_cartes est un compteur des cartes qu'il reste à retourner
    * Hors par passage dans la boucle while on retourne au moins une carte.
    * Ainsi le reste_cartes diminue strictement vers 0
    * la boucle se termine lorsque reste_cartes atteint 0.
    * Cela assure la terminaison de la boucle while
    * 
    */
   int restes_cartes = abs(get_nb_cartes_posees(partie) - get_nb_cartes_visibles(partie));
   printf("il reste:%i",restes_cartes);
    while (restes_cartes>0){
        affiche_effet(active_carte(&partie));
        affiche_plateau(partie);
        restes_cartes=abs(get_nb_cartes_posees(partie) - get_nb_cartes_visibles(partie));
    }
    affiche_gagnant_manche(faction1,faction2);
    if (get_ddrs(faction1)>get_ddrs(faction2)) {
        set_nb_victoires(&faction1,get_nb_victoires(faction1)+1);
    }
    else{
        set_nb_victoires(&faction2,get_nb_victoires(faction2)+1);

    }
    }
    affiche_gagnant(faction1,faction2);
    detruire_plateau(&partie);
}
