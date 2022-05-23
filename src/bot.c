#include <stdlib.h>
#include "../header/bot.h"

int choose_mulligan(){
    return rand()%2;
}

int choose_card_index(faction f){
    liste main = get_main(f);
    int size_main = len_liste(main);
    return rand()%(size_main); //choisit aléatoirement un entier entre 0 et size_main - 1
}

cell choose_cell_dispo(plateau p){
    liste dispo = get_cell_dispo(p);
    int size_dispo = len_liste(dispo);
    int choose = rand()%(size_dispo); //choisit aléatoirement un entier entre 0 et size_dispo - 1
    return get_at(choose, dispo);
}