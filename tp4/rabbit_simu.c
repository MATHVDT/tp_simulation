/* 
TP Simulation
Lab # 4a–A more realistic population growth 

VILLEDIEU DE TORCY Mathieu
ZZ2 F 2 G22
*/

#include "rabbit_simu.h"
#include "tp4.h"

population_t pop;
infoPop_t infoPop;


/****************************************************************************************************************************/
/*  initMaturite : fonction qui initialise aleatoirement l'age a partir duquel un lapin devient mature (entre 4 et 8)       */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/****************************************************************************************************************************/
void initMaturite(lapin_t * lapin)
{
    long random = genrand_real1();

    if (random < 0.25)
    {
        lapin->ageMmaturite = 5;
    }
    else if (random < 0.50)
    {
        lapin->ageMmaturite = 6;
    }
    else if (random < 0.75)
    {
        lapin->ageMmaturite = 7;
    }
    else
    {
        lapin->ageMmaturite = 8;
    }
}

/****************************************************************************************************************************/
/*  maturite : fonction qui indique si un lapin est mature ou non                                                           */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/*                                                                                                                          */
/*  Sortie : Un entier qui vaut 0 si le lapin n'est pas mature et 1 sinon                                                   */
/****************************************************************************************************************************/
int maturite(lapin_t * lapin)
{
    return lapin->age >= lapin->ageMmaturite;
}

/****************************************************************************************************************************/
/*  mortLapin : fonction qui determine si un lapin meurt ce moi-ci                                                          */
/*                                                                                                                          */
/*  Entree : Un lapin                                                                                                       */
/*                                                                                                                          */
/*  Sortie : Un entier qui vaut 0 si le lapin vit, 1 si le lapin meurt, et -1 en cas d'erreur                               */
/*           (age en annee hors de [| 0 ; 15 |])                                                                            */
/****************************************************************************************************************************/
int mortLapin(lapin_t * lapin)
{
    long random = genrand_real1();
    int mort = 0;

    switch (lapin->age / 12)
    {
        case 10 :
            if (random > 50) mort = 1;
        break;
        case 11 :
            if (random > 40) mort = 1;
        break;
        case 12 :
            if (random > 30) mort = 1;
        break;
        case 13 :
            if (random > 20) mort = 1;
        break;
        case 14 :
            if (random > 10) mort = 1;
        break;
        case 15 :
            mort = 1;
        break;
        default :
            if ((maturite(lapin) && random > 35) || ((lapin->age => 0) && (lapin->age < 10) && random > 60))
            {
                mort = 1;
            }
            else
            {
                mort = -1;
            }
    }
}


int main()
{

    return 0;
}
