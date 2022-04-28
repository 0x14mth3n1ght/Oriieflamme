#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "header/carte.h"
#include "header/faction.h"
#include "header/plateau.h"
#include "header/interface.h"
#include <time.h>

void test_init_faction()
{
    plateau plat;
    plat = cree_plateau();

    faction faction1;
    faction faction2;
    retourne_factions(plat,&faction1, &faction2);

    CU_ASSERT_NOT_EQUAL(get_faction_id(faction1),get_faction_id(faction2));

    CU_ASSERT_EQUAL(get_ddrs(faction1), 0); // TEST POINT DDRS avec getter
    CU_ASSERT_EQUAL(get_ddrs(faction2), 0);

    CU_ASSERT_EQUAL(get_nb_victoires(faction1), 0);
    CU_ASSERT_EQUAL(get_nb_victoires(faction2), 0);

    // TEST BON NOMBRE DE CARTE
    CU_ASSERT_EQUAL(len_liste(get_main(faction1)), nb_cartes_main_debut_manche);
    CU_ASSERT_EQUAL(len_liste(get_main(faction2)), nb_cartes_main_debut_manche);

    detruire_plateau(&plat);
}

void test_init_plateau()
{
    plateau plat;
    plat = cree_plateau();

    CU_ASSERT_EQUAL(get_nb_cartes_posees(plat), 0);
    CU_ASSERT_EQUAL(get_nb_cartes_visibles(plat), 0);
    CU_ASSERT_EQUAL(get_nb_cartes_activees(plat), 0);


    

    detruire_plateau(&plat);

}
void test_starting_faction() {

    srand(time(NULL)); // Utilisé pour pour générer le rand()
    int sum=0;
    int n=1000;
    for(int i=0;i<n;i+=1){
        sum+=rand()%2; //Test starting faction
    }
    float proba= sum/n;
    CU_ASSERT(proba>0.40&&proba<0.60);
    
}

void test_starting_faction_rd_2(){
    srand(time(NULL)); // Utilisé pour pour générer le rand()

    int starting_faction_rd_1=rand() % 2;
    int starting_faction_rd_2=(starting_faction_rd_1 + 1) % 2;
    CU_ASSERT_NOT_EQUAL(starting_faction_rd_1,starting_faction_rd_2);

}

void test_troisieme_manche() {
    plateau plat;
    plat = cree_plateau();

    faction faction1;
    faction faction2;
    retourne_factions(plat,&faction1, &faction2);

    set_nb_victoires(&faction1,2);
    CU_ASSERT_EQUAL(reinitialisation(&plat),0);

    detruire_plateau(&plat);


    plat = cree_plateau();
    retourne_factions(plat,&faction1, &faction2);

    set_nb_victoires(&faction1,1);
    set_nb_victoires(&faction2,1);
    CU_ASSERT_EQUAL(reinitialisation(&plat),1);


    detruire_plateau(&plat);

}

void test_mulligan() {
    plateau plat;
    plat = cree_plateau();

    faction faction1;
    faction faction2;
    retourne_factions(plat,&faction1, &faction2);

    liste main_avt_mulligan = get_main(faction1);

    CU_ASSERT_EQUAL(a_remelanger_main(faction1),0);
    CU_ASSERT_EQUAL(a_remelanger_main(faction2),0);

    remelanger_main(&faction1);

    CU_ASSERT_EQUAL(a_remelanger_main(faction1),1);
    CU_ASSERT_EQUAL(a_remelanger_main(faction2),0);

    liste main_apr_mulligan = get_main(faction1);

    CU_ASSERT_EQUAL(liste_equals(main_avt_mulligan,main_apr_mulligan),0);
    
    detruire_plateau(&plat);
}

void test_poser_carte() {
    plateau plat;
    plat = cree_plateau();

    faction faction1;
    faction faction2;
    retourne_factions(plat,&faction1, &faction2);

    liste main_f1= get_main(faction1);
    carte c1 = peek(main_f1);

    CU_ASSERT_EQUAL(pose_carte(&plat,&faction1,c1,0,0),1);
    CU_ASSERT_EQUAL(cachee_visible_existe(plat,0,0),0);

    grid grid_p= get_grid(plat);
    cell cell0 = get_cell(grid_p,0,0);

    carte c2 = get_card(cell0);

    CU_ASSERT_EQUAL(get_carte_id(c1),get_carte_id(c2));
    CU_ASSERT_EQUAL(get_occupee(cell0),1);
    CU_ASSERT_EQUAL(get_visible(cell0),0);
    CU_ASSERT_EQUAL(get_activee(cell0),0);

    CU_ASSERT_EQUAL(get_nb_cartes_posees(plat),1);
    CU_ASSERT_EQUAL(get_nb_cartes_visibles(plat),0);
    CU_ASSERT_EQUAL(get_nb_cartes_activees(plat),0);

    detruire_plateau(&plat);

}


void test_vanqueur_manche(){
    plateau plat;
    plat = cree_plateau();

    faction faction1;
    faction faction2;
    retourne_factions(plat,&faction1, &faction2);


}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("faction_test", 0, 0);

    CU_add_test(suite, "faction", test_init_faction);
    CU_add_test(suite, "plateau", test_init_plateau);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}