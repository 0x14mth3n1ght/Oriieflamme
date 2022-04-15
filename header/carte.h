#ifndef _CARTE_H
#define _CARTE_H 

/**
* \struct ceci est une declaration d'un type abstrait carte
*/
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

#endif
