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
    if (get_nb_victoires((*p)->faction1) == nb_manches_gagnantes || get_nb_victoires((*p)->faction1) == nb_manches_gagnantes)
    {
        return 0;
    }
    else{
        /* recupertion du nom des deux factions */
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

/*
liste retourne_factions(plateau p){
    liste l = cree_liste_vide(); 
}
*/

/*
int pose_carte(plateau *p, faction *f, carte c, int x, int y){
}
*/

/* pose carte comme pose cellule aksip */


