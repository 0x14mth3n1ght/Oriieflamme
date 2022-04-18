#include <stdlib.h>
#include <stdio.h>
#include "../header/structure.h"

/*----------- Grille : liste doublement chainee imbriquee dans liste doublement chainee d'éléments de type cell -----------*/

//La grille pointera toujours hors des fonctions vers la ligne y=0
//La ddl_fille pointera toujours hors des fonctions vers le maillon x=0

/*----Liste doublement chainee fille----*/
typedef struct maillon * ddl_fille;
typedef struct maillon maillon2D;

struct maillon {
    //Elements de la liste doublement chainee
    cell val; //cellule posee sur ces coordonnees (x,y) ; une case non occupée est caractérisée par une val = NULL
    int x; //abscisse de la ligne (offset_from_center : 0 si centre, 1 si case a droite, -1 si case a gauche etc)
    int y; //ordonnée de la case (egale à ddl_mere->y)
    //Pointeurs vers le "maillon" precedent ou suivant
    ddl_fille west;
    ddl_fille east;
};

/*----Liste doublement chainee mere----*/
typedef struct grid_base colonne;
//Liste doublement chaine mere = Pointeur vers un maillon "colonne"
typedef colonne* ddl_mere; // == type grid

struct grid_base {
    //Element de la liste doublement chainee
    ddl_fille ligne;
    int y; //ordonnée de la colonne (offset_from_center : 0 si centre, -1 si colonne d'en dessous, 1 si colonne d'au dessus etc)
    //Pointeurs vers le "maillon" precedent ou suivant
    ddl_mere north;
    ddl_mere south;
};

// ----Fonctions----

grid init_grille(){
    grid out = malloc(sizeof *out);
        out->ligne = NULL;
        out->y = 0;
        out->north = NULL;
        out->south = NULL;
    return out;    
}

void premiere_cellule(cell c, grid* pg){
    ddl_fille ini = malloc(sizeof *ini);/*Première ligne*/
        ini->val = c;
        ini->x = 0;
        ini->y = 0;
        ini->west = NULL;
        ini->east = NULL;
    (*pg)->ligne = ini;
    (*pg)->ligne->val = c;
}

int est_libre(grid g, int x, int y){
    return (test_ligne_vide(get_ligne(y,g))==NULL || get_case(g, x, y)==NULL);
}

void free_grille(grid* pg);/*TODO*/
int placer_cell(cell c, grid* pg, int x, int y);/*TODO*/

// --- Fonctions de base de liste chainee mère ---

/*  @requires : l est une liste doublement chaînée (fille) valide
    @assigns  : nothing
    @ensures  : retourne 1 si l est vide et 0 sinon*/
int test_ligne_vide(ddl_fille l){
    return (l==NULL);
}

/*  @requires : g est une liste doublement chaînée (mère) valide, c une cellule valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à au nord de la liste l */
ddl_mere cons_ligne_north(cell c, ddl_mere l){
    ddl_mere res = malloc(sizeof(ddl_mere));
    res->ligne = NULL;
    res->y = (l->y)+1; //décalage vers le nord : +1
    res->north = NULL;
    res->south = l;
    return res;
}

