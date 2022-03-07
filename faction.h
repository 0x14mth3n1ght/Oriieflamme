/* fichier faction.h */

/**
* \struct ceci est une declaration d'un type abstrait
* faction, lors de l'implementation, il faudra specifier
* les differents champs du type faction 
* (une faction sera donc caracterisee par un tuple)
* \attention j'attire l'attention sur le fait qu'il ne faudra
* pas oublier d'inclure certains champs lors de l'implementation afin 
* que les fonctions/procedures suivantes fonctionnent correctement
* en particulier des champs "main" et "pioche"
*/
typedef struct faction_base *faction;

/**
* \brief cette fonction permet de savoir si une faction
* a utilise l'option de remelanger sa main, c'est a dire,
* remettre sa main dans la boite a idee, la melanger, 
* et repiocher 8 cartes
* \param f une faction
* \attention 1) la faction passee en parametre doit exister
* si ce n'est pas le cas, une exception est renvoyee
* \return la fonction retourne l'entier 1 si la faction 
* a utilise l'option de remelanger sa main et 0 sinon
*/
int a_remelanger_main(faction f);

/**
* \brief cette procedure permet a une faction d'utiliser
* l'option de remelanger sa main, c'est a dire, 
* remettre sa main dans la boite a idee, la melanger,
* et repiocher 8 cartes
* \param fp un pointeur vers une faction (ici il y aura
* \a modification des champs "main" et "pioche" de la faction)
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
* \param fp un pointeur vers une faction (ici il y aura 
* \a modification des champs "main" et "pioche" de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* 2) la main ne doit pas etre deja vide
* \return la procedure ne retourne rien
*/
void vider_main(faction *f);

/**
* \brief cette procedure permet a une faction de melanger sa pioche
* \param fp un pointeur vers une faction (ici il y aura 
* \a modification du champ "pioche" de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* \return la procedure ne retourne rien
*/
void melanger_pioche(faction *f);

/**
* \brief cette procedure permet a une faction de repiocher ses cartes
* \param fp un pointeur vers une faction (ici il y aura
* \a modification du champ "main" et "pioche" de la faction)
* \attention 1) le pointeur doit pointer vers une faction existante
* 2) la main doit etre initialement vide
* \return la procedure ne retourne rien
*/
void repiocher(faction *f);