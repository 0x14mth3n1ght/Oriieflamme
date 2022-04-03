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

/*--------------------------------- Cartes en main : Fonctions ---------------------------------*/
void main_vide(carteEnMain cmain, int size){
    for (int i=0; i<size; i++){
        cmain[i] = /*wip : carte_nulle*/NULL ;
    }
}

int ajout_carte(carte c, carteEnMain cmain, int size){
    int i = 0;
    while (i<size){
        i++;
        if (cmain[i] == /*wip : carte_nulle*/NULL){
            cmain[i] = c;
            return i;
        }
    }
    //main pleine
    //assert(i == size-1);
    return 0;
}

int indice_carte_main(carte c, carteEnMain cmain, int size){
    int i=0;
    while (i<size){
        if (cmain[i] == c)
            return i;
        i++;
    }
    //non trouvé
    return -1;
}

int supprime_carte_main(carte c, carteEnMain cmain, int size){
    if (!(mem_main(c, cmain, size)))
        return 0;
    int i = 0;
    int deleted = 0;
    while (i<size - 1){
        if (cmain[i] == c)
            deleted = 1;
        if (deleted)
            cmain[i] == cmain[i+1]; //carte nulle si le prochain est carte_nulle.
        i++;
    }
    //Cas la carte etait en derniere position ou si elle a déjà été supprimée
    if (cmain[size-1] == c || deleted)
        cmain[size-1] = /*wip : carte_nulle*/NULL;

    return 1;
}

carte get_carte_at(int pos, carteEnMain cmain, int size){
    if (0 <= pos < size)
        return cmain[pos];
    return NULL;/*wip : carte nulle*/
}

/*--------------------------------- Pioche : liste chaînée ---------------------------------*/
struct bucket {
    carte card;
    pioche next;
};

/*----Fonctions----*/
pioche creer_pioche_vide(){
    return NULL;
}

int est_vide(pioche p){
    return (p==NULL);
}

/*  @requires : p est une pioche valide, c une carte valide
    @assigns  : nothing
    @ensures  : ajoute c au dessus de la liste p */
pioche cons(carte c, pioche p){
    pioche res = malloc(sizeof(pioche));
    res->card = c;
    res->next = p;
    return res;
}

void push(carte c, pioche *pp){
    *pp = cons(c, *pp);
}

carte pop(pioche* pp){
    if (*pp == NULL){
        printf("Error pop : la pioche est vide.\n");
        exit(EXIT_FAILURE);
    }
    carte out = (*pp)->card;
    *pp = (*pp) -> next;
    return out;
}

carte peek(pioche p){
    if (p == NULL){
        printf("Error peek : la pioche est vide.\n");
        exit(EXIT_FAILURE);
    }
    return p->card;
}

int mem_pioche(pioche p, carte c){
    while (p!=NULL){
        if (p->card == c) return 1;
        p = p->next;
    }
    return 0;
}

int pioche_len(pioche p){
    int len = 0;
    while (p!=NULL){
        len++;
        p = p->next;
    }
    return len;
}