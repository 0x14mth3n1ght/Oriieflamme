#ifndef _IA_H
#define _IA_H
/**
 * @file bot.h
 * @brief Mise en place des intéractions entre l'IA et le plateau
 * 
 */
#include "plateau.h"

/**
 * @brief Choisit un nombre aléatoire entre 0 et 1 et le renvoie
 * 
 * @return nombre 0 ou 1, choisi aléatoirement
 */
int choose_mulligan();

/**
 * @brief Choisit aléatoirement une carte de la main de la faction @b f et renvoie sa position dans la main
 * 
 * @param f faction valide
 * @return position de la carte de la main de @b f choisie aléatoirement
 */
int choose_card_index(faction f);

/**
 * @brief Choisit aléatoirement une cellule du plateau @b p qui soit disponible à l'emplacement et la renvoie
 * 
 * @param p plateau valide
 * @return cellule choisie aléatoirement parmi les cellules du plateau où l'emplacement est disponible
 */
cell choose_cell_dispo(plateau p);

#endif //_IA_H