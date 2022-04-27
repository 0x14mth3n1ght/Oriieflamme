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

int equals(carte c, carte d){
  return (c.id == d.id);
};

