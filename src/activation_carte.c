#include <stdlib.h>
#include "../header/plateau.h"
#include "../header/carte.h"
#include "../header/faction.h"
#include "../header/structure.h"
/**
 * @file TMP_plateau.c
 * @brief Début d'implémentation des effets des cartes. À terme sera inclus dans la fonction active_carte de plateau.c
 */

//id des cartes
const int id_fise = 1;
const int id_fisa = 2;
const int id_fc = 3;
const int id_ecologiie = 4;
const int id_liiens = 5;
const int id_ssa = 6;
const int id_alcool = 7;
const int id_cafe = 8;
const int id_the = 9;
const int id_ecocup = 10;
const int id_reprographie = 11;
const int id_idb = 12;
const int id_psn = 13;
const int id_heure_sup = 14;
const int id_kb = 15;
const int id_kg = 16;
const int id_mm = 17;
const int id_vy = 18;
const int id_js = 19;
const int id_fb = 20;
const int id_cb = 21;
const int id_all = 22;
const int id_gb = 23;
const int id_cm = 24;
const int id_tl = 25;
const int id_jf = 26;
const int id_dw = 27;
const int id_dadc = 28;
const int id_el = 29;
const int id_lpacav = 30;
const int id_ks = 31;
const int id_lp = 32;

/**
 * @brief Retourne la cellule en haut, à gauche du plateau
 * 
 * @param p plateau valide
 * @return La cellule en haut à gauche du plateau
 */
cell get_haut_gauche(plateau p){
    grid g = get_grid(p);
    int y_hg = taille_direction(north, g);
    int x_hg = taille_ligne_direction(west, g, y_hg);
    return get_cell(g, x_hg, y_hg);
}

//Retourner la carte après l'activation.
/**
 * @brief Active la carte située en @b (x,y) du plateau @b *pp
 * 
 * @param c la carte activée
 * @param pp pointeur valide vers un plateau valide
 */
