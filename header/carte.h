#ifndef _CARTE_H
#define _CARTE_H 

/**
* \struct ceci est le type carte
*/
struct carte {
    int id;
    char* nom;
    char* description;
    int occurences;
    char* nom_court;
};

typedef struct carte carte;

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
* \return 1 si elles sont égales, 0 sinon
*/
int equals(carte c, carte d);

/* CONSTANTES */

int nb_cartes_main_debut_manche = 8;
int nb_manches_gagnantes = 2;

const carte FISE = {1, "FISE", "La faction qui a posé cette carte gagne 1 point DDRS.", 4, "FISE"};
const carte FISA = {2, "FISA", "La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.", 4, "FISA"};
const carte FC = {3, "FC", "La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon", 4, "FC"};
const carte ECOLO = {4, "EcologIIE", "La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.", 2, "ECOLO"};
const carte IIE = {5, "lIIEns", "Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.", 2, "LIIEN"};
const carte SSALCOOL = {6, "Soirée sans alcool", "Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.", 1, "SSALCOOL"};
const carte ALCOOL = {7, "Alcool", "Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).", 1, "ALCOOL"};
const carte CAFE = {8, "Café", "Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.", 3, "CAFE"};
const carte THE = {9, "Thé", "Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.", 3, "THE"};
const carte ECOC = {10, "Ecocup", "Cette carte est sans effet.", 1, "ECOC"};
const carte REPRO = {11, "Reprographie", "La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).", 1, "REPRO"};
const carte ISOL = {12, "Isolation du bâtiment", "Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.", 1, "ISOLATION"};
const carte PSN = {13, "Parcours sobriété numérique", "Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.", 1, "SOBRE_NUM"};
const carte HS = {14, "Heures supplémentaires", "La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci)", 1, "HEURES_SUPP"};
const carte KB = {15, "Kahina Bouchama", "Supprimez une carte non retournée du plateau choisie au hasard.", 1, "KBOUCHAMA"};
const carte KG = {16, "Kevin Goilard", "Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.", 1, "KGOILARD"};
const carte MM = {17, "Massinissa Merabet", "La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.", 1, "MMERABET"};
const carte VY = {18, "Vitéra Y", "La faction qui a le moins de points DDRS gagne 3 points DDRS.", 1, "VY"};
const carte JS = {19, "Jonas Senizergues", "Supprimez toutes les cartes Heures supplémentaires retournées du plateau.", 1, "JSENIZ"};
const carte FB = {20, "Fetia Bannour", "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.", 1, "FBANNOUR"};
const carte CD = {21, "Catherine Dubois", "Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.", 1, "CDUBOIS"};
const carte ALL = {22, "Anne-Laure Ligozat", "Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).", 1, "ALLIGOZAT"};
const carte GB = {23, "Guillaume Burel", "Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.", 1, "GBUREL"};
const carte CM = {24, "Christophe Mouilleron", "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.", 1, "CMOUILLERON"};
const carte TL = {25, "Thomas Lim", "Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.", 1, "TLIM"};
const carte JF = {26, "Julien Forest", "La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.", 1, "JFOREST"};
const carte DW = {27, "Dimitri Watel", "La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.	", 1, "DWATEL"};
const carte DADC = {28, "Djibril-Aurélien Dembele-Cabot", "S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.", 1, "DCABOT"};
const carte EL = {29, "Eric Lejeune", "Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.", 1, "ELEJEUNE"};
const carte LPACAV = {30, "Lucienne Pacavé", "S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.", 1, "LPACAVE"};
const carte KS = {31, "Katrin Salhab", "Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.", 1, "KSALHAB"};
const carte LP = {32, "Laurent Prével", "Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions.", 1, "LPREVEL"};

#endif
