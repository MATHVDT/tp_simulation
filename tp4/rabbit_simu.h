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
    enum Sexe sexe;
    int ageMmaturite;

} lapin_t;

typedef struct infoPop
{
    int nbMale;
    int nbFemelle;
    int nbAdulte;
    int nbBebe;
    int nbTotal;

} infoPop_t;

typedef struct population
{
    lapin_t male[POPULATION_MAX];
    lapin_t femelle[POPULATION_MAX];
}
population_t;

/****************************************************************************************************************************/
/*  initMaturite : fonction qui initialise aleatoirement l'age a partir duquel un lapin devient mature (entre 4 et 8)       */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/****************************************************************************************************************************/
void initMaturite(lapin_t * lapin);

/****************************************************************************************************************************/
/*  maturite : fonction qui indique si un lapin est mature ou non                                                           */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/*                                                                                                                          */
/*  Sortie : Un entier qui vaut 0 si le lapin n'est pas mature et 1 sinon                                                   */
/****************************************************************************************************************************/
int maturite(lapin_t * lapin);

/****************************************************************************************************************************/
/*  mortLapin : fonction qui determine si un lapin meurt ce moi-ci                                                          */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/*                                                                                                                          */
/*  Sortie : Un entier qui vaut 0 si le lapin vit, 1 si le lapin meurt, et -1 en cas d'erreur                               */
/*           (age en annee hors de [| 0 ; 15 |])                                                                            */
/****************************************************************************************************************************/
int mortLapin(lapin_t * lapin);

#endif