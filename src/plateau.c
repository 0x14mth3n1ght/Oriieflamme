#include "..\header\plateau.h"
#include "..\header\structure.h"

typedef struct plateau_base *plateau;

struct plateau_base{
    grid grille;
    int nb_carte_posees;
};
