/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#include "rabbit_simu.h"

population_t pop;
infoPop_t infoPop;

int main()
{

    return 0;
}

/********************************************************/
/* initPopulation : Initialise la population de lapin   */
/*                  avec un male et une femelle bebes   */
/*                  et met a jour les info sur la pop   */
/* Entree : rien                                        */
/*                                                      */
/* Sortie  : rien                                       */
/********************************************************/
void initPopulation()
{
    // Initialisation de la population

    // Initialisation information population
    infoPop.nbMaleAdulte = 0;
    infoPop.nbMaleBebe = 1;

    infoPop.nbFemelleAdulte = 0;
    infoPop.nbFemelleBebe = 1;

    infoPop.nbAdulte = 0;
    infoPop.nbBebe = 2;
    infoPop.nbTotal = 2;

    // Ajout de deux lapins initiaux
    pop.male[0] = creerLapin(male);
    pop.femelle[0] = creerLapin(femelle);
}

/********************************************************/
/* creerLapin : Cree un lapin du sexe donne en parametre*/
/*              et initialise ses caracteristiques      */
/*                                                      */
/* Entree : le sexe du lapin                            */
/*                                                      */
/* Sortie  : l'adresse du lapin cree                    */
/********************************************************/
lapin_t *creerLapin(enum Sexe inSexe)
{
    lapin_t *lapin = malloc(sizeof(lapin_t));
    if (lapin != NULL)
    {
        lapin->age = 0;
        lapin->sexe = inSexe;
    }
    else
    {
        printf("Erreur creation lapin\n");
    }
    return lapin;
}