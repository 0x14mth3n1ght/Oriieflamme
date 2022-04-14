#include <stdlib.h>
#include <stdio.h>


#include "structure.h"

/*----------- Plateau = Grille : liste doublement chainee imbriquee dans liste doublement chainee -----------*/

/*----Liste doublement chainee mere----*/
//Liste doublement chaine mere = Pointeur vers un maillon "colonne"
typedef struct plateau_base colonne;
typedef colonne* ldc_mere;

struct plateau_base {
    //Element de la liste doublement chainee
    ldc_fille ligne;
    int y; //ordonnée de la colonne (offset_from_center : 0 si centre, 1 si colonne d'en dessous, -1 si colonne d'au dessus etc)
    //Pointeurs vers le "maillon" precedent ou suivant
    ldc_mere north;
    ldc_mere south;
};

/*----Liste doublement chainee fille----*/
typedef struct maillon * ldc_fille;
typedef struct maillon cell;

struct maillon {
    //Elements de la liste doublement chainee
    carte card;             //carte posee sur ces coordonnees (x,y)
    int x; //abscisse de la ligne (offset_from_center : 0 si centre, 1 si case a droite, -1 si case a gauche etc)
    int is_visible;         //0 si la carte est face cachée ; 1 si la carte est retournée
    int is_activated;       //1 si l'effet de la carte a été activée ; 0 sinon
    //Pointeurs vers le "maillon" precedent ou suivant
    ldc_fille west;
    ldc_fille east;
};

/*----Fonctions----*/
plateau init_grille(carte c){
    plateau out;
    ldc_fille ini;
        ini->card = c;
        ini->x = 0;
        ini->is_visible = 0;
        ini->is_activated = 0;
        ini->west = NULL;
        ini->east = NULL;
    out->ligne = ini;
    out->y = 0;
    out->north = NULL;
    out->south = NULL;
    return out;    
}

/*wip*/

/*--------------------------------- Liste chaînée ---------------------------------*/
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

int indice(elt e, liste l){
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
    liste curr = (*pl)->next; //Pointeur vers la case courante
    liste prec = *pl; //Pointeur vers la case précédente
    //Cas initial
    if (prec->val == e){ //Si la première case contient e
        *pl = (*pl)->next; //On commence par la case suivante
        return 1;
    }
    //Tant que l'on a pas trouvé e
    while (curr->val != e){
        prec->next = curr; //le suivant du précédent devient le pointeur courant
        prec = prec->next; //le pointeur du précédent avance
        curr = curr->next; //le pointeur du courant avance
    }
    //On est arrivé à e, ou à la fin
    if (curr != NULL){ //Arrivé à e
        prec->next = curr->next;
        free(curr); //On libère le maillon pointé par curr
        return 1;
    }
    //Pas arrivé à e : arrivée à la fin, e non enlevé
    return 0;
}

elt get_at(int pos, liste l){
    if (pos >= len(l)){
        printf("Error get_at : index pos out of range.\n");
        exit(EXIT_FAILURE);
    }
    for (int i=0; i<pos; i++)
        pop(&l);
    return peek(l);
}

liste melanger(liste l){
    liste out = cree_liste_vide();
    int n = len_liste(l);
    for (int i=0; i<n; i++){//Itération sur la taille de la liste
        int j = rand()%(n-i);
        elt chosen = get_at(j, l);
        push(chosen, &out);
        enlever(chosen, &l);
    }
    return out;
}