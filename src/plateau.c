#include "../header/plateau.h"
#include "../header/structure.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct plateau_base *plateau;

struct plateau_base{
    grid grille;
    faction faction1;
    faction faction2;
    int nb_cartes_posees;
    int nb_cartes_visibles;
    int nb_cartes_activees;
    int nb_ALL_retournee;
    liste cartes_visibles;
    liste cartes_activees;
};

/**
 * @brief fonction permettant de construire une cell avec une carte donnee retournee
 * @param car une carte
 * @param fac une faction 
*/
cell construcuteur_cell(carte car, faction fac){
    cell out = malloc(sizeof(cell));
    out->c = car;
    out->f = fac;
    out->occupee = 1;
    out->visible = 0;
    out->activee = 0;
    return out;
};

plateau cree_plateau(){
    plateau resultat = malloc(100*sizeof(plateau));

    init_cartes();
    /* initialisation des attributs */
    grid g = init_grille();
    for (int i=0; i<31; i++)
        printf("g[%i] = %p\n", i, g[i]);
    faction f1 = set_faction_defaut();
    faction f2 = set_faction_defaut();
    liste l_visibles = cree_liste_vide();
    liste l_activees = cree_liste_vide();
    /* initialisation des attributs du plateau */
    resultat->grille = g;
    resultat->faction1 = f1;
    resultat->faction2 = f2;
    resultat->nb_cartes_posees = 0;
    resultat->nb_cartes_visibles = 0;
    resultat->nb_cartes_activees = 0;
    resultat->cartes_visibles = l_visibles;
    resultat->cartes_activees = l_activees;
    resultat->nb_ALL_retournee = 0;
    set_faction_id(&(resultat->faction1), 1);
    set_faction_id(&(resultat->faction2), 2);
    set_pioche_defaut(&(resultat->faction1));
    set_pioche_defaut(&(resultat->faction2));
    melanger_pioche(&(resultat->faction1));
    melanger_pioche(&(resultat->faction2));
    for (int i=0; i<31; i++)
        printf("r->g[%i] = %p\n", i, (resultat->grille)[i]);
    return resultat;
}

