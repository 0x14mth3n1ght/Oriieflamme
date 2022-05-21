#ifndef _CARTE_H
#define _CARTE_H 

/**
* \struct ceci est le type carte
*/
struct carte_base {
    int id;
    char* nom;
    char* description;
    int occurences;
    char* nom_court;
};

typedef struct carte_base *carte;



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

/**
* \brief fonction permettant d'avoir accès au nom court de la carte
* \param c la carte 
* \return le nom court
*/
char* get_nom_court(carte c); 

/**
* \brief fonction permettant de savoir si deux cartes sont égales
* \param c
* \param d les deux cartes
* \return 1 si elles sont égales, 0 sinon.
*/
int equals(carte c, carte d);

/**
 * \brief Initialise toutes les cartes du jeu
 */
void init_cartes();

/* CONSTANTES */

#define nb_cartes_main_debut_manche 8
#define nb_manches_gagnantes 2

carte FISE;
carte FISA;
carte FC;
carte ECOLO;
carte IIE;
carte SSALCOOL;
carte ALCOOL;
carte CAFE;
carte THE;
carte ECOC;
carte REPRO;
carte ISOL;
carte PSN;
carte HS;
carte KB;
carte KG;
carte MM;
carte VY;
carte JS;
carte FB;
carte CD;
carte ALL;
carte GB;
carte CM;
carte TL;
carte JF;
carte DW;
carte DADC;
carte EL;
carte LPACAV;
carte KS;
carte LP;


#endif

