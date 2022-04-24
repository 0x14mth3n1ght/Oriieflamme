#include "../header/plateau.h"
#include "../header/structure.h"

typedef struct plateau_base *plateau;

struct plateau_base{
    grid grille;
    faction faction1;
    faction faction2;
    int nb_cartes_posees;
    int nb_cartes_visibles;
    int nb_cartes_activees;
    liste cartes_visibles;
    liste cartes_activees;
};

plateau cree_plateau(){
    plateau resultat;
    resultat = malloc();
    resultat->grille = init_grille();
    resultat->faction1 = faction_defaut_1;
    resultat->faction2 = faction_defaut_2;
    resultat->nb_cartes_posees = 0;
    resultat->nb_cartes_visibles = 0;
    resultat->nb_cartes_activees = 0;
    resultat->cartes_visibles = cree_liste_vide();
    resultat->nb_cartes_activees = cree_liste_vide();
    return resultat;
};

void detruire_plateau(plateau *p){
    free_grille(&(*p)->grille);
    free_liste(&(*p)->nb_cartes_visibles);
    free_liste(&(*p)->nb_cartes_activees);
    free_liste(&(*p)->faction1.main);
    free_liste(&(*p)->faction1.pioche);
    free_liste(&(*p)->faction2.main);
    free_liste(&(*p)->faction2.pioche);
    free(*p);
};

int reinitialisation(plateau *p){
    /* on verifie si partie terminee */
    if (get_nb_victoires((*p)->faction1) == nb_manches_gagnantes || get_nb_victoires((*p)->faction2) == nb_manches_gagnantes)
    {
        return 0;
    }
    else{
        /* recuperation du nom des deux factions */
        char* n_f1 = (*p)->faction1.nom;
        char* n_f2 = (*p)->faction2.nom;
        detruire_plateau(&p);
        *p = cree_plateau();
        set_name(&((*p)->faction1), n_f1);
        set_name(&((*p)->faction2), n_f2);
        set_pioche_defaut(&((*p)->faction1));
        set_pioche_defaut(&((*p)->faction2));
        melanger_pioche(&((*p)->faction1));
        melanger_pioche(&((*p)->faction2));
        repiocher(&((*p)->faction1));
        repiocher(&((*p)->faction2));
        return 1;
    };  
};

/* listes pour les factions */

struct node{
    faction val;
    liste_faction next;
};

liste_faction cons_faction(faction f, liste_faction n){
    liste_faction res = malloc(sizeof(liste_faction));
    res->val = f;
    res->next = n;
    return res;
};

void free_liste_faction(liste_faction* pl){
    while (*pl != NULL){
        liste_faction tmp = *pl;
        *pl = (*pl)->next;
        free(tmp);
    }
};

liste_faction retourne_factions(plateau p){
    l = NULL;
    l = cons_faction(p->faction2, cons_faction(p->faction1, l));
    return l;
};

int pose_carte(plateau *p, faction *f, carte car, int x, int y){
    if (get_cell((*p)->grille, x, y) != NULL){
        if (get_occupee(get_cell((*p)->grille, x, y)) == 0){
            get_cell((*p)->grille, x, y)->c = car;
            get_cell((*p)->grille, x, y)->fac = *f;
            get_cell((*p)->grille, x, y)->occupee = 1;
            enlever(car, &((*f)->main));
            (*p)->nb_cartes_posees += 1;
        }
    }
};

int retourne_carte(plateau *p, int x, int y){
    if (get_cell((*p)->grille, x, y) != NULL){
        if (get_occupee(get_cell((*p)->grille, x, y)) == 1){
            get_cell((*p)->grille, x, y)->visible = 1;
            (*p)->nb_cartes_visibles += 1;
        }
    }
};

int cachee_visible_existe(plateau *p, int x, int y){
    cell_base cellule = get_cell((*p)->grille, x ,y);
    if (cellule =! NULL){
        if (cellule->occupee == 0){
            return 3;
        }
        if (cellule->visible == 0){
            return 0;
        }
        if (cellule->visible == 1 && cellule->activee == 0){
            return 1;
        }
        if (cellule->visible == 1 && cellule->activee == 1){
            return 2;
        }
    }
};

carte get_card(struct cell_base cellule){
    return cellule.c;
};

faction get_faction(struct cell_base cellule){
    return cellule.f;
};

int get_occupee(struct cell_base cellule){
    return cellule.occupee;
};

int get_visible(struct cell_base cellule){
    return cellule.visible;
};

int get_activee(struct cell_base cellule){
    return cellule.activee;
};

grid get_grid(plateau p){
    return p->grille;
};

int get_nb_cartes_posees(plateau p){
    return p->nb_cartes_posees;
};

int get_nb_cartes_visibles(plateau p){
    return p->nb_cartes_visibles;
};

int get_nb_cartes_activees(plateau p){
    return p->nb_cartes_activees;
};

liste get_cartes_visibles(plateau p){
    return p->cartes_visibles;
};

liste get_cartes_activees(plateau p){
    return p->cartes_activees;
};

