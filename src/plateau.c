#include "../header/plateau.h"
#include "../header/structure.h"

typedef struct plateau_base *plateau;

struct plateau_base{
    grid grille;
    int nb_cartes_posees;
    int nb_cartes_visibles;
    liste cartes_retournees;
};

plateau cree_plateau(){
    plateau resultat;
    resultat = malloc();
    resultat->grille = init_grille();
    /*...*/
    return resultat;
};

void detruire_plateau(plateau *p){
    free_grille(&(*p)->grille);
    free_liste(&(*p)->cartes_retournees);
    free(*p);
};

/* pose carte comme pose cellule askip */