void activation(carte c, plateau* pp){
    /*Avant la fonction*/
    int x;
    int y;
    grid g = get_grid(*pp);
    cell cellule = get_cell(g, x, y);
    faction f = get_card_faction(*cellule); /*Faction qui a posé la carte*/
    /*Dans la fonction*/
    faction adverse = ???; /** @todo : Faction adverse*/
    int ddrs = get_ddrs(f); /*nombre actuel de points ddrs de la faction f*/
    liste hist_visible = ??? ; /** @todo : liste des cartes retournées*/
    int nb_retournees = len_liste(hist_visible);
    cell haut_gauche = get_haut_gauche(*pp);

    switch (get_carte_id(c)){
    case id_fise:
        add_ddrs(&f, 1);
        break;
    case id_fisa:
        if (nb_retournees%2==0)
            add_ddrs(&f, 2);
        break;
    case id_fc:
        if (find(FC, hist_visible)!=-1)
            add_ddrs(&f, 2);
        break;
    case id_ecologiie:
        int nb = 0; /*nombre de carte fise, fisa, fc retournées*/
        nb += nb_elt(FISE, hist_visible);
        nb += nb_elt(FISA, hist_visible);
        nb += nb_elt(FC, hist_visible);
        add_ddrs(&f, nb);
        break;
    case id_liiens:
        liste tmp_pioche = cree_liste_vide();
        while (find_carte_activee(FISE, *pp)!=NULL){
            supp_carte(FISE, pp);
            push(FISE, &tmp_pioche);
        }
        while (find_carte_activee(FISA, *pp)!=NULL){
            supp_carte(FISA, pp);
            push(FISA, &tmp_pioche);
        }
        while (find_carte_activee(FC, *pp)!=NULL){
            supp_carte(FC, pp);
            push(FC, &tmp_pioche);
        }
        tmp_pioche = melanger(tmp_pioche);
        int nb_posees = 0; //Nombre de cartes qu'on repose
        while (test_vide(tmp_pioche)!= 1){//Tant que la tmp_pioche n'est pas vide
            nb_posees++;
            carte a_poser = pop(&tmp_pioche);
            /*Coordonnées de la cellule en haut à gauche*/
            int y_hg = taille_direction(north, g);
            int x_hg = taille_ligne_direction(west, g, y_hg);
            pose_carte(pp, &f, a_poser, x_hg-nb_posees, y_hg);
        }
        break;
    case id_ssa:
        if (find_carte_activee(ALCOOL, *pp)!=NULL){//Si une carte alcool a été retournée
            while ((supp_carte(FISE, pp) || supp_carte(FISA, pp) || supp_carte(FC, pp)) != 0); //Tant qu'il y a des cartes fise, fisa et fc retournées sur le plateau
            /** @todo supprimer la première et la dernière ligne du plateau*/
        }
        else
            add_ddrs(&f, 5);
        break;
    case id_alcool: //Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).
        supp_cell_grille(&g, x+1, y+1);
        supp_cell_grille(&g, x+1, y-1);
        supp_cell_grille(&g, x-1, y-1);
        supp_cell_grille(&g, x-1, y+1);
        break;
    case id_cafe:
        while ((supp_carte(THE, pp) || supp_carte(ALCOOL, pp)) != 0); //Supprime toutes les cartes thé et alcool du plateau
        if (find(ECOC, hist_visible)!= -1)
            add_ddrs(&f, 1);
        else
            add_ddrs(&f, -1);
        break;
    case id_the:
        while ((supp_carte(CAFE, pp) || supp_carte(ALCOOL, pp)) != 0); //Supprime toutes les cartes café et alcool du plateau
        if (find(ECOC, hist_visible)!= -1)
            add_ddrs(&f, 1);
        else
            add_ddrs(&f, -1);
        break;
    case id_ecocup:
        break;
    case id_reprographie:
        /** @todo */
        break;
    case id_idb:
        /** @todo */
        break;
    case id_psn:
        for (int j=taille_direction(south, g); j<=taille_direction(north, g); j++){
            int gauche = taille_ligne_direction(west, g, j);
            int droite = taille_ligne_direction(east, g, j);
            set_visible(&g, gauche, j); /** @todo set_visible : retourne une carte sans l'activer */
            set_visible(&g, droite, j); /** @todo set_visible : retourne une carte sans l'activer */
        }
        break;
    case id_heure_sup:
        /** @todo */
        break;
    case id_kb:
        /** @todo */
        break;
    case id_kg:
        int nb_lignes = abs(taille_direction(south, g)) + abs(taille_direction(north, g)) + 1; //vérifier par calcul
        int j = rand()%(nb_lignes); //Choix d'un entier positif sur le nombre de ligne
        j = j + taille_direction(south, g); //Redécalage pour prendre en remettre les bons indices (peuvent être négatifs)
        /** @todo */
        break;
    case id_mm:
        carte dernier = peek(hist_visible);
        activation(dernier, pp);
        break;
    case id_vy:
        if (ddrs < get_ddrs(adverse))
            add_ddrs(&f, 3);
        else if (ddrs > get_ddrs(adverse))
            add_ddrs(&adverse, 3);
        break;
    case id_js:
        /*Parcours de tout le plateau*/
        for (int j=taille_direction(south, g); j<=taille_direction(north, g); j++){
            for (int i=taille_ligne_direction(west, g, j); i<=taille_ligne_direction(east, g, j); i++){
                cell curr_cell = get_cell(g, i, j);
                if ((get_carte_id(get_card(*curr_cell)) == id_heure_sup) && (cachee_visible_existe(pp, i, j)==1))
                    supp_cell_grille(&g, i, j);
            }
        }
        break;
    case id_fb:
        /** @todo */
        break;
    case id_cb:
        int gauche = taille_ligne_direction(west, g, y);
        int droite = taille_ligne_direction(east, g, y);
        int haut = taille_ligne_direction(north, g, y);
        int bas = taille_ligne_direction(south, g, y);
        supp_cell_grille(&g, gauche, y);
        supp_cell_grille(&g, droite, y);
        supp_cell_grille(&g, x, haut);
        supp_cell_grille(&g, x, bas);
        break;
    case id_all:
        /** @todo */
        break;
    case id_gb:
        if (get_ddrs(adverse) > ddrs){
            add_ddrs(&adverse, -3);
            add_ddrs(&f, 3);
        }
        break;
    case id_cm:
        if (find(HS, hist_visible)!=-1){
            /*Parcours de tout le plateau*/
            for (int j=taille_direction(south, g); j<=taille_direction(north, g); j++){
                for (int i=taille_ligne_direction(west, g, j); i<=taille_ligne_direction(east, g, j); i++){
                    cell curr_cell = get_cell(g, i, j);
                    if (get_card(*curr_cell) != CM && get_card(*curr_cell) != HS)
                        supp_cell_grille(&g, i, j);
                }
            }
        }
        break;
    case id_tl:
        /** @todo */
        break;
    case id_jf:
        if (find(CAFE, hist_visible)!= -1){
            int n = nb_elt(FISE, hist_visible);
            add_ddrs(&f, 6*n);
        }
        break;
    case id_dw:
        if (find(THE, *pp)!= -1){
            int n = nb_elt(FISA, hist_visible) + nb_elt(FC, hist_visible);
            add_ddrs(&f, 3*n);
        }
        break;
    case id_dadc:
        /** @todo */
        break;
    case id_el:
        /** @todo */
        break;
    case id_lpacav:
        /** @todo */
        break;
    case id_ks:
        if (find(DADC, hist_visible)!=-1 && find(EL, hist_visible)!=-1 && find(LPACAV, hist_visible)!=-1)//Si ces cartes sont retournées sur le plateau
            add_ddrs(&f, 10);
        else {
            for (int i=taille_ligne_direction(west, g, y); i<=taille_ligne_direction(east, g, y); i++)
                set_visible(&g, i, y); /** @todo set_visible : retourne une carte sans l'activer */
        }
        break;
    case id_lp:
        /** @todo */
        break;
    default:
        printf("Warning : activated unknown card.\n");
        break;
    }
}