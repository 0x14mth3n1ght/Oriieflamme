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
            push(pop(&((*f)->main)), &((*f)->pioche));
        }
    }
};

void melanger_pioche(faction *f){
    (*f)->pioche = melanger((*f)->pioche);
};

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

int get_ddrs(faction f){
    return f->points_DDRS;
};

void set_ddrs(faction *f, int i){
    (*f)->points_DDRS = i;
};

void add_ddrs(faction *f, int i){
    (*f)->points_DDRS += i;
};

liste get_main(faction f){
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

void set_pioche_defaut(faction *f){
    liste pioche_defaut = cree_liste_vide(); 
    push(FISE, &pioche_defaut);
    push(FISE, &pioche_defaut);
    push(FISE, &pioche_defaut);
    push(FISE, &pioche_defaut);
    push(FISA, &pioche_defaut);
    push(FISA, &pioche_defaut);
    push(FISA, &pioche_defaut);
    push(FISA, &pioche_defaut);
    push(FC, &pioche_defaut);
    push(FC, &pioche_defaut);
    push(FC, &pioche_defaut);
    push(FC, &pioche_defaut);
    push(ECOLO, &pioche_defaut);
    push(ECOLO, &pioche_defaut);
    push(IIE, &pioche_defaut);
    push(IIE, &pioche_defaut);
    push(SSALCOOL, &pioche_defaut);
    push(ALCOOL, &pioche_defaut);
    push(CAFE, &pioche_defaut);
    push(CAFE, &pioche_defaut);
    push(CAFE, &pioche_defaut);
    push(THE, &pioche_defaut);
    push(THE, &pioche_defaut);
    push(THE, &pioche_defaut);
    push(ECOC, &pioche_defaut);
    push(REPRO, &pioche_defaut);
    push(ISOL, &pioche_defaut);
    push(PSN, &pioche_defaut);
    push(HS, &pioche_defaut);
    push(KB, &pioche_defaut);
    push(KG, &pioche_defaut);
    push(MM, &pioche_defaut);
    push(VY, &pioche_defaut);
    push(JS, &pioche_defaut);
    push(FB, &pioche_defaut);
    push(CD, &pioche_defaut);
    push(ALL, &pioche_defaut);
    push(GB, &pioche_defaut);
    push(CM, &pioche_defaut);
    push(TL, &pioche_defaut);
    push(JF, &pioche_defaut);
    push(DW, &pioche_defaut);
    push(DADC, &pioche_defaut);
    push(EL, &pioche_defaut);
    push(LPACAV, &pioche_defaut);
    push(KS, &pioche_defaut);
    push(LP, &pioche_defaut);
    (*f)->pioche = pioche_defaut;
};

void set_pioche(faction *f, liste cartes){
    (*f)->pioche = cartes;
};

void set_main(faction *f, liste cartes){
    (*f)->main = cartes;
};




