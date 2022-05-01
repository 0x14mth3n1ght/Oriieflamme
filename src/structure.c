#include <stdlib.h>
#include <stdio.h>
#include "../header/structure.h"

#define N (nb_cartes_main_debut_manche*2+15) //Nombre de lignes
#define P (nb_cartes_main_debut_manche*2+15) //Nombre de colonnes

/**
 * @file structure.c
 * @brief Implémentation des fonctions de structures de grille du plateau et de liste chaînée.
 */

/**
 * @brief nulle est la cellule nulle
 * 
 */
const cell nulle = NULL;

/*--------------------------------- Grille : tableau 2D ---------------------------------*/

/**
 * @brief Construction d'une grille de n lignes et p colonnes
 * 
 * @param n nombre de lignes de la grille
 * @param p nombre de colonnes de la grille
 * @return Grille de @b n lignes et @b p colonnes, contenant la cellule vide sur chaque case
 */
grid new_grille(int n, int p){
    grid out = malloc(n*sizeof(cell*));
    for (int i=0; i<n; i++){
        out[i] = malloc(p*sizeof(cell));
        for (int j=0; j<p; j++){
            out[i][j] = nulle;
        }
    }
    return out;
}

grid init_grille(){
    return new_grille(N, P);
}

void premiere_cellule(cell c, grid* pg){
    int x_center = N / 2;
    int y_center = P / 2;
    if ((*pg)[x_center][y_center] != nulle){
        printf("warning premiere_cellule : la grille n'est pas vide au centre.\n");
        return;
    }
    (*pg)[x_center][y_center] = c;
}

int est_libre(grid g, int x, int y){
    return (g[x][y] != nulle);
}

void free_grille(grid* pg){
    for (int i=N-1; i>=0; i--){
        for (int j=0; j<P; j++){
            free((*pg)[i][j]);
        }
        free((*pg)[i]);
    }
    free(*pg);
}

int placer_cell(cell c, grid* pg, int x, int y){
    if ((*pg)[x][y] == nulle){//Si la case n'est pas occupée
        (*pg)[x][y] = c;
        return 1;
    }
    return 0;
}

cell get_cell(grid g, int x, int y){
    return g[x][y];
}

int taille_ligne_direction(direction d, grid g, int n){
    switch (d){
    case north:
        for (int i=0; i<N; i++){
            if (g[i][n] != nulle)
                return i;
        }
        return N; //si la colonne est nulle
        break;
    case south:
        for (int i=0; i<N; i++){
            if (g[N-1-i][n] != nulle)
                return N-1-i;
        }
        return 1; //si la colonne est nulle
        break;
    case west:
        for (int j=0; j<P; j++){
            if (g[n][j] != nulle)
                return j;
        }
        return P; //si la ligne est nulle
        break;
    case east:
        for (int j=0; j<P; j++){
            if (g[n][P-1-j] != nulle)
                return P-1-j;
        }
        return 1; //si la ligne est nulle
        break;   
    default:
        break;
    }
    return -1;
}

int taille_grille(direction d, grid g){
    int max = 0; //Recherche de max parmi toutes les lignes ou colonnes
    int min = (N>P)?N:P; //Recherche de min parmi toutes les lignes ou colonnes
    switch (d){
    case north:
        for (int j=0; j<P; j++){
            int val = taille_ligne_direction(north, g, j);
            min = (min < val)?min:val;
        }
        return min;
        break;
    case south:
        for (int j=0; j<P; j++){
            int val = taille_ligne_direction(south, g, j);
            max = (max > val)?max:val;
        }
        return max;
        break;
    case west:
        for (int i=0; i<N; i++){
            int val = taille_ligne_direction(west, g, i);
            min = (min < val)?min:val;
        }
        return min;
        break;
    case east:
        for (int i=0; i<N; i++){
            int val = taille_ligne_direction(east, g, i);
            max = (max > val)?max:val;
        }
        return max;
        break;
    default:
        return -1;
        break;
    }
}

int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2){
    if ((*pg)[x1][y1] == nulle && (*pg)[x2][y2] != nulle)
        return 2;
    if ((*pg)[x1][y1] == nulle)
        return -1;
    if ((*pg)[x2][y2] != nulle)
        return 1;
    cell c = (*pg)[x1][y1]; //On stocke la cellule à déplacer
    (*pg)[x2][y2] = c;
    (*pg)[x1][y1] = nulle;
    return 0;
}

int supp_cell_grille(grid* pg, int x, int y){
    if ((*pg)[x][y] == nulle) //S'il n'y a pas de cellule sur la case
        return 0;
    (*pg)[x][y] = nulle;
    return 1;
}

grid sous_grille(grid g, int x1, int y1, int x2, int y2){
    int n = abs(x2 - x1);
    int p = abs(y2 - y1);
    grid out = new_grille(n+1, p+1);
    for (int i=0; i<=n; i++){
        for (int j=0; j<=p; j++){
            out[i][j] = g[x1+i][y1+j];
        }
    }
    return out;
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
    liste res = malloc(sizeof(struct bucket));
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
    *pl = (*pl)-> next; //On avance dans la liste
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
        if (equals(l->val,e)==1)
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
    if (equals((*pl)->val,e)==1){ //Si la première case contient e
        liste first = *pl;
        *pl = (*pl)->next; //On commence par la case suivante
        free(first);
        return 1;
    }
    liste curr = (*pl)->next; //Pointeur vers la case courante
    liste prec = *pl; //Pointeur vers la case précédente
    //Tant que l'on a pas trouvé e
    while (equals(curr->val,e)==0){
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
        printf("Error get_at : index out of range.\n");
        exit(EXIT_FAILURE);
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
        if (equals(l->val,e)==1)
            n++;
        l = l->next;
    }
    return n;
}

liste deepcopy(liste l){
    liste out = cree_liste_vide();
    while (l!=NULL)
        push(pop(&l), &out);
    return out;
}

int liste_equals(liste l1, liste l2){
    while (test_vide(l1)==0 && test_vide(l2)==0){
        if (equals(l1->val, l2->val)==0)
            return 0;
        l1 = l1->next;
        l2 = l2->next;
    }
    if (test_vide(l1)==0 || test_vide(l2)==0)//Si l'une des deux listes est vide, alors elles ne sont pas de même taille
        return 0;
    return 1;
}

void print_liste(liste l){
    while(test_vide(l)!=1){
        printf("%d -> ", get_carte_id(pop(&l)));
    }
    printf("()\n");
}