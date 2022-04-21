#include "../header/faction.h"
#include "../header/carte.h"
#include "../header/structure.h"

struct faction_base {
    char* nom;
    int points_DDRS;
    liste main;
    liste pioche; 
    int nb_manches_gagnees;
    /* vaut 0 lorsque la faction est créee */
    int a_remelange;
};

int a_remelanger_main(faction f){
    return f->a_remelange;
};

void vider_main(faction *f){
    if (test_vide((*f)->main) != 1){
        while (test_vide((*f)->main) != 1){
            push(pop((*f)->main), (*f)->pioche);
        }
    }
};

void melanger_pioche(faction *f){
    (*f)->pioche = melanger((*f)->pioche);
};

/* modifier avec & lorsque la fonction prend un pointeur vers liste */

void repiocher(faction *f){
    if (test_vide((*f)->main) != 1){
        while (len_liste((*f)->main) < 8){
            push(pop(&((*f)->pioche)), &((*f)->main));
        }
    }
};

void remelanger_main(faction *f){
    if (a_remelanger_main(f) == 0){
        vider_main(*f);
        melanger_pioche(*f);
        repiocher(*f);
    }
};

char* get_faction_nom(faction f){
    return f->nom;
};

int get_ptsddrs_faction(faction f){
    return f->points_DDRS;
};

void set_ptsddrs_faction(faction *f, int i){
    (*f)->points_DDRS = i;
};

void add_ddrs(faction *f, int i){
    (*f)->points_DDRS += i;
};

liste get_main_faction(faction f){
    return f->main;
};

int get_nb_victoires(faction f){
    return f->nb_manches_gagnees;
};

void set_nb_victoires(faction *f, int i){
    (*f)->nb_manches_gagnees = i;
};

liste get_pioche(faction f){
    return f->pioche;
};

/* implémentation des const carte FISE
FISE->nom =... */

void set_pioche_defaut(faction *f){
    liste pioche_defaut = cree_liste_vide(); 
    /* ...
    liste_add....
    for i in (i=0; i < nb_occurences; i++){
        ....
    }
     */
    (*f)->pioche = pioche_defaut;
};