/*  @requires : g est une liste doublement chaînée (mère) valide, c une cellule valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à au sud de la liste l */
ddl_mere cons_ligne_south(cell c, ddl_mere l){
    ddl_mere res = malloc(sizeof(ddl_mere));
    res->ligne = NULL;
    res->y = (l->y)-1; //décalage vers le sud : -1
    res->north = l;
    res->south = NULL;
    return res;
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (mère) valide, c une cellule valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c au nord de la liste *pl */
void push_north(cell c, ddl_mere *pl){
    ddl_mere start = pl; /*Pointeur vers le début de la liste mère*/
    *pl = cons_ligne_north(c, *pl);
    pl = start; /*Replace le pointeur de la liste mère au début*/
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (mère) valide, c une cellule valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c au sud de la liste *pl */
void push_south(cell c, ddl_mere *pl){
    ddl_mere start = pl; /*Pointeur vers le début de la liste mère*/
    *pl = cons_ligne_south(c, *pl);
    pl = start; /*Replace le pointeur de la liste mère au début*/
}

/*  @requires : l est une liste doublement chaînée (mère) valide non-vide
    @assigns  : nothing
    @ensures  : retourne la liste fille au nord de la liste*/
ddl_fille peek_most_north(ddl_mere l){
    if (l == NULL){
        printf("Error peek_most_orth : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while (l->north != NULL){
        l = l->north;
    }
    return l->ligne;
}

/*  @requires : l est une liste doublement chaînée (mère) valide non-vide
    @assigns  : nothing
    @ensures  : retourne la liste fille au nord de la liste*/
ddl_fille peek_most_south(ddl_mere l){
    if (l == NULL){
        printf("Error peek_most_south : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while (l->south != NULL){
        l = l->south;
    }
    return l->ligne;
}

// --- Fonctions de base de liste chainee fille ---

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la ligne d'ordonnée y de g */
ddl_fille get_ligne(int y, grid g){
    int i = g->y;
    if (y==i) return g->ligne;
    if (y>0){//Si la ligne y est vers le nord
        while (i<y && g->north != NULL){
            i++;
            g = g->north;
        }
    }
    else{//Si la ligne est vers le sud
        while (i>y && g->south != NULL){
            i--;
            g = g->south;
        }
    }
    //g->y = y ou g = NULL
    if (g==NULL) return NULL;
    //g->y = y
    return g->ligne; 
}

/*  @requires : l est une liste doublement chaînée (fille) valide, c une cellule valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à l'ouest de la liste l */
ddl_fille cons_colonne_west(cell c, ddl_fille l){
    ddl_fille res = malloc(sizeof(ddl_fille));
    res->val = c;
    res->x = (l->x)-1; //décalage à gauche : -1
    res->y = l->y;
    res->west = NULL;
    res->east = l;
    return res;
}

/*  @requires : l est une liste doublement chaînée (fille) valide, c une cellule valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à l'est de la liste l */
ddl_fille cons_colonne_east(cell c, ddl_fille l){
    ddl_fille res = malloc(sizeof(ddl_fille));
    res->val = c;
    res->x = (l->x)+1;  //décalage à droite : +1
    res->west = l;
    res->east = NULL;
    return res;
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide, c une cellule valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c à l'ouest de la liste *pl */
void push_west(cell c, ddl_fille *pl){
    ddl_fille start = pl; /*Pointeur vers le début de la liste fille*/
    *pl = cons_colonne_west(c, *pl);
    pl = start; /*Replace le pointeur de la liste fille au début*/
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide, c une cellule valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c à l'est de la liste *pl */
void push_east(cell c, ddl_fille *pl){
    ddl_fille start = pl; /*Pointeur vers le début de la liste fille*/
    *pl = cons_colonne_east(c, *pl);
    pl = start; /*Replace le pointeur de la liste fille au début*/
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide non-vide
    @assigns  : *pl
    @ensures  : retourne l'élément à l'ouest de la liste et le retire de la liste*/
/*cell pop_west(ddl_fille* pl){
    if (*pl == NULL){
        printf("Error pop_west : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while ((*pl)->west != NULL){
        *pl = (*pl)->west;
    }
    cell e = (*pl)->val; //On stocke l'élément à l'ouest de la liste
    *pl = (*pl)-> east; //On recule vers l'est dans la liste
    return e; //Comment retirer l'élément ??
}*/

/*  @requires : l est une liste doublement chaînée (fille) valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément à l'ouest de la liste*/
cell peek_west(ddl_fille l){
    if (l == NULL){
        printf("Error peek_west : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while (l->west != NULL){
        l = l->west;
    }
    return l->val;
}

/*  @requires : l est une liste doublement chaînée (fille) valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément à l'est de la liste*/
cell peek_east(ddl_fille l){
    if (l == NULL){
        printf("Error peek_east : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'est
    while (l->east != NULL){
        l = l->east;
    }
    return l->val;
}

// --- Fonctions utilitaires ---

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la liste pointant vers la cellule située aux coordonnées (x,y) de la grille g ; s'il n'existe pas, renvoie null*/
ddl_fille get_case(grid g, int x, int y){
    ddl_fille ligne = get_ligne(y, g); //Ligne d'ordonnée y
    int i = ligne->x;
    if (x==i) return ligne;
    if (x>i){//Si la case x est vers l'est
        while (i<x && ligne->east != NULL){
            i++;
            ligne = ligne->east;
        }
    }
    else{//Si la case x est vers l'ouest
        while (i>x && ligne->west != NULL){
            i--;
            ligne = ligne->west;
        }
    }
    //ligne->x = x ou ligne = NULL
    if (ligne==NULL) return NULL;
    //ligne->x = x
    return NULL;
}

cell get_cell(grid g, int x, int y){
    if (get_case(g,x,y) == NULL) return NULL;
    return (get_case(g,x,y))->val;
}

int deplacer_cell(grid* pg, int x1, int y1, int x2, int y2){
    cell c = get_cell(*pg, x1, y1); //Cellule à déplacer
    if (supp_cell_grille(pg, x1, y1) == 0)
        return -1;
    if (placer_cell(c, pg, x2, y2) == 0)
        return 1;
    return 0;
}

//S'il y a une rangée de NULL qui va jusqu'à l'extremité, alors supprime la rangée.
int supp_cell_grille(grid* pg, int x, int y);/*TODO*/

// --- TAILLES ---

int taille_grille(direction d, grid g){
    switch (d) {
    case west:
        return taille_west(g); break;
    case north:
        return taille_north(g); break;
    case east:
        return taille_east(g); break;
    case south:
        return taille_south(g); break;
    default: 
        printf("Error direction doesn't exist\n");
        exit(EXIT_FAILURE);
        break;
    }
}

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au nord de la grille*/
int taille_north(grid g){
    int out = g->y;
    //Accès à la case la plus au nord
    while (g->north != NULL){
        g = g->north;
        out++; //décalage en haut "augmentation" : +1
    }
    return out;
}

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus au sud de la grille*/
int taille_south(grid g){
    int out = g->y;
    //Accès à la case la plus au nord
    while (g->south != NULL){
        g = g->south;
        out--; //décalage en bas "diminution" : -1
    }
    return out;
}

/*  @requires : l est une liste doublement chaînée (fille) valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest de la liste*/
int taille_fille_west(ddl_fille l){
    int out = l->x;
    //Accès à la case la plus à l'ouest
    while (l->west != NULL){
        l = l->west;
        out--; //décalage à gauche : -1
    }
    return out;
}

/*  @requires : l est une liste doublement chaînée (fille) valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la liste*/
int taille_fille_east(ddl_fille l){
    int out = l->x;
    //Accès à la case la plus à l'est
    while (l->east != NULL){
        l = l->east;
        out++; //décalage à droite : +1
    }
    return out;
}

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'ouest de la grille*/
int taille_west(grid g){
    //Recherche de la taille de la ligne la plus petite
    int min = 0;
    ddl_mere l_north = g; //Parcourt la liste vers le nord
    ddl_mere l_south = g; //Parcourt la liste vers le sud
    while (l_north != NULL){
        int taille_fw = taille_fille_west(l_north -> ligne);
        if (taille_fw < min)
            min = taille_fw;
        l_north = l_north -> north;
    }
    while (l_south != NULL){
        int taille_fw = taille_fille_west(l_south -> ligne);
        if (taille_fw < min)
            min = taille_fw;
        l_south = l_south -> south;
    }
    return min;
}

/*  @requires : g est une grille valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la grille*/
int taille_east(grid g){
    //Recherche de la taille de la ligne la plus grande
    int max = 0;
    ddl_mere l_north = g; //Parcourt la liste vers le nord
    ddl_mere l_south = g; //Parcourt la liste vers le sud
    while (l_north != NULL){
        int taille_fw = taille_fille_east(l_north -> ligne);
        if (taille_fw > max)
            max = taille_fw;
        l_north = l_north -> north;
    }
    while (l_south != NULL){
        int taille_fw = taille_fille_east(l_south -> ligne);
        if (taille_fw > max)
            max = taille_fw;
        l_south = l_south -> south;
    }
    return max;
}

int taille_ligne_direction(direction d, grid g, int i){
    switch (d){
        case west:
            return taille_fille_west(get_ligne(i, g)); break;
        case east:
            return taille_fille_east(get_ligne(i, g)); break;
        default: 
            printf("taille_ligne_direction : direction must be west or east\n");
            exit(EXIT_FAILURE);
            break;
    }
}

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
        printf("Error get_at : index pos out of range.\n");
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
        int j = rand()%(n-i); //Choix d'un entier parmis les éléments restants de la liste l (entre 0 et n-i-1)
        elt chosen = get_at(j, l); //Element choisi par l'aléatoire
        push(chosen, &out);
        enlever(chosen, &l);
    }
    return out;
}