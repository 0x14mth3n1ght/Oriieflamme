#include "../header/carte.h"

struct carte_base {
    int id;
    char* nom;
    char* description;
    int occurences;
};

int get_carte_id(carte c){
    return c->id;
};

char* get_carte_nom(carte c){
    return c->nom;
};

char* get_carte_description(carte c){
    return c->description;
};

int get_carte_occurences(carte c){
    return c->occurences;
};

