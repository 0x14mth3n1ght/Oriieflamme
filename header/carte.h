#ifndef _CARTE_H
#define _CARTE_H 
#include "structure.h"

/**
* \struct ceci est un type abstrait pour carte
*/
typedef struct carte_base *carte;

typedef carte elt;

/**
* \brief cette fonction permet de recuperer l'id d'une carte
* \param c une carte 
* \attention la carte passee en parametre doit exister
* \return retourne l'id de la carte
*/
int get_carte_id(carte c);

/**
* \brief cette fonction permet de recuperer le nom d'une carte
* \param c une carte 
* \attention la carte passee en parametre doit exister
* \return retourne le nom de la carte
*/
char* get_carte_nom(carte c);

/**
* \brief cette fonction permet de recuperer la description d'une carte
* \param c une carte 
* \attention la carte passee en parametre doit exister
* \return retourne la description de la carte
*/
char* get_carte_description(carte c);

/**
* \brief cette fonction permet de recuperer le nombre d'occurences d'une carte
* \param c une carte 
* \attention la carte passee en parametre doit exister
* \return retourne le nombre d'occurences de la carte
*/
int get_carte_occurences(carte c);

/* CONSTANTES */

int nb_cartes_main_debut_manche = 8;
int nb_manches_gagnantes = 2;

const carte FISE;
const carte FISA;
const carte FC;
const carte ECOLO;
const carte IIE;
const carte SSALCOOL;
const carte ALCOOL;
const carte CAFE;
const carte THE;
const carte ECOC;
const carte REPRO;
const carte ISOL;
const carte PSN;
const carte HS;
const carte KB;
const carte KG;
const carte MM;
const carte VY;
const carte JS;
const carte FB;
const carte CD;
const carte ALL;
const carte GB;
const carte CM;
const carte TL;
const carte JF;
const carte DW;
const carte DADC;
const carte EL;
const carte LPACAV;
const carte KS;
const carte LP;

#endif
