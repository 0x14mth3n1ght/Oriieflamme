#include "../header/faction.h"
#include "../header/carte.h"
#include "../header/structure.h"
#include <stdlib.h>
#include <stdio.h>

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
        while (len_liste((*f)->main) < nb_cartes_main_debut_manche){
            push(pop(&((*f)->pioche)), &((*f)->main));
        }
};

void remelanger_main(faction *f){
    if (a_remelanger_main(*f) == 0){
        vider_main(f);
        melanger_pioche(f);
        repiocher(f);
    }
    (*f)->a_remelange = 1;
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
    int i;
    for (i = 1; i <= FISE.occurences; i++){
        push(FISE, &pioche_defaut);
    }
    for (i = 1; i <= FISA.occurences; i++){
        push(FISA, &pioche_defaut);
    }
    for (i = 1; i <= FC.occurences; i++){
        push(FC, &pioche_defaut);
    }
    for (i = 1; i <= ECOLO.occurences; i++){
        push(ECOLO, &pioche_defaut);
    }
    for (i = 1; i <= IIE.occurences; i++){
        push(IIE, &pioche_defaut);
    }
    for (i = 1; i <= SSALCOOL.occurences; i++){
        push(SSALCOOL, &pioche_defaut);
    }
    for (i = 1; i <= ALCOOL.occurences; i++){
        push(ALCOOL, &pioche_defaut);
    }
    for (i = 1; i <= CAFE.occurences; i++){
        push(CAFE, &pioche_defaut);
    }
    for (i = 1; i <= THE.occurences; i++){
        push(THE, &pioche_defaut);
    }
    for (i = 1; i <= ECOC.occurences; i++){
        push(ECOC, &pioche_defaut);
    }
    for (i = 1; i <= REPRO.occurences; i++){
        push(REPRO, &pioche_defaut);
    }
    for (i = 1; i <= ISOL.occurences; i++){
        push(ISOL, &pioche_defaut);
    }
    for (i = 1; i <= PSN.occurences; i++){
        push(PSN, &pioche_defaut);
    }
    for (i = 1; i <= HS.occurences; i++){
        push(HS, &pioche_defaut);
    }
    for (i = 1; i <= KB.occurences; i++){
        push(KB, &pioche_defaut);
    }
    for (i = 1; i <= KG.occurences; i++){
        push(KG, &pioche_defaut);
    }
    for (i = 1; i <= MM.occurences; i++){
        push(MM, &pioche_defaut);
    }
    for (i = 1; i <= VY.occurences; i++){
        push(VY, &pioche_defaut);
    }
    for (i = 1; i <= JS.occurences; i++){
        push(JS, &pioche_defaut);
    }
    for (i = 1; i <= FB.occurences; i++){
        push(FB, &pioche_defaut);
    }
    for (i = 1; i <= CD.occurences; i++){
        push(CD, &pioche_defaut);
    }
    for (i = 1; i <= ALL.occurences; i++){
        push(ALL, &pioche_defaut);
    }
    for (i = 1; i <= GB.occurences; i++){
        push(GB, &pioche_defaut);
    }
    for (i = 1; i <= CM.occurences; i++){
        push(CM, &pioche_defaut);
    }
    for (i = 1; i <=TL.occurences; i++){
        push(TL, &pioche_defaut);
    }
    for (i = 1; i <=JF.occurences; i++){
        push(JF, &pioche_defaut);
    }
    for (i = 1; i <=DW.occurences; i++){
        push(DW, &pioche_defaut);
    }
    for (i = 1; i <=DADC.occurences; i++){
        push(DADC, &pioche_defaut);
    }
    for (i = 1; i <=EL.occurences; i++){
        push(EL, &pioche_defaut);
    }
    for (i = 1; i <=LPACAV.occurences; i++){
        push(LPACAV, &pioche_defaut);
    }
    for (i = 1; i <=KS.occurences; i++){
        push(KS, &pioche_defaut);
    }
    for (i = 1; i <=LP.occurences; i++){
        push(LP, &pioche_defaut);
    }
    (*f)->pioche = pioche_defaut;
};

void set_pioche(faction *f, liste cartes){
    (*f)->pioche = cartes;
};

void set_main(faction *f, liste cartes){
    (*f)->main = cartes;
};

void set_name(faction *f, char* n){
    (*f)->nom = n;
};

int get_faction_id(faction f){
    return f->id;
};

void set_faction_id(faction *f, int n){
    (*f)->id = n;
}

faction set_faction_defaut(){
    faction f= malloc(10*sizeof(faction));
    set_faction_id(&f,0);
    set_name(&f,"");
    set_ddrs(&f,0);
    set_main(&f,NULL);
    set_pioche(&f,NULL);
    set_nb_victoires(&f,0);
    f->a_remelange=0;
    //set_pioche_defaut(&f);
    return f;
};

void print_faction(faction f){
    printf("id=%d,\n nom=%s,\n points_DDRS=%d,\n main=", (*f).id, (*f).nom, (*f).points_DDRS);
    print_liste((*f).main);
    printf("pioche=");
    print_liste((*f).pioche);
    printf("nb_manches_gagnees=%d,\n a_remelange=%d\n", (*f).nb_manches_gagnees, (*f).a_remelange);
}