void detruire_plateau(plateau *p){
        printf("aa");
    fflush(stdout);
    free_grille(&(*p)->grille);
    printf("aa");
    fflush(stdout);
    free_liste(&((*p)->cartes_visibles));
    free_liste(&((*p)->cartes_activees));
    free_liste(&((*p)->faction1.main));
    free_liste(&((*p)->faction1.pioche));
    free_liste(&((*p)->faction2.main));
    free_liste(&((*p)->faction2.pioche));
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

        detruire_plateau(p);
        printf("aa");
        fflush(stdout);
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

void retourne_factions(plateau p, faction *pf1, faction *pf2){
  *pf1 = p->faction1;
  *pf2 = p->faction2;
}

int pose_carte(plateau *p, faction *fac, carte car, int x, int y){
    if (get_cell((*p)->grille, x, y) != NULL){
        if (get_occupee(get_cell((*p)->grille, x, y)) == 0){
            cell nouvelle_cell = construcuteur_cell(car, *fac);
            enlever(car, &((*fac).main));
            (*p)->nb_cartes_posees += 1;
            placer_cell(nouvelle_cell, &(*p)->grille, x , y);
            return 1;
        }
        else return 0;
    }
    else return 0;
}

int retourne_carte(plateau *p, int x, int y){
    grid g = get_grid(*p);
    //Cellule coordonnees x y
    cell cellule = get_cell(g, x, y);
    if (cellule != NULL){
        if (get_occupee(cellule) == 1 && get_visible(cellule) == 0){
            carte car = get_card(cellule);
            cellule->visible = 1;
            (*p)->nb_cartes_visibles += 1;
            push(car, &(*p)->cartes_visibles);
            //Test de fin de manche
            if ((*p)->nb_cartes_visibles == (*p)->nb_cartes_posees - (*p)->nb_ALL_retournee){//Si toutes les cartes posées ont été retournées, moins les dernières cartes du plateau affectés par l'effet de la carte Anne-Laure Ligozat, qu'on ignorera
                reinitialisation(p); //Termine la manche
                return 1;
            }
            return 1;
	    }
        else return 0;
    }
    else return 0;
};


int cachee_visible_existe(plateau *p, int x, int y){
    cell cellule = get_cell((*p)->grille, x ,y);
    if (cellule != NULL){
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
    return 3;
};

/**
 * @brief Supprime la case @b (x,y) du plateau @b *pp et modifie les bons compteurs de cartes sur le plateau
 * 
 * @param pp pointeur valide vers un plateau valide
 * @param x abscisse de la case à supprimer
 * @param y ordonnée de la case à supprimer
 * @return 1 s'il y avait une carte en @b (x,y) et qu'elle a été supprimée, 0 s'il n'y avait pas de carte en @b (x,y), -1 si autre erreur inconnue
 */
int supp_case(plateau* pp, int x, int y){
    grid g = get_grid(*pp);
    switch (cachee_visible_existe(pp, x, y)){
        case 0: //carte face cachée
            supp_cell_grille(&g, x, y);
            ((*pp)->nb_cartes_posees)--;
            return 1;
            break;
        case 1: //carte face visible
            supp_cell_grille(&g, x, y);
            ((*pp)->nb_cartes_visibles)--;
            ((*pp)->nb_cartes_posees)--;
            return 1;
            break;
        case 2: //carte face visible et activée
            supp_cell_grille(&g, x, y);
            ((*pp)->nb_cartes_activees)--;
            ((*pp)->nb_cartes_visibles)--;
            ((*pp)->nb_cartes_posees)--;
            return 1;
            break;
        case 3: //pas de carte
            return 0;
            break;
        default: //erreur
            return -1;
            break;
    }
}

carte get_card(cell cellule){
    return cellule->c;
};

faction get_faction(cell cellule){
    return cellule->f;
};

int get_occupee(cell cellule){
    return cellule->occupee;
};

int get_visible(cell cellule){
    return cellule->visible;
};

int get_activee(cell cellule){
    return cellule->activee;
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

void set_nb_cartes_posees(plateau *p, int n){
    (*p)->nb_cartes_posees = n;
};

void set_nb_cartes_visibles(plateau *p, int n){
    (*p)->nb_cartes_visibles = n;
};

void set_nb_cartes_activees(plateau *p, int n){
    (*p)->nb_cartes_activees = n;
};

int get_ALL(plateau p){
    return p->nb_ALL_retournee;
};

void set_ALL(plateau *p, int n){
    (*p)->nb_ALL_retournee = n;
};

//id des cartes (pour la clarté du code)
#define id_fise 1
#define id_fisa 2
#define id_fc 3
#define id_ecologiie 4
#define id_liiens 5
#define id_ssa 6
#define id_alcool 7
#define id_cafe 8
#define id_the 9
#define id_ecocup 10
#define id_reprographie 11
#define id_idb 12
#define id_psn 13
#define id_heure_sup 14
#define id_kb 15
#define id_kg 16
#define id_mm 17
#define id_vy 18
#define id_js 19
#define id_fb 20
#define id_cd 21
#define id_all 22
#define id_gb 23
#define id_cm 24
#define id_tl 25
#define id_jf 26
#define id_dw 27
#define id_dadc 28
#define id_el 29
#define id_lpacav 30
#define id_ks 31
#define id_lp 32

/**
 * @brief Teste si @b c est dans les @b n premières cases de @b t
 * 
 * @param c cellule
 * @param t tableau de cellules
 * @param n inférieur à la longueur de @b t
 * @return 1 s'il y a @b c dans @b t , 0 sinon
 */
int mem_cell_table(cell c, cell t[], int n){
    for (int i=0; i<n; i++){
        if (c==t[i])
            return 1;
    }
    return 0;
}

/**
 * @brief Active la carte située en @b (x,y) du plateau @b *pp
 * 
 * @param c la carte activée
 * @param pp pointeur valide vers un plateau valide
 * @param pf pointeur valide vers une faction valide, celle qui a posé la carte
 * @param p_adv pointeur valide vers une faction valide, celle adverse à celle qui a posé la carte
 * @param x abscisse de la cellule
 * @param y ordonnée de la cellule
 */
void activation(carte c, plateau* pp, faction* pf, faction* p_adv, int x, int y){
    grid g = get_grid(*pp);
    int ddrs = get_ddrs(*pf); /*nombre actuel de points ddrs de la faction *pf*/
    liste hist_visible = get_cartes_visibles(*pp);
    int nb_retournees = len_liste(hist_visible);

    switch (get_carte_id(c)){
    case id_fise:
        add_ddrs(pf, 1);
        break;
    case id_fisa:
        if (nb_retournees%2==0)
            add_ddrs(pf, 2);
        break;
    case id_fc:
        if (find(FC, hist_visible)!=-1)
            add_ddrs(pf, 2);
        break;
    case id_ecologiie:{
        int nb = 0; /*nombre de carte fise, fisa, fc retournées*/
        nb += nb_elt(FISE, hist_visible);
        nb += nb_elt(FISA, hist_visible);
        nb += nb_elt(FC, hist_visible);
        add_ddrs(pf, nb);
        break;}
    case id_liiens:{
        liste tmp_pioche = cree_liste_vide();
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    if (get_carte_id(get_card(c_parcours)) == id_fise){//si la carte en (i,j) est FISE
                        supp_case(pp, i, j);
                        push(FISE, &tmp_pioche);
                    }
                    if (get_carte_id(get_card(c_parcours)) == id_fisa){//si la carte en (i,j) est FISA
                        supp_case(pp, i, j);
                        push(FISA, &tmp_pioche);
                    }
                    if (get_carte_id(get_card(c_parcours)) == id_fise){//si la carte en (i,j) est FC
                        supp_case(pp, i, j);
                        push(FISE, &tmp_pioche);
                    }
                }
            }
        }
        tmp_pioche = melanger(tmp_pioche);
        int nb_posees = 0; //Nombre de cartes qu'on repose
        while (test_vide(tmp_pioche)!= 1){//Tant que la tmp_pioche n'est pas vide
            nb_posees++;
            carte a_poser = pop(&tmp_pioche);
            /*Coordonnées de la cellule en haut à gauche*/
            int x_hg = taille_grille(north, g);
            int y_hg = taille_ligne_direction(west, g, x);
            pose_carte(pp, pf, a_poser, x_hg, y_hg-nb_posees);
        }
        break;}
    case id_ssa:
        if (find(ALCOOL, hist_visible)!=-1){//Si une carte alcool a été retournée
            //Parcours de grille
            for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
                for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                    cell c_parcours = get_cell(g,i,j);
                    if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                        int card_id = get_carte_id(get_card(c_parcours));
                        if (card_id == id_fise || card_id == id_fisa || card_id == id_fc)//si la carte en (i,j) est FISE, ou FISA, ou FC
                            supp_case(pp, i, j);
                    }
                }
            }
            int prem_ligne = taille_grille(north, g);
            int dern_ligne = taille_grille(south, g);
            for (int j=taille_grille(west, g); j<=taille_grille(east, g); j++){
                supp_case(pp, prem_ligne, j); //Suppression de la première ligne
                supp_case(pp, dern_ligne, j); //Suppression de la dernière ligne
            }
        }
        else
            add_ddrs(pf, 5);
        break;
    case id_alcool: //Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).
        supp_case(pp, x+1, y+1);
        supp_case(pp, x+1, y-1);
        supp_case(pp, x-1, y-1);
        supp_case(pp, x-1, y+1);
        break;
    case id_cafe:
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    int card_id = get_carte_id(get_card(c_parcours));
                    if (card_id == id_the || card_id == id_alcool)//si la carte en (i,j) est Thé ou Alcool
                        supp_case(pp, i, j);
                }
            }
        }
        if (find(ECOC, hist_visible)!= -1)
            add_ddrs(pf, 1);
        else
            add_ddrs(pf, -1);
        break;
    case id_the:
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    int card_id = get_carte_id(get_card(c_parcours));
                    if (card_id == id_cafe || card_id == id_alcool)//si la carte en (i,j) est Café ou Alcool
                        supp_case(pp, i, j);
                }
            }
        }
        if (find(ECOC, hist_visible)!= -1)
            add_ddrs(pf, 1);
        else
            add_ddrs(pf, -1);
        break;
    case id_ecocup:
        break;
    case id_reprographie:{
        int compteur = 0; //Compteur de cartes paires
        liste tmp = deepcopy(hist_visible);
        while (test_vide(tmp)!=1){
            elt e = pop(&tmp);
            int n = nb_elt(e, tmp); //Le nombre de paires dans m cartes identiques est égal au nombre d'arrêtes dans un graphe complet d'ordre m
            int nb_pair = n*(n-1)/2; //Compteur de paires de cartes pour n cartes identiques
            compteur = compteur + nb_pair;
            enlever(e, &tmp);
        }
        add_ddrs(pf, compteur);
        free(tmp);
        break;}
    case id_idb:{
        int nb_f=0; //Nombre de carte non retournées et non supprimée posées par *pf
        int nb_adv=0; //Nombre de carte non retournées et non supprimée posées par *p_adv
        
        /*Parcours de tout le plateau*/
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell curr_cell = get_cell(g, i, j);
                if (cachee_visible_existe(pp, i, j) == 0){//Si la carte en (i,j) est face cachée
                    if (get_faction_id(get_faction(curr_cell)) == get_faction_id(*pf))//Si la carte a été posée par *pf
                        nb_f++;
                    else if (get_faction_id(get_faction(curr_cell)) == get_faction_id(*p_adv))//Si la carte a été posée par *p_adv
                        nb_adv++;
                }
            }
        }
        add_ddrs(pf, nb_f);
        add_ddrs(pf, nb_adv);
        break;}
    case id_psn:
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){/*Parcours de ligne*/
            int gauche = taille_ligne_direction(west, g, i);
            int droite = taille_ligne_direction(east, g, i);
            retourne_carte(pp, i, gauche);
            retourne_carte(pp, i, droite);
        }
        break;
    case id_heure_sup:{
        int nb = nb_elt(HS, hist_visible) + 1; //La carte qui vient d'être retournée n'est pas dans l'historique des cartes retournées
        add_ddrs(p_adv, -3*nb);
        break;}
    case id_kb:{
        int nb_non_retournees = 0; //Compteur de cartes non retournées
        /*Parcours de tout le plateau*/
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                if (cachee_visible_existe(pp, i, j) == 0)//S'il y a une carte face cachée
                    nb_non_retournees++;
            }
        }
        int random_carte_num = rand()%(nb_non_retournees); //Choix au hasard d'une carte non-retournée
        int compteur_carte_rand = 0;
        /*Parcours de tout le plateau*/
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                if (cachee_visible_existe(pp, i, j) == 0){//On regarde les cartes face cachées
                    if (compteur_carte_rand == random_carte_num){//Si on tombe sur la carte choisie
                        supp_case(pp, i, j);
                        return;
                    }
                    random_carte_num++;
                }
            }
        }
        break;}
    case id_kg:{
        int nb_lignes = abs(taille_grille(south, g) - taille_grille(north, g) +1); //vérifier par calcul
        int i = rand()%(nb_lignes); //Choix d'un entier positif sur le nombre de ligne
        int nb = 0; //Nombre de cartes sur la ligne
        for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){//Parcours de ligne
            cell curr_cell = get_cell(g, i, j);
            if (get_occupee(curr_cell)==1){//S'il y a une carte sur la cellule
                nb++;
                supp_case(pp, i, j);
            }
        }
        add_ddrs(pf, 2*nb);
        break;}
    case id_mm:
        if (test_vide(hist_visible)!=0){
            carte dernier = peek(hist_visible);
            activation(dernier, pp, pf, p_adv, x, y);
        }
        break;
    case id_vy:
        if (ddrs < get_ddrs(*p_adv))
            add_ddrs(pf, 3);
        else if (ddrs > get_ddrs(*p_adv))
            add_ddrs(p_adv, 3);
        break;
    case id_js:
        /*Parcours de tout le plateau*/
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell curr_cell = get_cell(g, i, j);
                if (get_visible(curr_cell)==1){
                    if (get_carte_id(get_card(curr_cell)) == id_heure_sup)
                        supp_case(pp, i, j);
                }
            }
        }
        break;
    case id_fb:
        if (find(HS, hist_visible)!=-1){//Si la carte HS est visible
            for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++)
                supp_case(pp, x, j);
        }
        else{
            int nb = nb_elt(CD, hist_visible)
                +nb_elt(ALL, hist_visible)
                +nb_elt(GB, hist_visible)
                +nb_elt(CM, hist_visible)
                +nb_elt(TL, hist_visible)
                +nb_elt(JF, hist_visible)
                +nb_elt(DW, hist_visible);
            add_ddrs(pf, nb);
        }
        break;
    case id_cd:{
        int gauche = taille_ligne_direction(west, g, x);
        int droite = taille_ligne_direction(east, g, x);
        int haut = taille_ligne_direction(north, g, y);
        int bas = taille_ligne_direction(south, g, y);
        supp_case(pp, x, gauche);
        supp_case(pp, x, droite);
        supp_case(pp, haut, y);
        supp_case(pp, bas, y);
        break;}
    case id_all:{
        int nb = nb_elt(ECOLO, hist_visible)
                +nb_elt(ECOC, hist_visible)
                +nb_elt(ISOL, hist_visible)
                +nb_elt(PSN, hist_visible);
        add_ddrs(pf, 3*nb);
        set_ALL(pp, get_ALL(*pp) + 1);
        break;}
    case id_gb:
        if (get_ddrs(*p_adv) > ddrs){
            add_ddrs(p_adv, -3);
            add_ddrs(pf, 3);
        }
        break;
    case id_cm:
        if (find(HS, hist_visible)!=-1){
            /*Parcours de tout le plateau*/
            for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
                for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                    cell curr_cell = get_cell(g, i, j);
                    if (get_carte_id(get_card(curr_cell)) != id_cm && get_carte_id(get_card(curr_cell)) != id_heure_sup)
                        supp_case(pp, i, j);
                }
            }
        }
        break;
    case id_tl:{
        int nb = nb_elt(FISE, hist_visible);
        if (find(JF, hist_visible)!=-1){//Si Julien Forest n'est pas retourné
            add_ddrs(pf, 3*nb);
        }
        else
            add_ddrs(p_adv, -nb);
        break;}
    case id_jf:
        if (find(CAFE, hist_visible)!= -1){//Si une carte café est retournée
            int nb = nb_elt(FISE, hist_visible);
            add_ddrs(pf, 6*nb);
        }
        break;
    case id_dw:
        if (find(THE, hist_visible)!= -1){//Si une carte thé est retournée
            int nb = nb_elt(FISA, hist_visible) + nb_elt(FC, hist_visible);
            add_ddrs(pf, 3*nb);
        }
        break;
    case id_dadc:{
        int nb_ret = 0; //Nombre de carte retournées
        for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++){//Parcours de ligne
            cell c_parcours = get_cell(g, x, j);
            if (get_visible(c_parcours)==1)
                nb_ret++;
        }
        if (nb_ret >= 3) //S'il y a plus de 3 cartes retournées sur la ligne x
            add_ddrs(pf, 5);
        break;}
    case id_el:{
        liste tmp = cree_liste_vide();
        cell choix_cellules[5]; //tableau des cellules choisies
        int choix_cartes_id[5]; //tableau des id des cartes choisies
        for (int n=0; n<5; n++){
            int nb_lignes = abs(taille_grille(south, g) - taille_grille(north, g) +1);
            int nb_colonnes = abs(taille_grille(east, g) - taille_grille(west, g) +1);

            //Choix de la cellule
            int i = rand()%(nb_lignes);
            int j = rand()%(nb_colonnes);
            cell cell_choisie = get_cell(g, i, j);
            while (get_visible(cell_choisie)!=1 || mem_cell_table(cell_choisie, choix_cellules, n) == 1){//Si la carte choisie est visible, ou si la cellule a déjà été choisie (déjà dans les n premières cases de choix_cellules), on recommence
                i = rand()%(nb_lignes);
                j = rand()%(nb_colonnes);
                cell_choisie = get_cell(g, i, j);
            }
            
            //on a choisi une cellule ayant une carte visible et pas encore choisie
            choix_cellules[n] = cell_choisie;
            choix_cartes_id[n] = get_carte_id(get_card(cell_choisie));
            
            switch (choix_cartes_id[n]){
                case id_cd: push(CD, &tmp); break;
                case id_all: push(ALL, &tmp); break;
                case id_gb: push(GB, &tmp); break;
                case id_cm: push(CM, &tmp); break;
                case id_tl: push(TL, &tmp); break;
                case id_jf: push(JF, &tmp); break;
                case id_dw: push(DW, &tmp); break;
                default: break;
            }
            supp_case(pp, i, j); //On supprime la carte du plateau (si c'est une des cartes citées, elle sera déplacée, sinon simplement supprimée)
        }
        tmp = melanger(tmp);
        int prem_ligne = taille_grille(north, g);
        int y_carte_hg = taille_ligne_direction(west, g, prem_ligne);
        int compteur = 0; //Décalage vers la gauche par rapport à la carte en haut a gauche
        while (test_vide(tmp)!=1){//On pose les cartes
            elt c_mel = pop(&tmp);
            compteur++;
            pose_carte(pp, pf, c_mel, prem_ligne, y_carte_hg -compteur);
        }
        free(tmp);
        break;}
    case id_lpacav:
        for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++){//Parcours de ligne
            cell curr_cell = get_cell(g, x, j);
            if (get_visible(curr_cell)){ //Si la cellule est visible
                if (get_carte_id(get_card(curr_cell)) == id_fisa){ //Si la carte sur la cellule est FISA
                    add_ddrs(pf, 5);
                    return; //Fin
                }
            }
        }
        for (int i=taille_ligne_direction(north, g, y); i<=taille_ligne_direction(south, g, y); i++){//Parcours de colonne
            cell curr_cell = get_cell(g, i, y);
            if (get_visible(curr_cell)){ //Si la cellule est visible
                if (get_carte_id(get_card(curr_cell)) == id_fisa){ //Si la carte sur la cellule est FISA
                    add_ddrs(pf, 5);
                    return; //Fin
                }
            }
        }
        break;
    case id_ks:
        if (find(DADC, hist_visible)!=-1 && find(EL, hist_visible)!=-1 && find(LPACAV, hist_visible)!=-1)//Si ces cartes sont retournées sur le plateau
            add_ddrs(pf, 10);
        else {
            for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++)
                retourne_carte(pp, x, j);
        }
        break;
    case id_lp:
        if ((*pp)->nb_cartes_visibles + 1 == (*pp)->nb_cartes_posees){ //S'il n'y a plus qu'une carte non-visible sur le plateau (Laurent Prével, qui va être retournée après..)
            set_ddrs(pf, INT_MAX -100);
            set_ddrs(p_adv, 0);
            reinitialisation(pp);
        }
        break;
    default:
        printf("Warning : activated unknown card.\n");
        break;
    }
}

