#include <stdlib.h>
#include "structure.h"

/*--------------------------------- Grille : liste quadruplement chaînée ---------------------------------*/

struct cell_base {
    carte card;
    int visible;    /* 0 : cachée, 1 : visible */
    int activated;  /* 0 : non-activée, 1 : activée */
    int i;          /* Cellule de l'abscisse de la grille (pourra etre négatif) */
    int j;          /* Cellule de l'ordonnée de la grille (pourra etre négatif) */
    cell* west;     /* Pointeur vers la carte à l'ouest */
    cell* north;    /* Pointeur vers la carte au nord   */
    cell* east;     /* Pointeur vers la carte à l'est   */
    cell* south;    /* Pointeur vers la carte au sud    */
};

grille debut_grille(carte card){
    grille res = malloc(sizeof(grille));
    res->card = card;
    res->visible = 0;
    res->activated = 0;
    res->i = 0;
    res->j = 0;
    cell* west = NULL;
    cell* north = NULL;
    cell* east = NULL;
    cell* south = NULL;
}
/*
void pointer_to(cell* c, int direction, int i, int j){
    c->
}*/

 /*--------------------------------- Pioche : liste chaînée ---------------------------------*/

struct bucket { /*Maillon*/
    carte card;
    pioche next;
};
