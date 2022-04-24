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


