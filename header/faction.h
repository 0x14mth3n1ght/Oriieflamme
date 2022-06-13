#ifndef _FACTION_H
#define _FACTION_H
#include "structure.h"

/* vérifier qu'il n'y a pas de soucis avec le include "structure" */

/**
* \struct ceci est le type faction
*/

struct faction_base {
    int id;
    char* nom;
    int points_DDRS;
    liste main;
    liste pioche; 
    int nb_manches_gagnees;
    /* vaut 0 lorsque la faction est créee */
    int a_remelange;
};

typedef struct faction_base faction;

/**
* \brief cette fonction permet de savoir si une faction
* a utilise l'option de remelanger sa main, c'est a dire,
* remettre sa main dans la boite a idee, la melanger, 
* et repiocher le nombre de cartes autorisees
* \param f une faction
* \attention 1) la faction passee en parametre doit exister
* si ce n'est pas le cas
* \return la fonction retourne l'entier 1 si la faction 
* a utilise l'option de remelanger sa main et 0 sinon
*/
int a_remelanger_main(faction f);

/**
* \brief cette procedure permet a une faction d'utiliser
* l'option de remelanger sa main, c'est a dire, 
* remettre sa main dans la boite a idee, la melanger,
* et repiocher nb_cartes_main_debut_manche cartes
* \param f un pointeur vers une faction (ici il y aura
* \a modification des champs de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* 2) si la faction a deja utilise l'option de remelanger sa main, 
* elle ne peut pas le refaire
* \return la procedure ne retourne rien
*/
void remelanger_main(faction *f);

/**
* \brief cette procedure permet a une faction de vider sa 
* main dans sa pioche. A la fin de la procedure
* la main de la faction est donc vide et la pioche modifiee
* \param f un pointeur vers une faction (ici il y aura 
* \a modification des champs de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* 2) la main ne doit pas etre deja vide
* \return la procedure ne retourne rien
*/
void vider_main(faction *f);

/**
* \brief cette procedure permet a une faction de melanger sa pioche
* \param f un pointeur vers une faction (ici il y aura 
* \a modification des champs de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* \return la procedure ne retourne rien
*/
void melanger_pioche(faction *f);

/**
* \brief cette procedure permet a une faction de repiocher ses cartes
* \param f un pointeur vers une faction (ici il y aura
* \a modification des champs de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* 2) la main doit etre initialement vide
* \return la procedure ne retourne rien
*/
void repiocher(faction *f);

/**
* \brief fonction qui permet de récupérer l'id d'une faction
* \param f une faction
* \attention la faction doit exister
* \return un entier correspondant à l'id de la faction
*/
int get_faction_id(faction f);

/**
* \brief procédure qui permet de fixer l'id d'une faction
* \param f un pointeur valide vers une faction
* \param n entier positif ou nul, l'id de la faction prendra cette valeur 
* \attention la faction doit exister
* \return rien
*/
void set_faction_id(faction *f, int n);

/**
* \brief cette fonction permet de récupérer le nom d'une faction
* \param f une faction
* \attention la faction doit exister
* \return le nom de la faction
*/
char* get_faction_nom(faction f);
 
/**
* \brief cette fonction permet de récupérer le nombre de points DDRS d'une faction
* \param f une faction
* \attention la faction doit exister
* \return le nombre de points DDRS de la faction
*/
int get_ddrs(faction f);

/**
* \brief cette procédure permet de modifier le nombre de points DDRS d'une faction
* \param f un pointeur vers une faction
* \param i un nombre de points a accorder 
* \attention le pointeur doit pointer vers une faction existante
* \attention le nombre passe en parametre est positif ou nul
* \return rien
*/
void set_ddrs(faction *f, int i);

/**
* \brief cette procédure permet d'ajouter un nombre de points DDRS à une faction
* \param f un pointeur vers une faction
* \param i un nombre de points a ajouter
* \attention le pointeur doit pointer vers une faction existante
* \attention le nombre passe en parametre est positif ou nul
* \return rien
*/
void add_ddrs(faction *f, int i);

/**
* \brief cette fonction permet de récupérer la main d'une faction 
* \param f une faction
* \attention la faction doit exister
* \return la main de la faction
*/
liste get_main(faction f);

/**
* \brief cette fonction permet d'obtenir le nombre de victoires d'une faction
* \param f une faction
* \attention la faction doit exister
* \return le nombre de victoires d'une faction
*/
int get_nb_victoires(faction f);

/**
* \brief cette fonction permet de modifier le nombre de victoires d'une faction
* \param f un pointeur vers une faction
* \param i un nombre de victoires a accorder
* \attention le pointeur doit pointer vers une faction existante
* \attention le nombre passe en parametre est positif ou nul
* \return rien 
*/
void set_nb_victoires(faction *f, int i);

/**
* \brief cette fonction permet d'obtenir la pioche d'une faction
* \param f une faction
* \attention la faction doit exister
* \return la pioche d'une faction
*/  
liste get_pioche(faction f);

/* fonctions supplémentaires que j'implémenterai si j'ai le temps */

/**
* \brief cette procédure permet de modifier la pioche d'une
* faction en la remplacant par une pioche par défault, dans laquelle 
* toutes les cartes sont rangees "dans l'ordre"
* \param f un pointeur vers une faction
* \attention le pointeur doit pointer vers une faction existante
* \return 
*/
void set_pioche_defaut(faction *f);

/**
* \brief cette procédure permet de modifier la main d'une faction
* \param cartes une liste de cartes
* \param f un pointeur vers une faction
* \attention la liste ne doit pas avoir plus de nb_cartes_main_debut_manche cartes 
* \attention le pointeur doit pointer vers une faction existante
* \return rien 
*/
void set_main(faction *f, liste cartes);

/**
* \brief cette procédure permet de modifier la pioche d'une faction, plus precisement
* la pioche prend comme valeur la liste de cartes passe en argument
* \param cartes une liste de cartes
* \param f un pointeur vers une faction
* \attention le pointeur doit pointer vers une faction existante 
* \return rien 
*/
void set_pioche(faction *f, liste cartes);

/**
* \brief cette procédure permet de donner un nouveau nom a une faction
* \param f un pointeur vers une faction
* \param n le nouveau nom de la faction
* \return rien
*/ 
void set_name(faction *f, char* n);

/* variables globales */

/**
* \brief cette fonction retourne une faction par défaut et ne prend aucun arguement
* \return une faction
*/ 
faction set_faction_defaut();


#endif