/**
 * @brief Renvoie la cellule non-activée en haut à gauche de la grille et stocke ses coordonnées dans les paramètres @b *px et @b *py
 * 
 * @param g grille valide
 * @param px pointeur valide, qui renverra vers l'abscisse de la cellule renvoyée
 * @param py pointeur valide, qui renverra vers l'ordonnée de la cellule renvoyée
 * @return la première cellule non-activée en haut à gauche de @b g
 */
cell non_visible_hg(plateau p, int* px, int* py){
    grid g = get_grid(p);
    /*Parcours de tout le plateau*/
    for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
        for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
            if (cachee_visible_existe(&p, i, j) == 0){
                *px = i;
                *py = j;
                return get_cell(g, i, j);
            }
        }
    }
    return NULL;
}

carte active_carte(plateau *pp){
    //Cellule non-visible en haut à gauche
    int x_hg;
    int y_hg;
    cell hg = non_visible_hg(*pp, &x_hg, &y_hg);
    carte c = get_card(hg);

    //Attribution des factions, celle qui a posé la carte, et son adversaire
    faction f = get_faction(hg); /*Faction qui a posé la carte*/
    faction f1;
    faction f2;
    faction adversaire;
    retourne_factions(*pp, &f1, &f2);
    if (get_faction_id(f) == get_faction_id(f1))
        adversaire = f2;
    else if (get_faction_id(f) == get_faction_id(f2))
        adversaire = f1;

    activation(c, pp, &f, &adversaire, x_hg, y_hg);
    
    //Modification de la cellule
    hg->visible = 1;
    hg->activee = 1;
    ((*pp)->nb_cartes_visibles)++;
    ((*pp)->nb_cartes_activees)++;
    push(c, &(*pp)->cartes_visibles);
    push(c, &(*pp)->cartes_activees);

    //Test de fin de manche
    if ((*pp)->nb_cartes_visibles == (*pp)->nb_cartes_posees - (*pp)->nb_ALL_retournee){//Si toutes les cartes posées ont été retournées, moins les dernières cartes du plateau affectés par l'effet de la carte Anne-Laure Ligozat, qu'on ignorera
        reinitialisation(pp); //Termine la manche
    }

    return c;
}
