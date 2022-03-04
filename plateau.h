#ifndef PLATEAU_H
#define PLATEAU_H

/* Type concret d'un plateau de jeu */
typedef struct _plateau {
    pile **grille;
    int taille;
    int **activees;
} plateau;


/*
@requires: /nothing
@assigns: /nothing
@ensures: Initialise un plateau vide
*/
plateau creer_plateau(int taille);


/*
@requires: /nothing
@assigns: plateau
@ensures: réinitialise les cases activées du plateau
*/
void reinitialisation_activees(plateau*);


/*
@requires: plateau non rempli
@assigns: /nothing
@ensures: renvoit vrai ssi le coup joué par joueur aux coordonnées indiquées est valide
*/
int coup_valide(plateau, int ligne, int colonne);


/*
@requires: /nothing
@assigns: /nothing
@ensures: renvoit vrai ssi le plateau est rempli
*/
int est_rempli(plateau);


/*
@requires: coordonnées valides
@assigns: /nothing
@ensures: Renvoit la liste (pile) des cases voisines
*/
pile cases_voisines(plateau, int, int);


/*
@requires: ligne et colonnes coordonnées valides
@assigns: /nothing
@ensures: Affiche la pile de la case correspondante
*/
void montrer_pile(plateau, int ligne, int colonne);


/*
@requires: /nothing
@assigns: /nothing
@ensures: Affiche le plateau
*/
void afficher_plateau(plateau);


/*
@requires: indice valide ou égal à -1 ; coordoonées valides ou égales à -1
@assigns: indice, ligne, colonne
@ensures: Retourne les coordonnées correspondant à l'indice ou vice versa
*/
void convertion_indice_coordonnees(plateau, int* indice, int* ligne, int* colonne);



#endif