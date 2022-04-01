#include "structure.h"

/*Grille : liste quadruplement chaînée*/

struct cell {
    int id_carte;
    int visible;    /* 0 : cachée, 1 : visible */
    int activated;  /* 0 : non-activée, 1 : activée */
    int i;          /* Cellule de l'abscisse de la grille (pourra etre négatif) */
    int j;          /* Cellule de l'ordonnée de la grille (pourra etre négatif) */
    cell* west;     /* Pointeur vers la carte à l'ouest */
    cell* north;    /* Pointeur vers la carte au nord   */
    cell* east;     /* Pointeur vers la carte à l'est   */
    cell* south;    /* Pointeur vers la carte au sud    */
};

 /*Pioche : liste chaînée*/

struct bucket { /*Maillon*/
    carte card;
    pioche next;
};