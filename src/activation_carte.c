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
cell cell_haut_gauche(plateau p){
    grid g = get_grid(p);
    int x = taille_grille(north, g);
    int y = taille_ligne_direction(west, g, x);
    return get_cell(g,x,y);
}

//Retourner la carte après l'activation.
/**
 * @brief Active la carte située en @b (x,y) du plateau @b *pp
 * 
 * @param c la carte activée
 * @param pp pointeur valide vers un plateau valide
 * @param x abscisse de la cellule
 * @param y ordonnée de la cellule
 */
void activation(carte c, plateau* pp, int x, int y){
    /*Avant la fonction*/
    grid g = get_grid(*pp);
    cell cellule = get_cell(g, x, y);
    faction f = get_faction(cellule); /*Faction qui a posé la carte*/
    /*Dans la fonction*/
    faction adverse = ???; /** @todo : Faction adverse*/
    int ddrs = get_ddrs(f); /*nombre actuel de points ddrs de la faction f*/
    liste hist_visible = get_cartes_visibles(*pp);
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
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    if (get_card_id(get_card(c_parcours)) == id_fise){//si la carte en (i,j) est FISE
                        supp_cell_grille(&g, i, j);
                        push(FISE, &tmp_pioche);
                    }
                    if (get_card_id(get_card(c_parcours)) == id_fisa){//si la carte en (i,j) est FISA
                        supp_cell_grille(&g, i, j);
                        push(FISA, &tmp_pioche);
                    }
                    if (get_card_id(get_card(c_parcours)) == id_fise){//si la carte en (i,j) est FC
                        supp_cell_grille(&g, i, j);
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
            pose_carte(pp, &f, a_poser, x_hg, y_hg-nb_posees);
        }
        break;
    case id_ssa:
        if (find(ALCOOL, hist_visible)!=-1){//Si une carte alcool a été retournée
            //Parcours de grille
            for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
                for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                    cell c_parcours = get_cell(g,i,j);
                    if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                        int card_id = get_card_id(get_card(c_parcours));
                        if (card_id == id_fise || card_id == id_fisa || card_id == id_fc)//si la carte en (i,j) est FISE, ou FISA, ou FC
                            supp_cell_grille(&g, i, j);
                    }
                }
            }
            int prem_ligne = taille_grille(north, g);
            int dern_ligne = taille_grille(south, g);
            for (int j=taille_grille(west, g); j<=taille_grille(east, g); j++){
                supp_cell_grille(&g, prem_ligne, j); //Suppression de la première ligne
                supp_cell_grille(&g, dern_ligne, j); //Suppression de la dernière ligne
            }
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
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    int card_id = get_card_id(get_card(c_parcours));
                    if (card_id == id_the || card_id == id_alcool)//si la carte en (i,j) est Thé ou Alcool
                        supp_cell_grille(&g, i, j);
                }
            }
        }
        if (find(ECOC, hist_visible)!= -1)
            add_ddrs(&f, 1);
        else
            add_ddrs(&f, -1);
        break;
    case id_the:
        //Parcours de grille
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell c_parcours = get_cell(g,i,j);
                if (get_visible(c_parcours) == 1){//S'il y a une carte sur la case et qu'elle est visible
                    int card_id = get_card_id(get_card(c_parcours));
                    if (card_id == id_cafe || card_id == id_alcool)//si la carte en (i,j) est Café ou Alcool
                        supp_cell_grille(&g, i, j);
                }
            }
        }
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
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){/*Parcours de ligne*/
            int gauche = taille_ligne_direction(west, g, i);
            int droite = taille_ligne_direction(east, g, i);
            retourne_carte(pp, &f, i, gauche);
            retourne_carte(pp, &f, i, droite);
        }
        break;
    case id_heure_sup:
        /** @todo */
        break;
    case id_kb:
        /** @todo */
        break;
    case id_kg:
        int nb_lignes = abs(taille_grille(south, g) - taille_grille(north, g) +1); //vérifier par calcul
        int j = rand()%(nb_lignes); //Choix d'un entier positif sur le nombre de ligne
        /** @todo */
        break;
    case id_mm:
        carte dernier = peek(hist_visible);
        activation(dernier, pp, x, y);
        break;
    case id_vy:
        if (ddrs < get_ddrs(adverse))
            add_ddrs(&f, 3);
        else if (ddrs > get_ddrs(adverse))
            add_ddrs(&adverse, 3);
        break;
    case id_js:
        /*Parcours de tout le plateau*/
        for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
            for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                cell curr_cell = get_cell(g, i, j);
                if ((get_carte_id(get_card(curr_cell)) == id_heure_sup) && (cachee_visible_existe(pp, i, j)==1))
                    supp_cell_grille(&g, i, j);
            }
        }
        break;
    case id_fb:
        if (find(HS, hist_visible)){
            for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++)
                supp_cell_grille(&g, x, j);
        }
        else{
            int n = nb_elt(CD, hist_visible)
                +nb_elt(ALL, hist_visible)
                +nb_elt(GB, hist_visible)
                +nb_elt(CM, hist_visible)
                +nb_elt(TL, hist_visible)
                +nb_elt(JF, hist_visible)
                +nb_elt(DW, hist_visible);
            add_ddrs(&f, n);
        }
        break;
    case id_cb:
        int gauche = taille_ligne_direction(west, g, x);
        int droite = taille_ligne_direction(east, g, x);
        int haut = taille_ligne_direction(north, g, y);
        int bas = taille_ligne_direction(south, g, y);
        supp_cell_grille(&g, x, gauche);
        supp_cell_grille(&g, x, droite);
        supp_cell_grille(&g, haut, y);
        supp_cell_grille(&g, bas, y);
        break;
    case id_all:
        int n = nb_elt(ECOLO, hist_visible)
                +nb_elt(ECOC, hist_visible)
                +nb_elt(ISOL, hist_visible)
                +nb_elt(PSN, hist_visible);
        add_ddrs(&f, 3*n);
        /** @todo suppression de la derniere carte non-retournée du plateau*/
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
            for (int i=taille_grille(north, g); i<=taille_grille(south, g); i++){
                for (int j=taille_ligne_direction(west, g, i); j<=taille_ligne_direction(east, g, i); j++){
                    cell curr_cell = get_cell(g, i, j);
                    if (get_carte_id(get_card(curr_cell)) != id_cm && get_card_id(get_card(curr_cell)) != id_heure_sup)
                        supp_cell_grille(&g, i, j);
                }
            }
        }
        break;
    case id_tl:
        if (find(JF, hist_visible)!=-1){//Si Julien Forest n'est pas retourné
            int n = nb_elt(FISE, hist_visible);
            add_ddrs(&f, 3*n);
        }
        else
            add_ddrs(&f, -nb_elt(FISE, hist_visible));
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
        int nb_ret = 0; //Nombre de carte retournées
        for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++){//Parcours de ligne
            cell c_parcours = get_cell(g, x, j);
            if (get_visible(c_parcours)==1)
                nb_ret++;
        }
        if (nb_ret >= 3) //S'il y a plus de 3 cartes retournées sur la ligne x
            add_ddrs(&f, 5);
        break;
    case id_el:
        /** @todo */
        break;
    case id_lpacav:
        for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++){//Parcours de ligne
            cell c_parcours = get_cell(g, x, j);
            if (get_visible(c_parcours)){
                int c_id = get_card_id(get_card(c_parcours));
                if (c_id == id_fisa){
                    add_ddrs(&f, 5);
                    return; //Fin
                }
            }
        for (int i=taille_ligne_direction(north, g, y); i<=taille_ligne_direction(south, g, y); i++){//Parcours de colonne
            cell c_parcours = get_cell(g, i, y);
            if (get_visible(c_parcours)){
                int c_id = get_card_id(get_card(c_parcours));
                if (c_id == id_fisa){
                    add_ddrs(&f, 5);
                    return; //Fin
                }
            }
        break;
    case id_ks:
        if (find(DADC, hist_visible)!=-1 && find(EL, hist_visible)!=-1 && find(LPACAV, hist_visible)!=-1)//Si ces cartes sont retournées sur le plateau
            add_ddrs(&f, 10);
        else {
            for (int j=taille_ligne_direction(west, g, x); j<=taille_ligne_direction(east, g, x); j++)
                retourne_carte(pp, &f, x, j);
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