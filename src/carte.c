#include "../header/carte.h"

int get_carte_id(carte c){
    return c.id;
};

char* get_carte_nom(carte c){
    return c.nom;
};

char* get_carte_description(carte c){
    return c.description;
};

int get_carte_occurences(carte c){
    return c.occurences;
};

char* get_nom_court(carte c){
    return c.nom_court;
};

int equals(carte c, carte d){
  return (c.id == d.id);
};

/**
 * @brief fonction renvoyant une carte avec les arguments passés en paramètre
 * @param id l'id de la carte
 * @param nom le nom de la carte
 * @param desc la description de la carte
 * @param occ le nombre d'occurences de la carte
 * @param nom_court le nom raccourci la carte (6 caractères max)
 * @return la carte voulue
 */
carte constructeur_de_carte(int id, char* nom, char* desc, int occ, char* nom_court){
    carte out;
    out.id = id;
    out.nom = nom;
    out.description = desc;
    out.occurences = occ;
    out.nom_court = nom_court;
    return out;
};

void init_cartes(){
    FISE = constructeur_de_carte(1, "FISE", "La faction qui a posé cette carte gagne 1 point DDRS.", 4, " FISE ");
    FISA = constructeur_de_carte(2, "FISA", "La faction qui a posé cette carte gagne 2 points DDRS si le nombre de cartes retournées sur le plateau (y compris celle-ci) est pair, et 0 sinon.", 4, " FISA ");
    FC = constructeur_de_carte(3, "FC", "La faction qui a posé cette carte gagne 4 points DDRS si au moins une autre carte FC est retournée sur le plateau et 0 sinon", 4, "  FC  ");
    ECOLO = constructeur_de_carte(4, "EcologIIE", "La faction qui a posé cette carte gagne 1 point DDRS par carte FISE/FISA/FC retournée.", 2, "ECOLOG");
    IIE = constructeur_de_carte(5, "lIIEns", "Prenez toutes les cartes FISE/FISA/FC retournées, retirez les du plateau, mélangez les et reposez les face cachées une par une sur la gauche de la carte la plus en haut à gauche du plateau, dans cet ordre. Les prochaines cartes à être retournées sont ces cartes là.", 2, "LIIENS");
    SSALCOOL = constructeur_de_carte(6, "Soirée sans alcool", "Si au moins une carte alcool est retournée, supprimez toutes les cartes FISE/FISA/FC retournées du plateau. Supprimez ensuite la première et la dernière ligne du plateau. Sinon la faction qui a posé cette carte gagne 5 points DDRS.", 1, "SALCOO");
    ALCOOL = constructeur_de_carte(7, "Alcool", "Supprimez du plateau toutes les cartes qui touchent cette carte-ci (mais laissez la carte Alcool sur le plateau).", 1, "ALCOOL");
    CAFE = constructeur_de_carte(8, "Café", "Supprimez toutes les cartes Thé et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.", 3, " CAFE ");
    THE = constructeur_de_carte(9, "Thé", "Supprimez toutes les cartes Café et Alcool retournées sur le plateau. Si une carte Ecocup est retournée sur le plateau, la faction qui a posé cette carte gagne 1 point DDRS. Sinon elle perd 1 point DDRS.", 3, " THE  ");
    ECOC = constructeur_de_carte(10, "Ecocup", "Cette carte est sans effet.", 1, "ECOCUP");
    REPRO = constructeur_de_carte(11, "Reprographie", "La faction adverse de celle qui a posé cette carte perd 1 points DDRS pour chaque paire de cartes retournées et identiques sur le plateau. (S'il y a 3 cartes identiques, cela fait 3 paires).", 1, "REPROG");
    ISOL = constructeur_de_carte(12, "Isolation du bâtiment", "Chaque faction gagne 1 point DDRS par carte non retournée et non supprimée du plateau qu'elle a posée sur le plateau.", 1, "ISOLAT");
    PSN = constructeur_de_carte(13, "Parcours sobriété numérique", "Retournez toutes les cartes non retournées les plus à gauche et à droite de chaque ligne, sans appliquer leur effet.", 1, "SOBREN");
    HS = constructeur_de_carte(14, "Heures supplémentaires", "La faction adverse de celle qui a posé cette carte perd 3 points DDRS par carte Heures supplémentaires retournée sur le plateau (y compris celle-ci)", 1, "H_SUPP");
    KB = constructeur_de_carte(15, "Kahina Bouchama", "Supprimez une carte non retournée du plateau choisie au hasard.", 1, "KBOUCH");
    KG = constructeur_de_carte(16, "Kevin Goilard", "Supprimez une ligne au hasard, la faction qui a posé cette carte gagne 2 points DDRS par carte supprimée ainsi.", 1, "KGOILA");
    MM = constructeur_de_carte(17, "Massinissa Merabet", "La faction qui a posé cette carte réactive l'effet de la dernière carte retournée avant Massinissa Merabet, en faisant comme elle l'avait posée elle-même, même si ce n'est pas le cas.", 1, "MMERAB");
    VY = constructeur_de_carte(18, "Vitéra Y", "La faction qui a le moins de points DDRS gagne 3 points DDRS.", 1, "VITERY");
    JS = constructeur_de_carte(19, "Jonas Senizergues", "Supprimez toutes les cartes Heures supplémentaires retournées du plateau.", 1, "JSENIZ");
    FB = constructeur_de_carte(20, "Fetia Bannour", "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes de la ligne et de la colonne où est posée cette carte (y compris celle-ci). Sinon la faction qui a posé cette carte gagne 1 point DDRS par carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest et Dimitri Watel retournée sur le plateau.", 1, "FBANNO");
    CD = constructeur_de_carte(21, "Catherine Dubois", "Supprimez la première et la dernière cartes de la ligne et de la colonne où est posée cette carte.", 1, "CDUBOI");
    ALL = constructeur_de_carte(22, "Anne-Laure Ligozat", "Pour chaque carte EcologIIE, Ecocup, Isolation du bâtiment et parcours Sobriété numérique retournée, la faction qui a posé cette carte gagne 3 points DDRS et la dernière carte non retournée du plateau est supprimée. (L'effet continue même si Anne-Laure Ligozat ou une des 4 cartes précédemment mentionnées est supprimée).", 1, "ALIGOZ");
    GB = constructeur_de_carte(23, "Guillaume Burel", "Si la faction adverse de celle qui a posé cette carte a plus de points DDRS, la seconde lui vole 3 points DDRS.", 1, "GBUREL");
    CM = constructeur_de_carte(24, "Christophe Mouilleron", "Si la carte Heures supplémentaires est retournée sur le plateau, supprimez toutes les cartes retournées du plateau sauf les cartes Christophe Mouilleron et Heures supplémentaires.", 1, "CMOUIL");
    TL = constructeur_de_carte(25, "Thomas Lim", "Si Julien Forest n'est par retourné sur le plateau, la faction qui a posé cette carte gagne 3 points DDRS par carte FISE retournée sur le plateau. Sinon la faction adverse perd 1 point DDRS par carte FISE retournée sur le plateau.", 1, " TLIM ");
    JF = constructeur_de_carte(26, "Julien Forest", "La faction qui a posé cette carte gagne 6 points DDRS par carte FISE retournée sur le plateau si au moins une carte Café est retournée sur le plateau.", 1, "JFORES");
    DW = constructeur_de_carte(27, "Dimitri Watel", "La faction qui a posé cette carte gagne 3 points DDRS par carte FISA ou FC retournée sur le plateau si au moins une carte Thé est retournée sur le plateau.	", 1, "DWATEL");
    DADC = constructeur_de_carte(28, "Djibril-Aurélien Dembele-Cabot", "S'il y a plus de 3 cartes retournées sur la ligne de cette carte, la faction qui a posé cette carte gagne 5 points DDRS.", 1, "DCABOT");
    EL = constructeur_de_carte(29, "Eric Lejeune", "Prenez au hasard 5 cartes retournées du plateau (ou toutes les cartes retournées du plateau s'il y a moins de 5). Si une de ces cartes est une carte Catherine Dubois, Anne-Laure Ligozat, Guillaume Burel, Christophe Mouilleron, Thomas Lim, Julien Forest ou Dimitri Watel, mélangez les et placez les à gauche de la case la plus à gauche de la première ligne. Les prochaines cartes à être retournées sont ces cartes là. Sinon, supprimez ces cartes du plateau.", 1, "ELEJEU");
    LPACAV = constructeur_de_carte(30, "Lucienne Pacavé", "S'il y a une carte FISA retournée dans la même ligne ou la même colonne que cette carte, la faction qui a posé cette carte gagne 5 points DDRS.", 1, "LPACAV");
    KS = constructeur_de_carte(31, "Katrin Salhab", "Si les cartes Djibril-Aurélien Djembele-Cabeau, Eric Lejeune et Lucienne Pacavé sont retournées, la faction qui a posé cette carte gagne 10 points DDRS. Sinon, retournez toutes les cartes dans la même ligne de cette carte sans appliquer leurs effets.", 1, "KSALHA");
    LP = constructeur_de_carte(32, "Laurent Prével", "Si Laurent Prével est la dernière carte retournée du plateau, la faction qui a posé cette carte gagne la manche, quel que soit le nombre de points DDRS des deux factions.", 1, "LPREVE");
};

