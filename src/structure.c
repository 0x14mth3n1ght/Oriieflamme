#include <stdlib.h>
#include <stdio.h>
#include "../header/structure.h"

#define N 50 //Nombre de lignes
#define P 50 //Nombre de colonnes

/**
 * @file structure.c
 * @brief Implémentation des fonctions de structures de grille du plateau et de liste chaînée.
 */

/*--------------------------------- Grille : tableau 2D ---------------------------------*/
grid init_grille(){
    grid out = malloc(N*sizeof(cell*));
    for (int i=0; i<N; i++){
        out[i] = calloc(P, sizeof(cell));
        for (int j=0; j<P; j++)
            out[i][j] = NULL;
    }
    return out;
}

void premiere_cellule(cell c, grid* pg){
    int x_center = N / 2;
    int y_center = P / 2;
    (*pg)[x_center][y_center] = c;
}

int est_libre(grid g, int x, int y){
    return (g[x][y] != NULL);
}

void free_grille(grid* pg){
    for (int i=0; i<N; i++){
        free((*pg)[i]);
    }
    free(*pg);
}

/**
 * @brief Permet de convertir les coodonnées relatives d'une grille de centre (0,0) en des coordonnées positifs d'une grille de centre (N/2, P/2);
 * 
 * @param x abscisse de coordonnées dans le système de grilles centrées en (0,0)
 * @param y ordonnée de coordonnées dans le système de grilles centrées en (0,0)
 * @return modifie les paramètres @b x et @b y en des indices utilisables par l'implémentation (indices positifs)
 */
void coords_tableaux(int x, int y){
    x = x + N / 2;
    y = y + P / 2;
}

/**
 * @brief Permet de convertir les coodonnées positifs d'une grille de centre (N/2, P/2) en des coordonnées relatives d'une grille de centre (0,0);
 * 
 * @param x abscisse de coordonnées dans le système de grilles centrées en (N/2, P/2)
 * @param y ordonnée de coordonnées dans le système de grilles centrées en (N/2, P/2)
 * @return modifie les paramètres @b x et @b y en des indices relatifs d'une grille centrée en (0,0) (indices relatifs)
 */
void coords_grille(int x, int y){
    x = x - N / 2;
    y = y - P / 2;
}

int placer_cell(cell c, grid* pg, int x, int y){
    //On recentre x et y en le centre de *pg
    coords_tableaux(x,y);
    if ((*pg)[x][y]==NULL){//Si la case n'est pas occupée
        (*pg)[x][y] = c;
        return 1;
    }
    return 0;
}

cell get_cell(grid g, int x, int y){
    //On recentre x et y en le centre de g
    coords_tableaux(x,y);
    return g[x][y];
}

int taille_grille(direction d, grid g){
    int max = 0; //Recherche de max parmi toutes les lignes ou colonnes
    switch (d){
    case west:
        for (int j=0; j<P; j++){
            int val = taille_ligne_direction(west, g, j);
            max = (max > val)?max:val;
        }
        return max;
        break;
    case east:
        for (int j=0; j<P; j++){
            int val = taille_ligne_direction(east, g, j);
            max = (max > val)?max:val;
        }
        return max;
        break;
    case north:
        for (int i=0; i<N; i++){
            int val = taille_ligne_direction(north, g, i);
            max = (max > val)?max:val;
        }
        return max;
        break;
    case south:
        for (int i=0; i<N; i++){
            int val = taille_ligne_direction(north, g, i);
            max = (max > val)?max:val;
        }
        return max;
        break;
    default:
        return -1;
        break;
    }
}

int taille_ligne_direction(direction d, grid g, int n){
    switch (d){
    case west:
        for (int i=0; i<N; i++){
            if (g[i][n] != NULL)
                return N/2 - i;
        }
        break;
    case east:
        for (int i=0; i<N; i++){
            if (g[N-1-i][n] != NULL)
                return N/2 - i;
        }
        break;
    case north:
        for (int j=0; j<P; j++){
            if (g[n][j] != NULL)
                return P/2 - j;
        }
        break;
    case south:
        for (int j=0; j<P; j++){
            if (g[n][P-1-j] != NULL)
                return P/2 - j;
        }
        break;   
    default:
        break;
    }
}

