#include "..\header\faction.h"
#include "..\header\carte.h"
#include "..\header\structure.h"

struct faction_base {
    char* nom;
    int points_DDRS;
    liste main;
    liste pioche; 
    int nb_manches_gagnees;
};
