#include <stdlib.h>
#include <stdio.h>
#include "structure.h"

/*----------- Plateau = Grille : liste doublement chainee imbriquee dans liste doublement chainee -----------*/

/*----Liste doublement chainee fille----*/
typedef struct maillon * ddl_fille;
typedef struct maillon cell;

struct maillon {
    //Elements de la liste doublement chainee
    carte card;             //carte posee sur ces coordonnees (x,y)
    int x; //abscisse de la ligne (offset_from_center : 0 si centre, 1 si case a droite, -1 si case a gauche etc)
    int is_visible;         //0 si la carte est face cachée ; 1 si la carte est retournée
    int is_activated;       //1 si l'effet de la carte a été activée ; 0 sinon
    //Pointeurs vers le "maillon" precedent ou suivant
    ddl_fille west;
    ddl_fille east;
};

/*----Liste doublement chainee mere----*/
//Liste doublement chaine mere = Pointeur vers un maillon "colonne"
typedef struct plateau_base colonne;
typedef colonne* ddl_mere; // == type plateau

struct plateau_base {
    //Element de la liste doublement chainee
    ddl_fille ligne;
    int y; //ordonnée de la colonne (offset_from_center : 0 si centre, 1 si colonne d'en dessous, -1 si colonne d'au dessus etc)
    //Pointeurs vers le "maillon" precedent ou suivant
    ddl_mere north;
    ddl_mere south;
};

/*----Fonctions----*/
plateau init_grille(carte c){
    plateau out = malloc(sizeof *out);
    ddl_fille ini = malloc(sizeof *out);
        ini->card = c;
        ini->is_visible = 0;
        ini->is_activated = 0;
        ini->x = 0;
        ini->west = NULL;
        ini->east = NULL;
    out->ligne = ini;
    out->y = 0;
    out->north = NULL;
    out->south = NULL;
    return out;    
}

/*Fonctions de base de liste chainee fille*/
/*  @requires :
    @assigns  :
    @ensures  : */
int test_colonne_vide(ddl_fille l){
    return (l==NULL);
}

/*  @requires : l est une liste doublement chaînée (fille) valide, c une carte valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à l'ouest de la liste l */
ddl_fille cons_colonne_west(carte c, ddl_fille l){
    //Accès à la case la plus à l'ouest de l
    int offset = l->x;
    while (l->west != NULL){
        l = l-> west;
        offset--;
    }
    ddl_fille res = malloc(sizeof(ddl_fille));
    res->card = c;
    res->x = offset; //décalage à gauche : -1
    res->is_visible = 0;
    res->is_activated = 0;
    res->west = NULL;
    res->east = l;
    return res;
}

/*  @requires : l est une liste doublement chaînée (fille) valide, c une carte valide
    @assigns  : nothing
    @ensures  : renvoie une nouvelle liste avec c à l'est de la liste l */
ddl_fille cons_colonne_east(carte c, ddl_fille l){
    ddl_fille res = malloc(sizeof(ddl_fille));
    res->card = c;
    res->x = (l->x)+1;  //décalage à gauche : +1
    res->is_visible = 0;
    res->is_activated = 0;
    res->west = l;
    res->east = NULL;
    return res;
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide, c une carte valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c à l'ouest de la liste *pl */
//<=>push à l'ouest
void add_west(carte c, ddl_fille *pl){
    *pl = cons_colonne_west(c, *pl);
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide, c une carte valide
    @assigns  : *pl
    @ensures  : renvoie une nouvelle liste avec c à l'est de la liste *pl */
//<=>push à l'ouest
void add_east(carte c, ddl_fille *pl){
    *pl = cons_colonne_east(c, *pl);
}

/*  @requires : pl est un pointeur valide vers une liste doublement chaînée (fille) valide non-vide
    @assigns  : *pl
    @ensures  : retourne l'élément à l'ouest de la liste et le retire de la liste*/
/*carte pop_west(ddl_fille* pl){
    if (*pl == NULL){
        printf("Error pop_west : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while ((*pl)->west != NULL){
        *pl = (*pl)->west;
    }
    carte e = (*pl)->card; //On stocke l'élément à l'ouest de la liste
    *pl = (*pl)-> east; //On recule vers l'est dans la liste
    return e; //Comment retirer l'élément ??
}*/

/*  @requires : l est une liste doublement chaînée (fille) valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément à l'ouest de la liste*/
carte peek_west(ddl_fille l){
    if (l == NULL){
        printf("Error peek_west : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'ouest
    while (l->west != NULL){
        l = l->west;
    }
    return l->card;
}

/*  @requires : l est une liste doublement chaînée (fille) valide non-vide
    @assigns  : nothing
    @ensures  : retourne l'élément à l'est de la liste*/
carte peek_east(ddl_fille l){
    if (l == NULL){
        printf("Error peek_east : list is empty.\n");
        exit(EXIT_FAILURE);
    }
    //Accès à la case la plus à l'est
    while (l->east != NULL){
        l = l->east;
    }
    return l->card;
}


// --- TAILLES ---

int taille_north(plateau g){
    int out = g->y;
    //Accès à la case la plus au nord
    while (g->north != NULL){
        g = g->north;
        out--; //décalage à "gauche" (haut) : -1
    }
    return out;
}

int taille_south(plateau g){
    int out = g->y;
    //Accès à la case la plus au nord
    while (g->south != NULL){
        g = g->south;
        out++; //décalage à "droite" (bas) : +1
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
        out--; //décalage à gauche : +1
    }
    return out;
}

/*  @requires : l est une liste doublement chaînée (fille) valide
    @assigns  : nothing
    @ensures  : retourne la coordonnée de la case située la plus à l'est de la liste*/
int taille_fille_east(ddl_fille l){
    int out = l->x;
    //Accès à la case la plus à l'ouest
    while (l->east != NULL){
        l = l->east;
        out++; //décalage à gauche : -1
    }
    return out;
}

int taille_west(plateau g){
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

int taille_east(plateau g){
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

int taille_ligne_west(plateau g, int i){
    int offset = g->y;
    if (offset > i) //Cas où on est en dessous de la ligne i
        while(g->y != i) //On va vers le nord
            g = g->north;
    if (offset < i) //Cas où on est au dessus de la ligne i
        while(g->y != i) //On va vers le sud
            g = g->south;
    return taille_fille_west(g->ligne);
}

int taille_ligne_east(plateau g, int i){
    int offset = g->y;
    if (offset > i) //Cas où on est en dessous de la ligne i
        while(g->y != i) //On va vers le nord
            g = g->north;
    if (offset < i) //Cas où on est au dessus de la ligne i
        while(g->y != i) //On va vers le sud
            g = g->south;
    return taille_fille_east(g->ligne);
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