int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2){
    coords_tableaux(x1,y1);
    coords_tableaux(x2,y2);
    if ((*pg)[x1][y1] == NULL && (*pg)[x2][y2] == NULL)
        return 2;
    if ((*pg)[x1][y1] == NULL)
        return -1;
    if ((*pg)[x2][y2] == NULL)
        return -1;
    cell c = (*pg)[x1][y1]; //On stocke la cellule à déplacer
    (*pg)[x2][y2] = c;
    (*pg)[x1][y1] = NULL;
    return 0;
}

int supp_cell_grille(grid* pg, int x, int y){
    coords_tableaux(x,y);
    if ((*pg)[x][y] == NULL) //S'il n'y a pas de cellule sur la case
        return 0;
    (*pg)[x][y] = NULL;
    return 1;
}

/*--------------------------------- Liste chaînée ---------------------------------*/
/**
 * @struct bucket
 * @brief Type concret de la structure de maillon de la liste chaînée. Ses éléments sont des @b elt, type abstrait.
 */
struct bucket {
    elt val;
    liste next;
};

/*----Fonctions----*/
liste cree_liste_vide(){
    return NULL;
}

int test_vide(liste l){
    return (l==NULL);
}

/*  @requires : l est une liste valide, e un élément valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec e au dessus de la liste l */
liste cons(elt e, liste l){
    liste res = malloc(sizeof(liste));
    res->val = e;
    res->next = l;
    return res;
}

void push(elt e, liste *pl){
    *pl = cons(e, *pl);
}

elt pop(liste* pl){
    if (*pl == NULL){
        printf("Error pop : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    elt e = (*pl)->val; //On stocke l'élément en haut de la liste
    liste head = *pl;
    *pl = (*pl)-> next; //On avance dans la liste
    free(head);
    return e;
}

elt peek(liste l){
    if (l == NULL){
        printf("Error peek : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    return l->val;
}

int find(elt e, liste l){
    int i = 0;
    while (l!=NULL){
        if (l->val == e)
            return i;
        i++;
        l = l->next;
    }
    //e n'a pas été trouvé
    return -1;
}

int len_liste(liste l){
    int n = 0;
    while (l!=NULL){
        n++;
        l = l->next;
    }
    return n;
}

int enlever(elt e, liste* pl){
    //Cas initial
    if ((*pl)->val == e){ //Si la première case contient e
        liste first = *pl;
        *pl = (*pl)->next; //On commence par la case suivante
        free(first);
        return 1;
    }
    liste curr = (*pl)->next; //Pointeur vers la case courante
    liste prec = *pl; //Pointeur vers la case précédente
    //Tant que l'on a pas trouvé e
    while (curr->val != e){
        prec = prec->next; //le pointeur du précédent avance
        curr = curr->next; //le pointeur du courant avance
    }
    //On est arrivé à e, ou à la fin
    if (curr != NULL){ //Arrivé à e
        prec->next = curr->next;
        free(curr);
        return 1;
    }
    //Pas arrivé à e : arrivée à la fin, e non enlevé
    return 0;
}

elt get_at(int pos, liste l){
    if (pos >= len_liste(l)){
        return NULL;
    }
    for (int i=0; i<pos; i++)
        pop(&l);
    return peek(l);
}

liste melanger(liste l){
    liste out = cree_liste_vide();
    //On va choisir des elements restants au hasard dans l, on les ajoute à out et on les supprime de l 
    int n = len_liste(l);
    for (int i=0; i<n; i++){ //Itération sur la taille de la liste
        int j = rand()%(n-i); //Choix d'un entier parmi les éléments restants de la liste l (entre 0 et n-i-1)
        elt chosen = get_at(j, l); //Élement choisi par l'aléatoire
        push(chosen, &out);
        enlever(chosen, &l);
    }
    return out;
}

void free_liste(liste* pl){
    while (*pl != NULL){
        liste tmp = *pl;
        *pl = (*pl)->next;
        free(tmp);
    }
}

int nb_elt(elt e, liste l){
    int n = 0;
    while (l!=NULL){
        if (l->val == e)
            n++;
        l = l->val;
    }
    return n;
}