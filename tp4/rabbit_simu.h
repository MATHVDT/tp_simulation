/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#ifndef RABBIT_SIMU_H
#define RABBIT_SIMU_H

// #include "tp4.h"
#include "lapin.h"

#define ICI printf("\nici\n");
#define POPULATION_MAX 100000000
#define PROTECTION_JEUNE_POP 7

typedef struct infoPop
{
    int nbMale;
    int nbMaleAdulte;
    int nbMaleBebe;

    int nbFemelle;
    int nbFemelleAdulte;
    int nbFemelleBebe;

    int nbAdulte;
    int nbBebe;
    int nbTotal;

} infoPop_t;

typedef struct population
{
    lapin_t *male[POPULATION_MAX];
    lapin_t *femelle[POPULATION_MAX];
} population_t;

// Prototypes de fonctions

void initPopulation();

void actualisationPopMois(int nbMoisEcoules);

void anniversaire(lapin_t **p_lapin);

void checkMort(lapin_t **p_lapin,
               int indiceLapin);

void reproduction(lapin_t *lapinMale,
                  lapin_t *lapinFemelle);

void affichagePop();

#endif