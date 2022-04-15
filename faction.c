#include "faction.h"
#include "carte.h"
//#include "structure.h"

struct faction_base {
    char* nom;
    int points_DDRS;
    carte* main;
    pile pioche; 
    int nb_manches_gagnees;
}

