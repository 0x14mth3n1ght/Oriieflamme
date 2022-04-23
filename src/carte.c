#include "../header/carte.h"
#include <stdio.h>
#include <stdlib.h>

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

int main(){
    print("nom = %s", get_carte_nom(CD));
    return 0;
};