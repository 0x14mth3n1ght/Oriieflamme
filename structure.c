#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

/*Implémentation liste chainée*/

list cree_liste_vide(){
    return NULL;
}

int est_vide(list l){
    return (l==NULL);
}

/*  @requires l est une liste valide
    @assigns nothing
    @ensures ajoute a au dessus de la liste l    */
list cons(value a, list l){
    list res = malloc(sizeof(list));
    res->val = a;
    res->next = l;
    return res;
}

void push(value a, list *pl){
    *pl = cons(a, *pl);
}

value pop(list *pl){
    if (*pl == NULL){
        printf("Error : Incorrect file. (Pop error : List is empty)\n");
        exit(EXIT_FAILURE);
    }
    value res;
    res = (*pl)->val;
    *pl = (*pl)->next;
    return res;
}

void print_liste(list l){
    while (l != NULL){ /*Terminaison : la liste ne boucle pas car on n'utilise que les fonctions de base des piles*/
        printf("-> [%i] ", l->val);
        l = l-> next;
    }
    printf("-> []\n");
}

/*Implémentation grille (Tableau 2D)*/

grille creer_grille(int h, int w){
    char** mat = malloc(h * sizeof(char*));
    int i,j;
    for (i=0;i<h;i+=1) {
        mat[i] = calloc(w, sizeof(char));
        for (j=0;j<w;j+=1)
            mat[i][j] = 0;
    }
    return mat;
}

void affiche_grille(grille g, int h, int w){
    int i,j;
    for (i=0; i<h; i+=1){
        for (j=0; j<w; j+=1)
            printf("%i", t[i][j]);
        printf("\n");
    }
}