/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#ifndef RABBIT_SIMU_H
#define RABBIT_SIMU_H

#define POPULATION_MAX 1000000

enum Sexe
{
    male,
    femelle
};

typedef struct lapin
{
    int age; // Age en mois
    Sexe sexe;

} lapin_t;

typedef struct infoPop
{
    int nbMale;
    int nbFemelle;
    int nbAdulte;
    int nbBebe;
    int nbTotal;

} infoPop_t;

typedef population
{
    lapin_t male[POPULATION_MAX];
    lapin_t femelle[POPULATION_MAX];
}
population_t;

#endif