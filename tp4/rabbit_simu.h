/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#ifndef RABBIT_SIMU_H
#define RABBIT_SIMU_H

#include "tp4.h"
#include "lapin.h"

#define POPULATION_MAX 1000000

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

void initPopulation(population_t *pop,
                    infoPop_t *infoPop);

void actualisationPopMois(population_t *pop,
                          infoPop_t *infoPop);

void anniversaire(infoPop_t *infoPop,
                  lapin_t *lapin);

void checkMort(population_t *pop,
               infoPop_t *infoPop,
               lapin_t *lapin,
               int indiceLapin);

void reproduction(population_t *pop,
                  infoPop_t *infoPop,
                  lapin_t *lapinMale,
                  lapin_t *lapinFemelle);

#endif